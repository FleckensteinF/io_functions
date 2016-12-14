#include <iostream> 
#include <fstream>
#include <sstream>

using namespace Tools;

template<class T> std::string IOFunctions::toString(const T& t){
  std::stringstream stream;
  stream << t;
  return stream.str();
}

template<class T> T IOFunctions::fromString(const std::string& s){
  std::stringstream stream(s);
  T t;
  stream >> t;
  return t;
}

template <class EigenMatrix> 
EigenMatrix IOFunctions::fromVector(const std::vector<float>& input, const std::string& name){
  EigenMatrix result(EigenMatrix::Identity());
  size_t dim1 = result.rows();
  size_t dim2 = result.cols();
  if(input.size() != dim1*dim2){
    std::cerr << name << " size is " << input.size() << " instead of " << dim1*dim2 << ". " << std::endl;
    std::cout << "please enter correct dimension next time, using identity for now." << std::endl;
  }else{
    for(size_t i = 0; i < dim1; ++i){
      for(size_t j = 0; j < dim2; ++j){
  	result(i,j) = input[i*dim2 + j];
      }
    }
  }
  return result;
}

template <class EigenMatrix>
void IOFunctions::toVector(std::vector<float>& output, const EigenMatrix& input){
  size_t dim1 = input.rows();
  size_t dim2 = input.cols();
  output.resize(dim1*dim2, 0.f);
  toVector<EigenMatrix>(output.begin(), input);
}

template <class EigenMatrix>
void IOFunctions::toVector(std::vector<float>::iterator output, const EigenMatrix& input){
  size_t dim1 = input.rows();
  size_t dim2 = input.cols();
  for(size_t i = 0; i < dim1; ++i){
    for(size_t j = 0; j < dim2; ++j){
      *(output + i*dim2 + j) = input(i,j);
    }
  }  
}

template<class T> bool IOFunctions::writeToFile(const std::string& filepath, const std::vector<std::pair<std::string, std::vector<T> > >& input, const char& separator, const std::string& infoLine){
  std::ofstream output;
  output.open(filepath.c_str());
  if(!output.good()){
    std::cerr << "Error opening file " << filepath << "!" << std::endl;
    return true;
  }

  if(infoLine.compare("") != 0){
    output << infoLine << std::endl;
  }

  for(size_t i = 0; i < input.size(); ++i){
    output << input[i].first;
    if(!input[i].second.empty()){
      output << separator;
      for(int j = 0; j < int(input[i].second.size())-1; ++j){
	output << input[i].second[j] << separator;
      }
      output << input[i].second.back();
    }
    output << std::endl;
  }
  output.close();
#ifdef DEBUG
  std::cout << "wrote to file " << filepath << std::endl;
#endif
  return false;
};

template<class T> bool IOFunctions::writeToFile(const std::string& filepath, const std::vector<std::vector<T> >& input, const char& separator, const std::string& infoLine){
  std::vector<std::pair<std::string, std::vector<T> > > transformedInput;
  for(size_t i = 0; i < input.size(); ++i){
    if(input[i].size() == 0){
      // nothing to do
      // skiping this entry
      std::cout << "line " << i << " of given input is empty: skipping this line!" << std::endl; 
      continue;
    }
    std::pair<std::string, std::vector<T> > element;
    // store first element as string
    element.first = toString<T>(input[i][0]);
    for(size_t j = 1; j < input[i].size(); ++j){
      element.second.push_back(input[i][j]);
    }
    transformedInput.push_back(element);
  }
  return writeToFile<T>(filepath, transformedInput, separator, infoLine);
};

template<class T> bool IOFunctions::writeToFile(const std::string& filepath, const std::map<std::string, std::vector<T> >& input, const char& separator, const std::string& infoLine){
  std::vector<std::pair<std::string, std::vector<T> > > transformedInput;
  typename std::map<std::string, std::vector<T> >::const_iterator it;
  for(it = input.begin(); it != input.end(); ++it){
    std::pair<std::string, std::vector<T> > element;
    element.first = it->first;
    element.second = it->second;
    transformedInput.push_back(element);
  }
  return writeToFile<T>(filepath, transformedInput, separator, infoLine);
};

template<class T> bool IOFunctions::readFromFile(const std::string& filepath, std::vector<std::pair<std::string,std::vector<T> > >& result, const char& separator, std::string* infoLine){
  std::string line,buff,key;
  std::ifstream input;
  std::vector<T> elements;
  bool onlyKeyInLine = true;

  input.open(filepath.c_str()); 
  if(!input.good()){
    std::cerr << "Error opening file " << filepath << "!" << std::endl;
    return true;
  }
        
  if(infoLine){
    getline(input, *infoLine);
  }

  while(input.good()){
    getline(input, line);
    if(line.size() == 0){
      continue;
    }
    elements.clear();
    key = line;
    onlyKeyInLine = true;
    if(std::string::npos != line.find(separator)){
      onlyKeyInLine = false;
      key = line.substr(0, line.find(separator));
      line = line.substr(line.find(separator)+1);      
#ifdef DEBUG
      std::cout << "found key \'" << key << "\' with value "; 
      std::cout << line << std::endl;
#endif
    }
    while(std::string::npos != line.find(separator)){
      buff = line.substr(0, line.find(separator)); 
      line = line.substr(line.find(separator)+1);
      elements.push_back(fromString<T>(buff));
    }
    if(line.size() != 0 && !onlyKeyInLine){
      elements.push_back(fromString<T>(line));
    }
    //if(elements.size() != 0){ -> wrong! wanna also add lines with only one value = key
    result.push_back(std::pair<std::string,std::vector<T> >(key,elements));
    //}
  }
  input.close();
  return false;
}

template<class T> bool IOFunctions::readFromFile(const std::string& filepath, std::vector<std::vector<T> >& result, const char& separator, std::string* infoLine){
  std::vector<std::pair<std::string, std::vector<T> > > transformedResult;
  if(readFromFile<T>(filepath, transformedResult, separator, infoLine)){
    return true;
  }

  // transform into correct result format
  for(size_t i = 0; i < transformedResult.size(); ++i){
    std::vector<T> element;
    element.resize(transformedResult[i].second.size()+1);
    element[0] = fromString<T>(transformedResult[i].first);
#ifdef DEBUG
    if(i == 0){
      std::cout << "key=" << transformedResult[i].first << std::endl;
      std::cout << "elem0=" << element[0] << std::endl;
    } 
#endif
    for(size_t j = 0; j < transformedResult[i].second.size(); ++j){
      element[j+1] = transformedResult[i].second[j];
    }
    result.push_back(element);
  }
  return false;
}

template<class T> bool IOFunctions::readFromFile(const std::string& filepath, std::map<std::string,std::vector<T> >& result, const char& separator, std::string* infoLine){
  std::vector<std::pair<std::string, std::vector<T> > > transformedResult;
  if(readFromFile<T>(filepath, transformedResult, separator, infoLine)){
    return true;
  }

  // transform into correct result format
  for(size_t i = 0; i < transformedResult.size(); ++i){
    result[transformedResult[i].first] = transformedResult[i].second;
  }
  return false;
}
