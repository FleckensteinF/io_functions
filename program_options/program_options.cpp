#include "program_options.h"

#include <iostream>
#include <sstream>
#include <fstream>

using std::vector;
using std::string;
using boost::program_options::value;

using namespace Tools;

const string ProgramOptions::ModeParser::invalid = "INVALID";

ProgramOptions::ModeParser::ModeParser(const std::string& name, const std::string shortName, const std::string info,
				       const std::vector<std::vector<std::string> >& modeValues)
  : mode(invalid), _name(name), _shortName(shortName), _info(info),
    _modeValues(modeValues){
}
 
std::string ProgramOptions::ModeParser::getDescription() const{
  std::stringstream result;
  result << _name << " mode options: " << std::endl;
  for(size_t i = 0; i < _modeValues.size(); ++i){
    for(size_t j = 0; j < _modeValues[i].size()-1; ++j){
      result << _modeValues[i][j] << ", ";
    }
    if(!_modeValues[i].empty()){
      result << _modeValues[i].back();
    }
    result << std::endl;
  }
  return result.str();
}

void ProgramOptions::ModeParser::setMode(const std::string& modeString){
  bool foundMatch = false;
  //search for given modeString
#ifdef DEBUG
  std::cout << _name << ": looking for match to " << modeString << std::endl;
#endif
  for(size_t i = 0; i < _modeValues.size(); ++i){
    for(size_t j = 0; j < _modeValues[i].size(); ++j){
      if(_modeValues[i][j].compare(modeString) == 0){
	// strings match
	mode = _modeValues[i][0];
	foundMatch = true;
	break;
      }
    }
  }
  if(!foundMatch){
    mode = invalid;
  }
}

bool ProgramOptions::ModeParser::checkForInvalidValue() const{
  if(mode.compare(invalid) == 0){
    std::cout << "ERROR: mode of " << _name << " was set to " << mode << "!" << std::endl;
    std::cout << "please use instead: " << std::endl;
    std::cout << getDescription() << std::endl;
    return true;
  }
  return false;
}

std::string ProgramOptions::ModeParser::name() const{
  return _name;
}
std::string ProgramOptions::ModeParser::shortName() const{
  return _shortName;
}

std::string ProgramOptions::ModeParser::defaultValue() const{
  if(_modeValues.empty() || _modeValues[0].empty()){
    return invalid;
  }
  return _modeValues[0][0];
}

std::string ProgramOptions::ModeParser::info() const{
  return _info;
}

ProgramOptions::ProgramOptions(int argc, char** argv, std::vector<ModeParser> modeParsers, const bool init)
  : 
  configPath("configPath"),
  // other
  invalidMode(false),

  // mode parsers
  _modeParsers(modeParsers),

  // boost program options
  _configFileOptions("Configuration File Options"),
  _cmdLineOptions("CMD Line Options"){

  if(init){
    initialize(argc, argv);
  }
}

ProgramOptions::~ProgramOptions(){
}

std::string ProgramOptions::getMode(const std::string& valueName) const{
  if(_mainOptions.find(valueName) != _mainOptions.end()){
    for(size_t i = 0; i < _modeParsers.size(); ++i){
      if(valueName.compare(_modeParsers[i].name()) == 0){
	return _modeParsers[i].mode;
      }
    }
  }
  return ModeParser::invalid;
}

bool ProgramOptions::helpRequested() const{
  return _mainOptions.count("help");
}

std::string ProgramOptions::help(){
  invalidMode = true;
  std::stringstream helpStream;
  helpStream << _cmdLineOptions << std::endl;
  for(size_t i = 0; i < _modeParsers.size(); ++i){
    helpStream << _modeParsers[i].getDescription() << std::endl; 
  }
  return helpStream.str();
}

void ProgramOptions::initializeOptions(){
  _cmdLineOptions.add_options()
    ("help,h", "produce help message")
    ((configPath+",c").c_str(), value<string>()->default_value("main.config"), "set path for config file")
    ;
  _cmdLineOptions.add(_configFileOptions);
}

void ProgramOptions::initializeModeOptions(){
  for(size_t i = 0; i < _modeParsers.size(); ++i){
    _configFileOptions.add_options()
      ((_modeParsers[i].name()+","+_modeParsers[i].shortName()).c_str(), value<string>()->default_value(_modeParsers[i].defaultValue()), _modeParsers[i].info().c_str())
      ;  
  }
}

void ProgramOptions::parse(int argc, char** argv){
  // parse cmd line
  boost::program_options::store(boost::program_options::parse_command_line(argc, argv, _cmdLineOptions), _mainOptions);
  notify(_mainOptions);

  if(_mainOptions.count("help")){
    std::cout << help() << std::endl;
    invalidMode = true;
  }

  // check for config file path
  if(_mainOptions.count(configPath)){
    // look for file:
    std::ifstream configFile(_mainOptions[configPath].as<string>().c_str());
    if(configFile.is_open()){
      boost::program_options::store(boost::program_options::parse_config_file(configFile, _configFileOptions), _mainOptions);
      configFile.close();
      boost::program_options::notify(_mainOptions);
      std::cout << "parsed " << _mainOptions[configPath].as<string>() << std::endl;
      // parse command line again to overwrite config file options with command line options 
      boost::program_options::store(boost::program_options::parse_command_line(argc, argv, _cmdLineOptions), _mainOptions);
      notify(_mainOptions);
    }
  }
}

void ProgramOptions::parseModeValues(){
  // set mode values and check for invalid values
  for(size_t i = 0; i < _modeParsers.size(); ++i){
    _modeParsers[i].setMode(_mainOptions[_modeParsers[i].name()].as<string>());
    invalidMode = invalidMode || _modeParsers[i].checkForInvalidValue();
  }
}

void ProgramOptions::initialize(int argc, char** argv){
  initializeModeOptions();
  initializeOptions();
  parse(argc, argv);
  parseModeValues();
}
