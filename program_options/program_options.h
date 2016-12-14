#ifndef _TOOLS_PROGRAM_OPTIONS_H_
#define _TOOLS_PROGRAM_OPTIONS_H_


#include <boost/program_options.hpp>

namespace Tools{
  // class that handles the console input, and parses the config file
  // the program parameters are stored 
  // and can be retrieved using the public string members
  class ProgramOptions{
  public:
    // handles options, which take different arguments 
    // for the same option
    class ModeParser{
    public:
      // is returned, when the given input is not a valid option
      static const std::string invalid;
      // holds the resulting option value after calling setMode 
      std::string mode;
    
      ModeParser(const std::string& name, const std::string shortName, const std::string info, const std::vector<std::vector<std::string> >& modeValues);
      // outputs a string, that describes the valid options
      std::string getDescription() const;
      // sets the mode member according to the given modeString
      // to the first of several allowed values, if modeString matches one of them
      // to invalid, if modeString matches none of the allowed values
      void setMode(const std::string& modeString);
      // checks whether mode is set to invalid
      // and outputs an error to cout
      bool checkForInvalidValue() const;
      // get the option name
      std::string name() const;
      std::string shortName() const;
      std::string defaultValue() const;
      std::string info() const;
    private:
      // identifier for an instance, 
      // used in getDescription
      // and for error messages
      std::string _name, _shortName, _info;
      // allowed values
      // _modeValues.size() = number of different values
      // each vector of string represents one value
      // its elements are the different input arguments 
      // mapping to the same option
      std::vector<std::vector<std::string> > _modeValues;
    };

    // allowed program options
    const std::string configPath;
    // define in child class as const string 

    // true, if help was called or one of the modeParser instances has mode=invalid
    // false otherwise
    bool invalidMode;

    ProgramOptions(int argc, char** argv, const std::vector<ModeParser> modeParsers=std::vector<ModeParser>(), const bool initialize=true);
    virtual ~ProgramOptions();
    // returns the options arguments given the options string name 
    // (one of the public string members from above)
    template <typename ReturnType> ReturnType get(const std::string& valueName) const;
    std::string getMode(const std::string& valueName) const;

    // true if help output was requested
    bool helpRequested() const;

  protected:
    // stores options that don't have default values
    std::vector<std::string> _optionsWithoutDefaultValue;
    std::vector<ModeParser> _modeParsers;
    // used to parse the command line and config files
    boost::program_options::options_description _configFileOptions, _cmdLineOptions;
    boost::program_options::variables_map _mainOptions;
  
    // hepler function initializing all the options and their properties
    // must be implemented by child class
    // if an option has no default value, store the name in '_optionsWithoutDefaultValue'
    virtual void initializeOptions();

    // initializes options for the mode parsers
    // using the name of the mode parser as option name
    void initializeModeOptions();
  
    // implement help output
    virtual std::string help();
    // parses the commandline input
    // overwrite if more config files should be used
    virtual void parse(int argc, char** argv);
    // set the mode value and check for invalid values
    void parseModeValues();
    // calls the functions needed to initialize
    // the options and parse the arguments
    void initialize(int argc, char** argv);
  };
};
#include "program_options.hpp"

#endif // _TOOLS_PROGRAM_OPTIONS_H_
