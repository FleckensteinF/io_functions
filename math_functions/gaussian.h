#ifndef _TOOLS_FUNCTIONS_GAUSSIAN_H_
#define _TOOLS_FUNCTIONS_GAUSSIAN_H_

#include "function.h"

namespace Tools{
  namespace Functions{
    template<class Numeric, size_t dim>
      class Gaussian : public Function<Numeric, dim, 1>{
    public:
      typedef typename Function<Numeric, dim, 1>::InputValue InputValue;
      typedef typename Function<Numeric, dim, 1>::OutputValue OutputValue;
      typedef Eigen::Matrix<Numeric, dim, dim> Covariance;
      Gaussian(const InputValue& mean, const Covariance& covariance);
      OutputValue operator()(const InputValue& x) const;

      // access members
      const InputValue& mean() const;
      const Covariance& covariance() const;

    private:
      InputValue _mean;
      Covariance _covariance, _covarianceInverse;
      Numeric _prefactor;
    };

    template<class Numeric>
      class Gaussian<Numeric, 1> : public Function<Numeric, 1, 1>{
    public:
      typedef typename Function<Numeric, 1, 1>::InputValue InputValue;
      typedef typename Function<Numeric, 1, 1>::OutputValue OutputValue;
      typedef Numeric Variance;
      Gaussian(const InputValue& mean, const Variance& variance);
      OutputValue operator()(const InputValue& x) const;

      // access members
      const InputValue& mean() const;
      const Variance& variance() const;
    private:
      InputValue _mean;
      Variance _variance, _varianceInverse;
      Numeric _prefactor;
    };
    typedef Gaussian<float, 1> Gaussian1f;
    typedef Gaussian<float, 2> Gaussian2f;
    typedef Gaussian<double, 1> Gaussian1d;
    typedef Gaussian<double, 2> Gaussian2d;

  };
};

#include "gaussian.hpp"

#endif // _TOOLS_FUNCTIONS_GAUSSIAN_H_
