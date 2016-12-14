#include <Eigen/Geometry>

template<class Numeric, size_t dim>
Tools::Functions::Gaussian<Numeric, dim>::Gaussian(const InputValue& mean, const Covariance& covariance) :
  _mean(mean)
  , _covariance(covariance)
{
  Numeric pot = 1.0;
  Numeric mult = 2*M_PI;
  for(size_t i = 0; i < dim; ++i){
    pot *= mult;
  }
  _prefactor = 1.0/sqrt(pot*_covariance.determinant());
  _covarianceInverse = _covariance.inverse();
}

template<class Numeric, size_t dim>
typename Tools::Functions::Gaussian<Numeric, dim>::OutputValue Tools::Functions::Gaussian<Numeric, dim>::operator()(const InputValue& x) const{
  InputValue diff =  x - _mean;
  return OutputValue(_prefactor*exp(-0.5*diff.transpose()*_covarianceInverse*diff));
}

template<class Numeric, size_t dim>
const typename Tools::Functions::Gaussian<Numeric, dim>::InputValue& Tools::Functions::Gaussian<Numeric, dim>::mean() const{
  return _mean;
}

template<class Numeric, size_t dim>
const typename Tools::Functions::Gaussian<Numeric, dim>::Covariance& Tools::Functions::Gaussian<Numeric, dim>::covariance() const{
  return _covariance;
}

template<class Numeric>
Tools::Functions::Gaussian<Numeric, 1>::Gaussian(const InputValue& mean, const Variance& variance) :
  _mean(mean)
  , _variance(variance)
  , _varianceInverse(1.0/variance)
  , _prefactor(1.0/sqrt(2*M_PI*variance))
{
}

template<class Numeric>
typename Tools::Functions::Gaussian<Numeric, 1>::OutputValue Tools::Functions::Gaussian<Numeric, 1>::operator()(const InputValue& x) const{
  InputValue diff =  x - _mean;
  return OutputValue(_prefactor*exp(-0.5*_varianceInverse*diff*diff));
}

template<class Numeric>
const typename Tools::Functions::Gaussian<Numeric, 1>::InputValue& Tools::Functions::Gaussian<Numeric, 1>::mean() const{
  return _mean;
}

template<class Numeric>
const typename Tools::Functions::Gaussian<Numeric, 1>::Variance& Tools::Functions::Gaussian<Numeric, 1>::variance() const{
  return _variance;
}
