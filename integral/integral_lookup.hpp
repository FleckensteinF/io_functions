template<class Numeric>
Tools::Integral::IntegralLookup1D<Numeric>::IntegralLookup1D(FunctionType const* function,  const InputValue& minValue, const InputValue& maxValue, const Numeric& intervallSize) :
  IntegralOverFunction<Numeric, 1>(function, intervallSize)
  , _minValue(1.0)
  , _maxValue(0.0)
  , _factor(1.0/intervallSize)
  , _offset(minValue)
{
  computeTable(minValue, maxValue, intervallSize);
}

template<class Numeric>
Numeric Tools::Integral::IntegralLookup1D<Numeric>::integrate(const InputValue& minValue, const InputValue& maxValue) const{
  Numeric result = 0.0;
  if(_table.empty()){
    return result;
  }

  Numeric intervallSize = IntegralOverFunction<Numeric, 1>::_intervallSize;
  for(Numeric x = minValue; x <= maxValue-intervallSize; x += intervallSize){
    result += integrate(x);
  }
  return result;
}

template<class Numeric>
Numeric Tools::Integral::IntegralLookup1D<Numeric>::integrate(const InputValue& value) const{
  if(_table.empty()){
    return 0.0;
  }
  int index = toGrid(value);
  if(index < 0){
    return _table.front();
  }
  if(index >= _table.size()){
    return _table.back();
  }
  return _table[index];  
}

template<class Numeric>
Numeric Tools::Integral::IntegralLookup1D<Numeric>::intervallSize() const{
  return IntegralOverFunction<Numeric, 1>::_intervallSize;
}

template<class Numeric>
size_t Tools::Integral::IntegralLookup1D<Numeric>::numberOfIntervalls() const{
  return _table.size();
}

template<class Numeric>
void Tools::Integral::IntegralLookup1D<Numeric>::setFunctionPointer(FunctionType const* function){
  this->_function = function;
}

template<class Numeric>
int Tools::Integral::IntegralLookup1D<Numeric>::toGrid(const InputValue& value) const{
  return int(_factor*(value-_offset));
}

template<class Numeric>
void Tools::Integral::IntegralLookup1D<Numeric>::computeTable(const InputValue& minValue, const InputValue& maxValue, const Numeric& intervallSize){
  _minValue = 1.0;
  _maxValue = 0.0;
  _factor = 1.0/intervallSize;
  _offset = minValue;
  Numeric x;
  _table.clear();
  for(x = _offset; x <= maxValue-intervallSize; x += intervallSize){
    _table.push_back(IntegralOverFunction<Numeric, 1>::integrate(x, x+intervallSize));
    _minValue = std::min(_minValue, _table.back());
    _maxValue = std::max(_maxValue, _table.back());
  }
  std::cout << "constructed integral look up with values from " << _minValue << " to " << _maxValue << std::endl;
}

template<class Numeric>
Tools::Integral::IntegralLookup2D<Numeric>::IntegralLookup2D(FunctionType const* function,  const InputValue& minValue, const InputValue& maxValue, const Numeric& intervallSize) : 
  IntegralOverFunction<Numeric, 2>(function, intervallSize)
  , _minValue(1.0)
  , _maxValue(0.0)
  , _factor(1.0/intervallSize)
  , _offset(minValue)
{
  computeTable(minValue, maxValue, intervallSize);
}

template<class Numeric>
Numeric Tools::Integral::IntegralLookup2D<Numeric>::integrate(const InputValue& minValue, const InputValue& maxValue) const{
  Numeric result = 0.0;
  if(_table.empty() || _table.front().empty()){
    return result;
  }

  Numeric intervallSize = IntegralOverFunction<Numeric, 2>::_intervallSize;
  for(Numeric x = minValue.x(); x <= maxValue.x()-intervallSize; x += intervallSize){
    for(Numeric y = minValue.y(); y <= maxValue.y()-intervallSize; y += intervallSize){
      result += integrate(InputValue(x, y));
    }
  }
  return result;
}

template<class Numeric>
Numeric Tools::Integral::IntegralLookup2D<Numeric>::integrate(const InputValue& value) const{
  if(_table.empty() || _table.front().empty()){
    return 0.0;
  }
  Index index = toGrid(value);
  std::vector<Numeric> const* vecToUse;
  if(index.x() < 0){
    vecToUse = &_table.front();
  }else if(index.x() >= _table.size()){
    vecToUse = &_table.back();
  }else{
    vecToUse = &_table[index.x()];
  }

  if(vecToUse->empty()){
    return 0.0;
  }

  if(index.y() < 0){
    return vecToUse->front();
  }
  if(index.y() >= vecToUse->size()){
    return vecToUse->back();
  }
  return (*vecToUse)[index.y()];
}

template<class Numeric>
Numeric Tools::Integral::IntegralLookup2D<Numeric>::intervallSize() const{
  return IntegralOverFunction<Numeric, 2>::_intervallSize;
}

template<class Numeric>
size_t Tools::Integral::IntegralLookup2D<Numeric>::numberOfIntervalls() const{
  if(_table.empty() || _table.front().empty()){
    return 0;
  }
  return std::min(_table.size(), _table.front().size());
}

template<class Numeric>
void Tools::Integral::IntegralLookup2D<Numeric>::setFunctionPointer(FunctionType const* function){
  this->_function = function;
}

template<class Numeric>
typename Tools::Integral::IntegralLookup2D<Numeric>::Index Tools::Integral::IntegralLookup2D<Numeric>::toGrid(const InputValue& value) const{
  InputValue buff = _factor*(value-_offset);
  return Index(buff.x(), buff.y());
}

template<class Numeric>
void Tools::Integral::IntegralLookup2D<Numeric>::computeTable(const InputValue& minValue, const InputValue& maxValue, const Numeric& intervallSize){
  _minValue = 1.0;
  _maxValue = 0.0;
  _factor = 1.0/intervallSize;
  _offset = minValue;
  _table.clear();
  Numeric x, y;
  InputValue min, max;
  for(x = _offset.x(); x <=maxValue.x()-intervallSize; x += intervallSize){
    _table.push_back(std::vector<Numeric>());
    for(y = _offset.y(); y <=maxValue.y()-intervallSize; y += intervallSize){
      min = InputValue(x, y);
      max = InputValue(x+intervallSize, y+intervallSize);
      _table.back().push_back(IntegralOverFunction<Numeric, 2>::integrate(min, max));
      _minValue = std::min(_table.back().back(), _minValue);
      _maxValue = std::max(_table.back().back(), _maxValue);
    }
  }
  std::cout << "constructed integral look up with values from " << _minValue << " to " << _maxValue << std::endl;
}
