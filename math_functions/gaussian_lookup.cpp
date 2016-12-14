#include "gaussian_lookup.h"

Tools::Functions::Gaussian2<1>::Gaussian2(const Mean& meanV, const Covariance& covarianceV) :
  _mean(meanV)
  , _covariance(covarianceV)
  , _covarianceInverse(1.0/_covariance)
  , _prefactor(prefactor())
{
}

typename Tools::Functions::Gaussian2<1>::FunctionType::OutputValue Tools::Functions::Gaussian2<1>::operator()(const typename FunctionType::InputValue& x) const{
  Mean diff = x - _mean;
  return _prefactor*ExpForGaussian::expLookup(-0.5*diff*_covarianceInverse*diff);
}

const typename Tools::Functions::Gaussian2<1>::Mean& Tools::Functions::Gaussian2<1>::mean() const{
  return _mean;
}

const typename Tools::Functions::Gaussian2<1>::Covariance& Tools::Functions::Gaussian2<1>::covariance() const{
  return _covariance;
}

double Tools::Functions::Gaussian2<1>::prefactor() const{
  return 1.0/sqrt(2*M_PI*_covariance);
}
