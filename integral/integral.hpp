#include <iostream>

template<class Numeric> 
Numeric Tools::Integral::trapezArea(const Numeric& a, const Numeric& c, const Numeric&h){
  return 0.5*h*(a+c);
}

template<class Numeric> 
Numeric Tools::Integral::halfIntervalVolume(const Numeric (&functionValues)[3], const Numeric& intervallSize){
  static const Numeric factor = 1.0/3.0;
  Numeric min = std::min(std::min(functionValues[0], functionValues[1]), functionValues[2]);
  Numeric max = std::max(std::max(functionValues[0], functionValues[1]), functionValues[2]);
  Numeric mid = functionValues[0];
  for(size_t i = 1; i < 3; ++i){
    if(std::fabs(mid-max) >= std::numeric_limits<Numeric>::epsilon() || std::fabs(mid-min) >= std::numeric_limits<Numeric>::epsilon()){
      mid = functionValues[i];
    }
  }
  
  return 0.5*intervallSize*intervallSize*min+factor*trapezArea<Numeric>(mid-min, max-min, intervallSize)*intervallSize;
}

template<class Numeric, size_t dim>
Tools::Integral::IntegralBase<Numeric, dim>::IntegralBase(const Numeric& intervallSize) :
_intervallSize(std::fabs(intervallSize))
{

}

template<class Numeric, size_t dim>
const Numeric& Tools::Integral::IntegralBase<Numeric, dim>::intervallSize() const{
  return _intervallSize;
}

template<class Numeric>
Tools::Integral::IntegralBase<Numeric, 1>::IntegralBase(const Numeric& intervallSize) :
_intervallSize(std::fabs(intervallSize))
{

}

template<class Numeric>
const Numeric& Tools::Integral::IntegralBase<Numeric, 1>::intervallSize() const{
  return _intervallSize;
}

template<class Numeric, size_t dim>
Tools::Integral::IntegralOverFunction<Numeric, dim>::IntegralOverFunction(FunctionType const* function, const Numeric& intervallSize) :
  IntegralBase<Numeric, dim>(intervallSize)
  , _function(function)
{

}

template<class Numeric, size_t dim>
Numeric Tools::Integral::IntegralOverFunction<Numeric, dim>::integrate(const InputValue& /*minValue*/, const InputValue& /*maxValue*/) const{
  std::cout << "ERROR in Tools::Integral::IntegralOverFunction::integrate: no function implemented for dim > 2" << std::endl;
  return Numeric(0.0);
}

template<class Numeric>
Tools::Integral::IntegralOverFunction<Numeric, 1>::IntegralOverFunction(FunctionType const* function, const Numeric& intervallSize) :
  IntegralBase<Numeric, 1>(intervallSize)
  , _function(function)
{

}

template<class Numeric>
Numeric Tools::Integral::IntegralOverFunction<Numeric, 1>::integrate(const InputValue& minValue, const InputValue& maxValue) const{
  // iterate over intervall
  Numeric result = 0.0;
  Numeric i;
  Numeric intervallSize = IntegralBase<Numeric, 1>::_intervallSize;
  for(i = minValue; i < maxValue; i+=intervallSize){
    result += trapezArea<Numeric>((*_function)(i), (*_function)(i+intervallSize), intervallSize);
  }
  if(maxValue - i > 1e-3){
    result += trapezArea<Numeric>((*_function)(i), (*_function)(maxValue), maxValue-i);
  }
  return result;
}

template<class Numeric>
Tools::Integral::IntegralOverFunction<Numeric, 2>::IntegralOverFunction(FunctionType const* function, const Numeric& intervallSize) :
  IntegralBase<Numeric, 2>(intervallSize)
  , _function(function)
{
  
}

template<class Numeric>
Numeric Tools::Integral::IntegralOverFunction<Numeric, 2>::integrate(const InputValue& minValue, const InputValue& maxValue) const{
  Numeric intervallSize = IntegralBase<Numeric, 2>::_intervallSize*0.5;
  // compute border values
  int nX = floor((maxValue.x()-minValue.x())/intervallSize);
  int nY = floor((maxValue.y()-minValue.y())/intervallSize);
  if(nX <= 0 || nY <= 0){
    std::cout << "max: " << maxValue.transpose() << ", min: " << minValue.transpose() << ", intervall size: " << intervallSize << std::endl;
    // min and max value are turned around or too close
    // -> return 0.0
    std::cout << "ERROR in Tools::Integral::IntegralOverFunction::integrate: max and min values given in wrong order or too close!" << std::endl;
    return 0.0;
  }

  // compute, whats left until desired max value
  Numeric xRest = maxValue.x()-minValue.x() - nX*intervallSize;
  Numeric yRest = maxValue.y()-minValue.y() - nY*intervallSize;

  // iterate over intervalls to compute function values
  std::vector<std::vector<Numeric> > values(nX+2, std::vector<Numeric>(nY+2, Numeric(0.0)));
  for(int i = 0; i <= nX; ++i){
    for(int j = 0; j <= nY; ++j){
      values[i][j] = ((*_function)(minValue + intervallSize * typename FunctionType::InputValue(i,j)));
    }
    // y border values
    values[i][nY+1] = ((*_function)(typename FunctionType::InputValue(minValue.x() + i*intervallSize, maxValue.y())));
  }
  // x border values
  for(int j = 0; j <= nY; ++j){
    values[nX+1][j] = ((*_function)(minValue + intervallSize * typename FunctionType::InputValue(maxValue.x(), minValue.y() + j*intervallSize)));
  }
  values[nX+1][nY+1] = (*_function)(maxValue);

  // use values to compute volume
  Numeric result = 0.0;
  for(int x = 0; x < nX; ++x){
    for(int y = 0; y < nY; ++y){
      result += intervallVolume(values, x, y, intervallSize);
    }
    // y border value
    result += intervallVolume(values, x, nY, yRest);
  }

  // x border values
  for(int y = 0; y < nY; ++y){
    result += intervallVolume(values, nX, y, xRest);
  }
  result += intervallVolume(values, nX, nY, sqrt(xRest*yRest));

  return result;
}

template<class Numeric>
Numeric Tools::Integral::IntegralOverFunction<Numeric, 2>::intervallVolume(const std::vector<std::vector<Numeric> >& values, const size_t& x, const size_t& y, const Numeric& stepsize) const{
  Numeric result = 0.0;
  Numeric functionValues[3];
  functionValues[0] = values[x][y];
  functionValues[1] = values[x+1][y];
  functionValues[2] = values[x][y+1];
  result += halfIntervalVolume(functionValues, stepsize);
  functionValues[0] = values[x+1][y+1];
  result += halfIntervalVolume(functionValues, stepsize);
  return result;
}
