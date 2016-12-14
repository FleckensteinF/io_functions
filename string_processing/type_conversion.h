#ifndef _TYPE_CONVERSION_H_
#define _TYPE_CONVERSION_H_

#include <string>

namespace Tools{
  namespace StringProcessing{
    // type conversion functions
    std::string chartostr(char c);
    double atof(std::string s);
    int atoi(std::string s);
    int strtoint(std::string s);
    double strtofloat(std::string s);
    bool stringtoboolean(std::string s);      
    std::string booleantostring(bool b);
    std::string inttostr(int n, bool showsign = false);
    std::string floattostr(double d, bool showsign = false);
    int stringscanf(std::string s, std::string pattern,  ...);
    std::string stringprintf(std::string str, ...);
  };
};
#endif // _TYPE_CONVERSION_H_
