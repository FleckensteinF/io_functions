#include <Eigen/Geometry>

template<size_t dim>
Tools::Functions::Gaussian2<dim>::Gaussian2(const Mean& meanV, const Covariance& covarianceV) :
  _mean(meanV)
  , _covariance(covarianceV)
  , _covarianceInverse(_covariance.inverse())
  , _prefactor(prefactor())
{
}

template<size_t dim>
typename Tools::Functions::Gaussian2<dim>::FunctionType::OutputValue Tools::Functions::Gaussian2<dim>::operator()(const typename FunctionType::InputValue& x) const{
  Mean diff = x - _mean;
  return _prefactor*ExpForGaussian::expLookup(-0.5*diff.transpose()*_covarianceInverse*diff);
}

template<size_t dim>
const typename Tools::Functions::Gaussian2<dim>::Mean& Tools::Functions::Gaussian2<dim>::mean() const{
  return _mean;
}

template<size_t dim>
const typename Tools::Functions::Gaussian2<dim>::Covariance& Tools::Functions::Gaussian2<dim>::covariance() const{
  return _covariance;
}

template<size_t dim>
double Tools::Functions::Gaussian2<dim>::prefactor() const{
  double pot = 1.0;
  double mult = 2*M_PI;
  for(size_t i = 0; i < dim; ++i){
    pot *= mult;
  }
  return 1.0/sqrt(pot*_covariance.determinant());
}
