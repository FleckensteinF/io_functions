#ifndef _TOOLS_INTEGRAL_GAUSSIAN_LOOKUP2_H_
#define _TOOLS_INTEGRAL_GAUSSIAN_LOOKUP2_H_

#include "integral.h"
#include "math_functions/gaussian_lookup.h"

namespace Tools{
  namespace Integral{
    class GaussianLookup2_1D{
    public:
      typedef IntegralOverFunction<double, 1> IntegralType;
      typedef typename IntegralType::InputValue InputValue;
      typedef Functions::Gaussian2<1> FunctionType;
      typedef typename FunctionType::Covariance Variance;
      GaussianLookup2_1D(const InputValue& mean, const Variance& variance, const double& intervallSize);
      GaussianLookup2_1D(const GaussianLookup2_1D& other);
      GaussianLookup2_1D& operator=(const GaussianLookup2_1D& other);

      double integrate(const InputValue& minValue, const InputValue& maxValue) const;
      double integrate(const InputValue& value) const;

      // parameter access
      const InputValue& mean() const;
      const Variance& variance() const;
      const double& intervallSize() const;
    private:
      FunctionType _gaussian;
      IntegralType _integral;
    };

    class GaussianLookup2_2D{
    public:
      typedef IntegralOverFunction<double, 2> IntegralType;
      typedef typename IntegralType::InputValue InputValue;
      typedef Functions::Gaussian2<2> FunctionType;
      typedef typename FunctionType::Covariance Covariance;
      GaussianLookup2_2D(const InputValue& mean, const Covariance& covariance, const double& intervallSize);
      GaussianLookup2_2D(const GaussianLookup2_2D& other);
      GaussianLookup2_2D& operator=(const GaussianLookup2_2D& other);

      double integrate(const InputValue& minValue, const InputValue& maxValue) const;
      double integrate(const InputValue& value) const;

      // parameter access
      const InputValue& mean() const;
      const Covariance& covariance() const;
      const double& intervallSize() const;
    private:
      FunctionType _gaussian;
      IntegralType _integral;
      InputValue stddev(const Covariance& covariance) const;
    };
  };
};

#endif // _TOOLS_INTEGRAL_GAUSSIAN_LOOKUP2_H_
