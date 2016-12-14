template<class Numeric>
Tools::Integral::GaussianLookup1D<Numeric>::GaussianLookup1D(const InputValue& mean, const Variance& variance, const size_t& numberOfIntervalls) : 
  _gaussian(FunctionType(mean, variance))
  , _lookup(IntegralLookupType(&_gaussian, mean-6*sqrt(variance), mean+6*sqrt(variance), 12*sqrt(variance)/(1.0*numberOfIntervalls)))
{
  std::cout << "intervall size: " << _lookup.intervallSize() << " no intervalls " << _lookup.numberOfIntervalls() <<  std::endl;
}

template<class Numeric>
Tools::Integral::GaussianLookup1D<Numeric>::GaussianLookup1D(const InputValue& mean, const Variance& variance, const Numeric& intervallSize) : 
  _gaussian(FunctionType(mean, variance))
  , _lookup(IntegralLookupType(&_gaussian, mean-6*sqrt(variance), mean+6*sqrt(variance), intervallSize))
{
  std::cout << "intervall size: " << _lookup.intervallSize() << " no intervalls " << _lookup.numberOfIntervalls() <<  std::endl;
}

template<class Numeric>
Tools::Integral::GaussianLookup1D<Numeric>::GaussianLookup1D(const GaussianLookup1D& other) : 
  _gaussian(other._gaussian)
  , _lookup(other._lookup)
{
  _lookup.setFunctionPointer(&_gaussian);
}

template<class Numeric>
typename Tools::Integral::GaussianLookup1D<Numeric>::GaussianLookup1D& Tools::Integral::GaussianLookup1D<Numeric>::operator=(const GaussianLookup1D& other){
  _gaussian = other._gaussian;
  _lookup = other._lookup;
  _lookup.setFunctionPointer(&_gaussian);
  return *this;
}

template<class Numeric>
void Tools::Integral::GaussianLookup1D<Numeric>::setGaussianParameters(const InputValue& mean, const Variance& variance, bool useNumberOfIntervalls){
  _gaussian = FunctionType(mean, variance);
  if(useNumberOfIntervalls){
    _lookup = IntegralLookupType(&_gaussian, mean-6*sqrt(variance), mean+6*sqrt(variance), 12*sqrt(variance)/(1.0*_lookup.numberOfIntervalls()));
  }else{
    _lookup = IntegralLookupType(&_gaussian, mean-6*sqrt(variance), mean+6*sqrt(variance), _lookup.intervallSize());
  }
  std::cout << "intervall size: " << _lookup.intervallSize() << " no intervalls " << _lookup.numberOfIntervalls() <<  std::endl;
}

template<class Numeric>
Numeric Tools::Integral::GaussianLookup1D<Numeric>::integrate(const InputValue& minValue, const InputValue& maxValue) const{
  return _lookup.integrate(minValue, maxValue);
}

template<class Numeric>
Numeric Tools::Integral::GaussianLookup1D<Numeric>::integrate(const InputValue& value) const{
  return _lookup.integrate(value);
}

template<class Numeric>
const typename Tools::Integral::GaussianLookup1D<Numeric>::InputValue& Tools::Integral::GaussianLookup1D<Numeric>::mean() const{
  return _gaussian.mean();
}

template<class Numeric>
const typename Tools::Integral::GaussianLookup1D<Numeric>::Variance& Tools::Integral::GaussianLookup1D<Numeric>::variance() const{
  return _gaussian.variance();
}

template<class Numeric>
Numeric Tools::Integral::GaussianLookup1D<Numeric>::intervallSize() const{
  return _lookup.intervallSize();
}

template<class Numeric>
Tools::Integral::GaussianLookup2D<Numeric>::GaussianLookup2D(const InputValue& mean, const Covariance& covariance, const size_t& numberOfIntervallsIn1Dim) : 
  _gaussian(FunctionType(mean, covariance))
  , _lookup(IntegralLookupType(&_gaussian, mean-6*stddev(covariance), mean+6*stddev(covariance), 
			       12*std::min(stddev(covariance).x(), stddev(covariance).y())/(1.0*numberOfIntervallsIn1Dim)))
{
    std::cout << "intervall size: " << _lookup.intervallSize() << " no intervalls " << _lookup.numberOfIntervalls() <<  std::endl;
}

template<class Numeric>
Tools::Integral::GaussianLookup2D<Numeric>::GaussianLookup2D(const InputValue& mean, const Covariance& covariance, const Numeric& intervallSize) : 
  _gaussian(FunctionType(mean, covariance))
  , _lookup(IntegralLookupType(&_gaussian, mean-6*stddev(covariance), mean+6*stddev(covariance), intervallSize))
{
  std::cout << "intervall size: " << _lookup.intervallSize() << " no intervalls " << _lookup.numberOfIntervalls() <<  std::endl;
}

template<class Numeric>
Tools::Integral::GaussianLookup2D<Numeric>::GaussianLookup2D(const GaussianLookup2D& other) : 
  _gaussian(other._gaussian)
  , _lookup(other._lookup)
{
  _lookup.setFunctionPointer(&_gaussian);
}

template<class Numeric>
typename Tools::Integral::GaussianLookup2D<Numeric>::GaussianLookup2D& Tools::Integral::GaussianLookup2D<Numeric>::operator=(const GaussianLookup2D& other){
  _gaussian = other._gaussian;
  _lookup = other._lookup;
  _lookup.setFunctionPointer(&_gaussian);
  return *this;
}

template<class Numeric>
void Tools::Integral::GaussianLookup2D<Numeric>::setGaussianParameters(const InputValue& mean, const Covariance& covariance, bool useNumberOfINtervalls){
  _gaussian = FunctionType(mean, covariance);
  InputValue stddevValue = stddev(covariance);
  if(useNumberOfINtervalls){
    Numeric intervallSize = 12*std::min(stddevValue.x(), stddevValue.y())/(1.0*_lookup.numberOfIntervalls());
    _lookup = IntegralLookupType(&_gaussian, mean-6*stddevValue, mean+6*stddevValue, intervallSize);
  }else{
    _lookup = IntegralLookupType(&_gaussian, mean-6*stddevValue, mean+6*stddevValue, _lookup.intervallSize());
  }
  std::cout << "intervall size: " << _lookup.intervallSize() << " no intervalls " << _lookup.numberOfIntervalls() <<  std::endl;
}

template<class Numeric>
Numeric Tools::Integral::GaussianLookup2D<Numeric>::integrate(const InputValue& minValue, const InputValue& maxValue) const{
  return _lookup.integrate(minValue, maxValue);
}

template<class Numeric>
Numeric Tools::Integral::GaussianLookup2D<Numeric>::integrate(const InputValue& value) const{
  return _lookup.integrate(value);
}

template<class Numeric>
const typename Tools::Integral::GaussianLookup2D<Numeric>::InputValue& Tools::Integral::GaussianLookup2D<Numeric>::mean() const{
  return _gaussian.mean();
}

template<class Numeric>
const typename Tools::Integral::GaussianLookup2D<Numeric>::Covariance& Tools::Integral::GaussianLookup2D<Numeric>::covariance() const{
  return _gaussian.covariance();
}

template<class Numeric>
Numeric Tools::Integral::GaussianLookup2D<Numeric>::intervallSize() const{
  return _lookup.intervallSize();
}

template<class Numeric>
typename Tools::Integral::GaussianLookup2D<Numeric>::InputValue Tools::Integral::GaussianLookup2D<Numeric>::stddev(const Covariance& covariance) const{
  InputValue stddev = covariance.diagonal();
  stddev.x() = sqrt(stddev.x());
  stddev.y() = sqrt(stddev.y());
  return stddev;  
}

