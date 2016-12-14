#ifndef _TOOLS_INTEGRAL_GAUSSIAN_LOOKUP_H_
#define _TOOLS_INTEGRAL_GAUSSIAN_LOOKUP_H_

#include "integral_lookup.h"
#include "math_functions/gaussian.h"

namespace Tools{
  namespace Integral{

    template<class Numeric>
      class GaussianLookup1D{
    public:
      typedef IntegralLookup1D<Numeric> IntegralLookupType;
      typedef typename IntegralLookupType::InputValue InputValue;
      typedef Functions::Gaussian<Numeric, 1> FunctionType;
      typedef typename FunctionType::Variance Variance;
      GaussianLookup1D(const InputValue& mean, const Variance& variance, const Numeric& intervallSize);
      GaussianLookup1D(const InputValue& mean, const Variance& variance, const size_t& numberOfIntervalls);
      GaussianLookup1D(const GaussianLookup1D& other);
      GaussianLookup1D& operator=(const GaussianLookup1D& other);
      void setGaussianParameters(const InputValue& mean, const Variance& variance, bool useNumberOfINtervalls=true);

      Numeric integrate(const InputValue& minValue, const InputValue& maxValue) const;
      Numeric integrate(const InputValue& value) const;

      // parameter access
      const InputValue& mean() const;
      const Variance& variance() const;
      Numeric intervallSize() const;
    private:
      FunctionType _gaussian;
      IntegralLookupType _lookup;
    };

    template<class Numeric>
      class GaussianLookup2D{
    public:
      typedef IntegralLookup2D<Numeric> IntegralLookupType;
      typedef typename IntegralLookupType::InputValue InputValue;
      typedef Functions::Gaussian<Numeric, 2> FunctionType;
      typedef typename FunctionType::Covariance Covariance;
      GaussianLookup2D(const InputValue& mean, const Covariance& covariance, const Numeric& intervallSize);
      GaussianLookup2D(const InputValue& mean, const Covariance& covariance, const size_t& numberOfIntervallsIn1Dim);
      GaussianLookup2D(const GaussianLookup2D& other);
      GaussianLookup2D& operator=(const GaussianLookup2D& other);
      void setGaussianParameters(const InputValue& mean, const Covariance& covariance, bool useNumberOfINtervalls=true);

      Numeric integrate(const InputValue& minValue, const InputValue& maxValue) const;
      Numeric integrate(const InputValue& value) const;

      // parameter access
      const InputValue& mean() const;
      const Covariance& covariance() const;
      Numeric intervallSize() const;
    private:
      FunctionType _gaussian;
      IntegralLookupType _lookup;
      InputValue stddev(const Covariance& covariance) const;
    };

  };
};

#include "gaussian_lookup.hpp"

#endif // _TOOLS_INTEGRAL_GAUSSIAN_LOOKUP_H_
