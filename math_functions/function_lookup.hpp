template<class Numeric>
typename Tools::Functions::FunctionLookup<Numeric>::OutputValue Tools::Functions::FunctionLookup<Numeric>::operator()(const InputValue& x) const{
  if(_values.empty()){
    return OutputValue(0.0);
  }
  if(x <= _minX){
    return _values.front();
  }
  if(x >= _maxX){
    return _values.back();
  }
  return _values[(x-_minX)*_intervallSizeInverse];
}
