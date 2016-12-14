#include "exp_lookup.h"

#include <iostream>

Tools::Functions::ExpForGaussian::ExpForGaussian(){
  // compute look up values
  // from -10 to 0
  FunctionLookup<double>::_minX = double(-10);
  FunctionLookup<double>::_maxX = double(0);
  FunctionLookup<double>::_intervallSize = double(1e-7);
  FunctionLookup<double>::_intervallSizeInverse = double(1.0)/FunctionLookup<double>::_intervallSize;

  std::cout << "Tools::Function::ExpForGaussian:" << std::endl;
  std::cout << "intervall size: " << FunctionLookup<double>::_intervallSize << std::endl;

  double min = FunctionLookup<double>::_minX;
  double max = FunctionLookup<double>::_maxX;
  double iSize = FunctionLookup<double>::_intervallSize;
  double iSizeInverse = 1.0/iSize;
  _values.resize(ceil((max-min)*iSizeInverse)+1, 0.0);

# pragma omp parallel for
  for(size_t i = 1; i < _values.size(); ++i){
    _values[i] = exp(min+(i-1)*iSize);
  }

  //double minVal = 1.0;
  //double maxVal = 0.0;
  //for(size_t i = 0; i < _values.size(); ++i){
  //  minVal = std::min(_values[i], minVal);
  //  maxVal = std::max(_values[i], maxVal);
  //}
  //std::cout << "values between: " << minVal << " and " << maxVal << std::endl;
}

Tools::Functions::ExpForGaussian Tools::Functions::ExpForGaussian::expLookup = Tools::Functions::ExpForGaussian();
