#include "integral/gaussian_lookup2.h"
#include "integral/gaussian_lookup.h"

#include <boost/math/distributions/normal.hpp>
#include "boost/date_time/posix_time/posix_time.hpp"

#include "gtest/gtest.h"

using namespace Tools::Integral;
using namespace Tools::Functions;

TEST(gaussian1f, values1D) {
  Gaussian1f gaussian(0.f, 1.f);
  EXPECT_NEAR(0.398942, gaussian(0.f), 1e-3);
  EXPECT_NEAR(0.241971, gaussian(1.f), 1e-3);
}

TEST(gaussian2f, values2D) {
  Gaussian2f gaussian(Gaussian2f::InputValue(0.f, 0.f),  Gaussian2f::Covariance::Identity());
  EXPECT_NEAR(0.1591549, gaussian(Gaussian2f::InputValue(0.f, 0.f)), 1e-3);
  EXPECT_NEAR(0.05854982, gaussian(Gaussian2f::InputValue(1.f, 1.f)), 1e-3);
}

TEST(integral1D, integralOverFunction) {
  Gaussian1f gauss(0.f, 1.f);
  IntegralOverFunction<float, 1> integral(&gauss, 1e-1);
  EXPECT_NEAR(1.f, integral.integrate(-100.f, 100.f), 1e-6);
}

TEST(integral2D, integralOverFunction) {
  Gaussian2f gauss(Gaussian2f::InputValue(0.f, 0.f), Gaussian2f::Covariance::Identity());
  IntegralOverFunction<float, 2> integral(&gauss, 1e-1);
  EXPECT_NEAR(1.f, 
	      integral.integrate(IntegralOverFunction<float, 2>::InputValue(-25.f, -25.f), 
				 IntegralOverFunction<float, 2>::InputValue(25.f, 25.f)),
	      1e-3);
}

TEST(integralLookup1D, values){
  Gaussian1f gauss(0.f, 1.f);
  IntegralLookup1D<float> lookup(&gauss, -100.f, 100.f, 1e-1);
  EXPECT_NEAR(1.f, lookup.integrate(-100.f, 100.f), 1e-6);
  EXPECT_NEAR(0.0398278, lookup.integrate(0.f), 1e-4);
}

TEST(integralLookup2D, values){
  Gaussian2f gauss(Gaussian2f::InputValue(0.f, 0.f), Gaussian2f::Covariance::Identity());
  IntegralLookup2D<float> lookup(&gauss, 
				 IntegralLookup2D<float>::InputValue(-25.f, -25.f),
				 IntegralLookup2D<float>::InputValue(25.f, 25.f),
				 1e-1);
  EXPECT_NEAR(1.f, 
	      lookup.integrate(IntegralLookup2D<float>::InputValue(-25.f, -25.f),
			       IntegralLookup2D<float>::InputValue(25.f, 25.f)),
	      5e-3);
  EXPECT_NEAR(0.00158626, lookup.integrate(IntegralLookup2D<float>::InputValue(0.f, 0.f)), 1e-4);
}

TEST(gaussianLookup1D, numberOfIntervalls){
  GaussianLookup1D<float> lookup(1.f, 2.f, size_t(120));
  lookup.setGaussianParameters(0.f, 1.f);
  EXPECT_NEAR(1.f, lookup.integrate(-6.f, 6.f), 1e-6);
  EXPECT_NEAR(1.f, lookup.integrate(-7.f, 7.f), 1e-6);
  EXPECT_NEAR(0.0398278, lookup.integrate(0.f), 1e-4);
}


TEST(gaussianLookup2D, numberOfIntervalls){
  GaussianLookup2D<float> lookup(Gaussian2f::InputValue(1.f, 1.f), 2.f*Gaussian2f::Covariance::Identity(), size_t(120));
  lookup.setGaussianParameters(Gaussian2f::InputValue(0.f, 0.f), Gaussian2f::Covariance::Identity());
  EXPECT_NEAR(1.f, lookup.integrate(Gaussian2f::InputValue(-6.f, -6.f),
				    Gaussian2f::InputValue(6.f, 6.f)), 
	      5e-3);
  EXPECT_NEAR(1.f, lookup.integrate(Gaussian2f::InputValue(-7.f, -7.f),
				    Gaussian2f::InputValue(7.f, 7.f)), 
	      5e-3);
  EXPECT_NEAR(0.00158626, lookup.integrate(Gaussian2f::InputValue(0.f, 0.f)), 1e-4);
}

TEST(gaussianLookup1D, intervallSize){
  GaussianLookup1D<float> lookup(1.f, 2.f, float(1e-1));
  lookup.setGaussianParameters(0.f, 1.f, false);
  EXPECT_NEAR(1.f, lookup.integrate(-6.f, 6.f), 1e-6);
  EXPECT_NEAR(1.f, lookup.integrate(-7.f, 7.f), 1e-6);
  EXPECT_NEAR(0.0398278, lookup.integrate(0.f), 1e-4);
}


TEST(gaussianLookup2D, intervallSize){
  GaussianLookup2D<float> lookup(Gaussian2f::InputValue(1.f, 1.f), 2.f*Gaussian2f::Covariance::Identity(), float(1e-1));
  lookup.setGaussianParameters(Gaussian2f::InputValue(0.f, 0.f), Gaussian2f::Covariance::Identity(), false);
  EXPECT_NEAR(1.f, lookup.integrate(Gaussian2f::InputValue(-6.f, -6.f),
				    Gaussian2f::InputValue(6.f, 6.f)), 
	      5e-3);
  EXPECT_NEAR(1.f, lookup.integrate(Gaussian2f::InputValue(-7.f, -7.f),
				    Gaussian2f::InputValue(7.f, 7.f)), 
	      5e-3);
  EXPECT_NEAR(0.00158626, lookup.integrate(Gaussian2f::InputValue(0.f, 0.f)), 1e-4);
}

TEST(expForGaussian, values){
  for(double x= -11.f; x <= 0.f; x+=1e-1){
    EXPECT_NEAR(exp(x), ExpForGaussian::expLookup(x), 1e-4);
  }
}

TEST(gaussian2, values){
  Gaussian2<1> gaussian;
  boost::math::normal_distribution<double> expectedGaussian;
  double expected, test;
  for(double x=-10.0; x <= 10.0; x+=1e-2){
    expected = boost::math::pdf(expectedGaussian,x);
    test = gaussian(x);
    EXPECT_NEAR(expected, test, 1e-4);
  }

  Gaussian2<1> gaussian2(0.0, 400.0);
  boost::math::normal_distribution<double> expectedGaussian2(0.0, 20.0);
  for(double x=-30.0; x <= 30.0; x+=1e-2){
    EXPECT_NEAR(boost::math::pdf(expectedGaussian2,x), gaussian2(x), 1e-4);
  }
}

TEST(gaussian2, integral){
  Gaussian2<1> gaussian;
  IntegralOverFunction<double,1> integral(&gaussian, 1e-2);
  EXPECT_NEAR(1.0, integral.integrate(-10.0, 10.0), 1e-5);

  Gaussian2<1> gaussian2(0.0, 400.0);
  IntegralOverFunction<double,1> integral2(&gaussian2, 1e-2);
  EXPECT_NEAR(1.0, integral2.integrate(-200.0, 200.0), 1e-5);
}

TEST(gaussian2, time){
  Gaussian2<1> gaussian;
  boost::math::normal_distribution<double> expectedGaussian;
  boost::posix_time::ptime startBoost(boost::posix_time::microsec_clock::local_time());
  for(double x=-10.0; x <= 10.0; x+=1e-4){
    boost::math::pdf(expectedGaussian,x);
  }
  boost::posix_time::ptime endBoost(boost::posix_time::microsec_clock::local_time());
  boost::posix_time::time_duration durationBoost(endBoost - startBoost);
  
  boost::posix_time::ptime start(boost::posix_time::microsec_clock::local_time());
  for(double x=-10.0; x <= 10.0; x+=1e-4){
    gaussian(x);   
  }   
  boost::posix_time::ptime end(boost::posix_time::microsec_clock::local_time());
  boost::posix_time::time_duration duration(end - start);
  
  std::cout << "custom: " << duration << ", boost: " << durationBoost << std::endl;
  if(duration > durationBoost){
    std::cout << "custom look up is slower than boost!" << std::endl;
  }
  EXPECT_GT(durationBoost, duration);
}

TEST(gaussianIntegralLookup1D, values){
  GaussianLookup2_1D gaussianIntegral(0.f, 1.f, 1e-4);
  EXPECT_NEAR(1.f, gaussianIntegral.integrate(-6.f, 6.f), 1e-5);
  //EXPECT_NEAR(0.0398278, gaussianIntegral.integrate(0.f), 1e-4);
}

TEST(gaussianIntegralLookup2D, values){
  GaussianLookup2_2D gaussianIntegral(GaussianLookup2_2D::InputValue(0., 0.), 
				      GaussianLookup2_2D::Covariance::Identity(),
				      1e-1);
  EXPECT_NEAR(1., 
	      gaussianIntegral.integrate(GaussianLookup2_2D::InputValue(-6., -6.),
					 GaussianLookup2_2D::InputValue(6., 6.)),
	      1e-3);
  //EXPECT_NEAR(0.00158626, gaussianIntegral.integrate(GaussianLookup2_2D::InputValue(0.0, 0.0)), 1e-4);
}

TEST(gaussianIntegralLookup1D, copy){
  GaussianLookup2_1D* gaussianIntegral = new GaussianLookup2_1D(0.f, 1.f, 1e-4);

  GaussianLookup2_1D gaussianIntegral2(*gaussianIntegral);
  delete gaussianIntegral;
  EXPECT_NEAR(1.f, gaussianIntegral2.integrate(-6.f, 6.f), 1e-5);

  gaussianIntegral = new GaussianLookup2_1D(0.f, 1.f, 1e-4);
  gaussianIntegral2 = *gaussianIntegral;
  delete gaussianIntegral;
  EXPECT_NEAR(1.f, gaussianIntegral2.integrate(-6.f, 6.f), 1e-5);
  //EXPECT_NEAR(1.f, gaussianIntegral2.integrate(0.0), 1e-5);
}

TEST(gaussianIntegralLookup2D, copy){
  GaussianLookup2_2D* gaussianIntegral = new GaussianLookup2_2D(GaussianLookup2_2D::InputValue(0., 0.), 
								GaussianLookup2_2D::Covariance::Identity(),
								1e-1);
  GaussianLookup2_2D gaussianIntegral2(*gaussianIntegral);
  delete gaussianIntegral;
  EXPECT_NEAR(1., 
	      gaussianIntegral2.integrate(GaussianLookup2_2D::InputValue(-6., -6.),
					  GaussianLookup2_2D::InputValue(6., 6.)),
	      1e-3);
  gaussianIntegral = new GaussianLookup2_2D(GaussianLookup2_2D::InputValue(0., 0.), 
					    GaussianLookup2_2D::Covariance::Identity(),
					    1e-1);
  gaussianIntegral2 = *gaussianIntegral;
  delete gaussianIntegral;
  EXPECT_NEAR(1., 
  	      gaussianIntegral2.integrate(GaussianLookup2_2D::InputValue(-6., -6.),
					  GaussianLookup2_2D::InputValue(6., 6.)),
  	      1e-3);
  //EXPECT_NEAR(1., 
  //	      gaussianIntegral2.integrate(GaussianLookup2_2D::InputValue(0.0, 0.0)),
  //	      1e-3);
}
