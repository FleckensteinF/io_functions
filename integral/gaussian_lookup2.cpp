#include "gaussian_lookup2.h"

Tools::Integral::GaussianLookup2_1D::GaussianLookup2_1D(const InputValue& mean, const Variance& variance, const double& intervallSize) : 
  _gaussian(FunctionType(mean, variance))
  , _integral(IntegralType(&_gaussian, intervallSize))
{
}

Tools::Integral::GaussianLookup2_1D::GaussianLookup2_1D(const GaussianLookup2_1D& other) : 
  _gaussian(other._gaussian)
  , _integral(IntegralType(&_gaussian, other.intervallSize()))
{
}

Tools::Integral::GaussianLookup2_1D& Tools::Integral::GaussianLookup2_1D::operator=(const GaussianLookup2_1D& other){
  _gaussian = other._gaussian;
  _integral = IntegralType(&_gaussian, other.intervallSize());
  return *this;
}

double Tools::Integral::GaussianLookup2_1D::integrate(const InputValue& minValue, const InputValue& maxValue) const{
  return _integral.integrate(minValue, maxValue);
}

double Tools::Integral::GaussianLookup2_1D::integrate(const InputValue& value) const{
  return _integral.integrate(value-0.5*_integral.intervallSize(), value+0.5*_integral.intervallSize());
}

const Tools::Integral::GaussianLookup2_1D::InputValue& Tools::Integral::GaussianLookup2_1D::mean() const{
  return _gaussian.mean();
}

const Tools::Integral::GaussianLookup2_1D::Variance& Tools::Integral::GaussianLookup2_1D::variance() const{
  return _gaussian.covariance();
}

const double& Tools::Integral::GaussianLookup2_1D::intervallSize() const{
  return _integral.intervallSize();
}

Tools::Integral::GaussianLookup2_2D::GaussianLookup2_2D(const InputValue& mean, const Covariance& covariance, const double& intervallSize) : 
  _gaussian(FunctionType(mean, covariance))
  , _integral(IntegralType(&_gaussian, intervallSize))
{
}

Tools::Integral::GaussianLookup2_2D::GaussianLookup2_2D(const GaussianLookup2_2D& other) : 
  _gaussian(other._gaussian)
  , _integral(IntegralType(&_gaussian, other.intervallSize()))
{
}

Tools::Integral::GaussianLookup2_2D& Tools::Integral::GaussianLookup2_2D::operator=(const GaussianLookup2_2D& other){
  _gaussian = other._gaussian;
  _integral = IntegralType(&_gaussian, other.intervallSize());
  return *this;
}

double Tools::Integral::GaussianLookup2_2D::integrate(const InputValue& minValue, const InputValue& maxValue) const{
  return _integral.integrate(minValue, maxValue);
}

double Tools::Integral::GaussianLookup2_2D::integrate(const InputValue& value) const{
  return _integral.integrate(value-0.5*_integral.intervallSize()*InputValue::Ones(), value+0.5*_integral.intervallSize()*InputValue::Ones());
}

const Tools::Integral::GaussianLookup2_2D::InputValue& Tools::Integral::GaussianLookup2_2D::mean() const{
  return _gaussian.mean();
}

const Tools::Integral::GaussianLookup2_2D::Covariance& Tools::Integral::GaussianLookup2_2D::covariance() const{
  return _gaussian.covariance();
}

const double& Tools::Integral::GaussianLookup2_2D::intervallSize() const{
  return _integral.intervallSize();
}

Tools::Integral::GaussianLookup2_2D::InputValue Tools::Integral::GaussianLookup2_2D::stddev(const Covariance& covariance) const{
  InputValue stddev = covariance.diagonal();
  stddev.x() = sqrt(stddev.x());
  stddev.y() = sqrt(stddev.y());
  return stddev;  
}

