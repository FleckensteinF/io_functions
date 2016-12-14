#ifndef _TOOLS_FUNCTIONS_GAUSSIAN_LOOKUP_H_
#define _TOOLS_FUNCTIONS_GAUSSIAN_LOOKUP_H_

#include "exp_lookup.h"

namespace Tools{
  namespace Functions{
    template<size_t dim>
      class Gaussian2 : public Function<double, dim, 1>{
    public:
      typedef Function<double, dim, 1> FunctionType;
      typedef typename FunctionType::InputValue Mean;
      typedef Eigen::Matrix<double, dim, dim> Covariance;
      Gaussian2(const Mean& mean, const Covariance& covariance=Covariance::Identity());
      virtual ~Gaussian2(){};
      virtual typename FunctionType::OutputValue operator()(const typename FunctionType::InputValue& x) const;

      // member access
      const Mean& mean() const;
      const Covariance& covariance() const;
    private:
      static ExpForGaussian _expLookup;
      Mean _mean;
      Covariance _covariance, _covarianceInverse;
      double _prefactor;
      double prefactor() const;
    };
    template<>
      class Gaussian2<1> : public Function<double, 1, 1>{
    public:
      typedef Function<double, 1, 1> FunctionType;
      typedef typename FunctionType::InputValue Mean;
      typedef double Covariance;
      Gaussian2(const Mean& mean=0.0, const Covariance& covariance=1.0);
      virtual ~Gaussian2(){};
      virtual typename FunctionType::OutputValue operator()(const typename FunctionType::InputValue& x) const;

      // member access
      const Mean& mean() const;
      const Covariance& covariance() const;
    private:
      static ExpForGaussian _expLookup;
      Mean _mean;
      Covariance _covariance, _covarianceInverse;
      double _prefactor;
      double prefactor() const;
    };
  };
};

#include "gaussian_lookup.hpp"

#endif // _TOOLS_FUNCTION_GAUSSIAN_LOOKUP_H_
