#include <iostream>

template <typename ReturnType> ReturnType Tools::ProgramOptions::get(const std::string& valueName) const{
  if(_mainOptions.find(valueName) != _mainOptions.end()){
    return _mainOptions[valueName].as<ReturnType>();
  }

  // check for options without default value
  bool unsetOption = false;
  for(size_t i = 0; i < _optionsWithoutDefaultValue.size(); ++i){
    if(valueName.compare(_optionsWithoutDefaultValue[i]) == 0){
      // value was not set, but is required
      std::cout << "ERROR: requesting " << valueName << ": option value was not set" << std::endl;
      unsetOption = true;
    }
  }

  if(!unsetOption){
    // options is unknown
    std::cout << "ERROR: unrecognized option " << valueName << std::endl;
  }
  return ReturnType();
}

