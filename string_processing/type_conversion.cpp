#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <math.h>
#include <algorithm>
#include <limits>
#include <vector>

#include "string_ana.h"
#include "string_mod.h"
#include "type_conversion.h"

/// converts a single char to a string
/**
   \param c char to convert
   \returns string
*/
std::string Tools::StringProcessing::chartostr(char c){
  std::stringstream ss;
  ss << c;
  return ss.str();
}

/// converts a string to a boolean
/** 
    \param s string to analyze
    \returns boolean
*/
bool Tools::StringProcessing::stringtoboolean(std::string s){
  s = stringtrim(s, " (){}[]\t\n;,:");
  return (bool)((s == "true") || (s == "True") || (s=="1"));
}

/// converts a boolean to a string
/** 
    \param b boolean 
    \returns "true" or "false"
*/
std::string Tools::StringProcessing::booleantostring(bool b){
  if(b) return "true";
  else return "false";
}


/// a version of the stdlib function that treads c++ strings
double Tools::StringProcessing::atof(std::string s){
  return atof(s.c_str());
}

/// a version of the stdlib function that treads c++ strings
int Tools::StringProcessing::atoi(std::string s){
  return atoi(s.c_str());
}

/// a wrapper for sscanf that treats c++ strings
int Tools::StringProcessing::stringscanf(std::string s, std::string pattern,  ...){
  int retval;
  va_list args;
  va_start (args, pattern);
  retval = vsscanf(s.c_str(), pattern.c_str(), args);
  va_end (args);
  return retval;
}

/// behaves like sprintf(char*, ...), but with c++ strings and returns the result
/**
   \param str pattern to be printed to
   \return resulting string
   The function interally calles sprintf, but converts the result to a c++ string and returns that one. 
   Problems of memory allocation are taken care of automatically.
 */
std::string Tools::StringProcessing::stringprintf(std::string str, ...){
  unsigned int size = 256;
  va_list args;
  char* buf = (char*)malloc(size*sizeof(char));
  va_start (args, str);
  while(size <= (unsigned int)vsnprintf(buf, size, str.c_str(), args)){
    size *= 2;
    buf = (char*)realloc(buf, size*sizeof(char));
  }
  va_end (args);      
  std::string retval = std::string(buf);
  free(buf);
  return retval;
}  


/// converts a float/double to a c++ string
/**
   \param d float/double to be converted
   \param showsign force including the sign (+/-) into the resulting string
   \return string version of the floating point number
 */
std::string Tools::StringProcessing::floattostr(double d, bool showsign){
  std::stringstream ss;
  if(showsign && d>0){
    ss << "+";
  }
  ss << d;
  return ss.str();
};


/// converts an integer to a c++ string
/**
   \param n integer to be converted
   \param showsign force including the sign (+/-) into the resulting string
   \return string version of the integer
 */
std::string Tools::StringProcessing::inttostr(int n, bool showsign){
  if(!showsign){
    return stringprintf("%d", n);
  } else return stringprintf( n<0 ? "%d" : "+%d", n);
};

/// converts a string into an integer
/**
   \param s string to be converted
   \return integer result
 */
int Tools::StringProcessing::strtoint(std::string s){
  std::stringstream stream(s);
  int t;
  stream >> t;
  return t;
}

/// converts a string into a double precision float
/**
   \param s string to be converted
   \return double result
 */
double Tools::StringProcessing::strtofloat(std::string s){
  std::stringstream stream(s);
  double t;
  stream >> t;
  return t;
}
