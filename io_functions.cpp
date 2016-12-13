#include "io_functions.h"

using namespace Tools;

bool IOFunctions::endsWith(const std::string& input, const std::string& ending){
  std::string back = input.substr(input.size()-ending.size(),ending.size());
  return ending.compare(back) == 0;
}

// helper function
// cut of at the last occurence of 'at'
// returns the back part of the cut, if back is true
// returns the front part otherwise
std::string cutOfAt(const std::string sequence, const char& at, const bool back){
  size_t index = sequence.find_last_of(at);

  if(back){
    return sequence.substr(index+1);
  }else{
    return sequence.substr(0,index);
  }
}

std::string IOFunctions::fileSuffix(const std::string& path){
  if(std::string::npos == path.find(".")){
    return "";
  } 
  return cutOfAt(path, '.', true);
}

std::string IOFunctions::fileName(const std::string& filePath){
  std::string result = cutOfAt(filePath, '/', true);
  return cutOfAt(result, '.', false);
}

std::string IOFunctions::containingFolderPathOf(const std::string& filePath){
  if(std::string::npos == filePath.find("/")){
    return "";
  }
  return cutOfAt(filePath, '/', false);
}

std::string IOFunctions::containingFolderOf(const std::string& filePath){
  std::string folderPath = containingFolderPathOf(filePath);
  return cutOfAt(folderPath, '/', true);
}

std::string IOFunctions::addTrailingSlash(const std::string& filePath){
  std::string result = filePath;
  if(filePath.back() != '/'){
    result = filePath+'/';
  }
  return result;
}

// load paths to  all files in directory 
bool IOFunctions::loadFilePathsFromDirectory(const std::string& directory, std::vector<std::string>& filePaths){
  // load the directory
  boost::filesystem::path folder;
  if(loadDirectory(directory, folder)){
    // an error occured
    std::cout << "ERROR in IOFunctions: cannot load file paths!" << std::endl;
    return true;
  }

  // iterate over directory and store file paths
  boost::filesystem::directory_iterator endIter;
  for(boost::filesystem::directory_iterator dirItr(folder); dirItr != endIter; ++dirItr){
    if(boost::filesystem::is_directory(*dirItr)){
      continue;
    }
    filePaths.push_back(dirItr->path().string());
  }
  std::sort(filePaths.begin(), filePaths.end());
  return false;
}

// load paths in directory 
bool IOFunctions::loadPathsFromDirectory(const std::string& directory, std::vector<std::string>& paths){
  // load the directory
  boost::filesystem::path folder;
  if(loadDirectory(directory, folder)){
    // an error occured
    std::cout << "ERROR in IOFunctions: cannot load file paths!" << std::endl;
    return true;
  }

  // iterate over directory and store file paths
  boost::filesystem::directory_iterator endIter;
  for(boost::filesystem::directory_iterator dirItr(folder); dirItr != endIter; ++dirItr){
    paths.push_back(dirItr->path().string());
  }
  std::sort(paths.begin(), paths.end());
  return false;
}

// loads directory with name directory
// returns true, if an error occured
// returns false otherwise
bool IOFunctions::loadDirectory(const std::string& directory, boost::filesystem::path& directoryPath){
  // load the directory with boost
  directoryPath = boost::filesystem::path(directory);
  //TODO: is the output at the correct position?
  if(boost::filesystem::exists(directoryPath) && boost::filesystem::is_directory(directoryPath)){
    return false;
  }
  std::cout << "ERROR in IOFunctions: given directoryPath \'" << directoryPath << "\' can not be loaded." << std::endl;
  std::cout << "Either it does not exist or it is not a directory!" << std::endl;
  return true;
}

// creates the directory if not already existent
void IOFunctions::loadMakeDirectory(const std::string& directory, boost::filesystem::path& directoryPath){
  // check, whether the directory already exists
  if(loadDirectory(directory, directoryPath)){
    std::cout << "--> creating new directory with name " << directory << std::endl;
    // create directory
    boost::filesystem::create_directory(directoryPath);
  }
}

void IOFunctions::loadMakeDirectory(const std::string& directory){
  boost::filesystem::path directoryPath;
  loadMakeDirectory(directory, directoryPath);
}

void IOFunctions::moveFile(const std::string& oldFilepath, const std::string& newFilepath){
  boost::filesystem::path oldPath(oldFilepath);
  if(!boost::filesystem::exists(oldFilepath)){
    return;
  }
  boost::filesystem::path newPath(newFilepath);
  if(boost::filesystem::exists(newFilepath)){
    boost::filesystem::remove(newFilepath);
  }
  boost::filesystem::rename(oldFilepath, newFilepath);
}

std::vector<std::string> IOFunctions::stringSplit(const std::string& str, const std::string& del){
  std::vector<std::string> split;
  std::string substr;
  if(del.size() > 0){
    size_t oldpos = 0;
    size_t newpos = 0;
    while(newpos < str.size() && oldpos <= newpos){
      oldpos = newpos;
      newpos = str.find(del, oldpos);
      substr = str.substr(oldpos, std::min(str.size(),newpos)-oldpos);
      if(substr.size() > 0){
	split.push_back(substr);
      }
      if(newpos < str.size()){
	newpos += del.size();
      }
    }
  }
  if(split.size() < 1){
    split.push_back(str);
  }
  return split; 
}

bool IOFunctions::fileNameCompare(const std::string& string1, const std::string& string2){
  std::string name1 = fileName(string1);
  std::string name2 = fileName(string2);

  return name2.compare(name1) == 0;
}

Tools::IOFunctions::FilenameCompare::FilenameCompare(const std::string& referenceValue) :
  referenceValue(referenceValue){
}

bool Tools::IOFunctions::FilenameCompare::operator() (const std::string &arg){
  return fileNameCompare(arg, referenceValue);
}
