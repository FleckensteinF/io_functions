#include <string>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <math.h>
#include <algorithm>
#include <limits>
#include <vector>

#include "string_ana.h"
#include "type_conversion.h"

/// finds if a string is empty
/** 
    \param haystack string to search
*/
bool Tools::StringProcessing::strempty(std::string haystack){
  return !(bool)(haystack.find_first_not_of("\n\t ")<haystack.size());
}

/// finds if a string contains another
/** 
    \param haystack string to search
    \param needle string to find
*/
bool Tools::StringProcessing::stringcontains(std::string haystack, std::string needle){
  return (bool)(haystack.find(needle)<haystack.size());
}

/// count the occurences of "needle" in "haystack"
/**
   \param haystack string to search
   \param needle string to search for
*/
size_t Tools::StringProcessing::stringcount(std::string haystack, std::string needle){
  size_t n = 0;
  size_t pos = haystack.find(needle);
  while(pos<haystack.size()){
    n++;
    pos++;
    pos=haystack.find(needle, pos);
  }
  return n;
}

/// finds the neares matching parenthesis in a string from a given position
/**
   \param str string to search
   \param nextpos starting position of parenthesis check 
   \param paropen opening parenthesis (arbitrary string)
   \param parclose closing parenthesis (arbitrary string)
   \return position of matching parenthesis close in the string
*/
size_t Tools::StringProcessing::findParenthesisMatch(std::string str, size_t nextpos, std::string paropen, std::string parclose){
  size_t openbrace = 0;
  size_t closebrace = 0;
  size_t bracestack = 1;
  while((bracestack > 0) && (nextpos < str.size())){
    openbrace = str.find(paropen, nextpos+1);
    closebrace = str.find(parclose, nextpos+1);
    nextpos++;
    if(openbrace < closebrace){
      bracestack++;
      nextpos = openbrace;
    } else {
      bracestack--;
      nextpos = closebrace;
    }
  }
  return nextpos;
}

/// finds the neares matching parenthesis in a string from a given position
/**
   \param str string to search
   \param nextpos starting position of parenthesis check 
   \param paropen opening parenthesis (arbitrary string)
   \param parclose closing parenthesis (arbitrary string)
   \return position of matching parenthesis close in the string
*/
size_t Tools::StringProcessing::rfindParenthesisMatch(std::string str, size_t nextpos, std::string paropen, std::string parclose){
  size_t openbrace = 0;
  size_t closebrace = 0;
  size_t bracestack = 1;
  while((bracestack > 0) && (nextpos < str.size())){
    openbrace = str.rfind(paropen, nextpos-1);
    closebrace = str.rfind(parclose, nextpos-1);
    // this line is correct and important!
    closebrace = std::min(closebrace, closebrace+1);
    // it helps to avoid overflows of 'closebrace' that lead to wrong return values!
    nextpos--;
    if(openbrace < closebrace){
      bracestack++;
      nextpos = closebrace;
    } else {
      bracestack--;
      nextpos = openbrace;
    }
  }
  return nextpos;
}

/// finds the neares matching parenthesis in a string from a given position
/**
   \param str string to search
   \param nextpos starting position of parenthesis check 
   \param paropen opening parenthesis (arbitrary character)
   \param parclose closing parenthesis (arbitrary character)
   \return position of matching parenthesis close in the string
*/
size_t Tools::StringProcessing::findParenthesisMatch(std::string str, size_t nextpos, char paropen, char parclose){
  return findParenthesisMatch(str, nextpos,chartostr(paropen),chartostr(parclose));
}

/// reverse-finds the neares matching parenthesis in a string from a given position
/**
   \param str string to search
   \param nextpos starting position of parenthesis check 
   \param paropen opening parenthesis (arbitrary character)
   \param parclose closing parenthesis (arbitrary character)
   \return position of matching parenthesis close in the string
*/
size_t Tools::StringProcessing::rfindParenthesisMatch(std::string str, size_t nextpos, char paropen, char parclose){
  return rfindParenthesisMatch(str, nextpos,chartostr(paropen),chartostr(parclose));
}

/// finds the next "free" occurrence of needle in haystack
/**
   \param haystack string to search
   \param needle string to search for
   \param paropen opening parenthesis, denoting the beginning of a "closed block"
   \param parclose closing parenthesis, denoting the end of a "closed block"
   \param startpos position to start searching at
 */
size_t Tools::StringProcessing::findFree(std::string haystack, std::string needle, std::string paropen, std::string parclose, size_t startpos){
  size_t needlepos = haystack.find(needle, startpos);
  size_t nextparopen = haystack.find(paropen, startpos);
  while(needlepos > nextparopen){
    startpos = findParenthesisMatch(haystack, nextparopen, paropen, parclose)+1;
    needlepos = haystack.find(needle, startpos);
    nextparopen = haystack.find(paropen, startpos);
  }
  return needlepos;
}  

/// reverse-finds the next "free" occurrence of needle in haystack
/**
   \param haystack string to search
   \param needle string to search for
   \param paropen opening parenthesis, denoting the beginning of a "closed block"
   \param parclose closing parenthesis, denoting the end of a "closed block"
   \param startpos position to start searching at
 */
size_t Tools::StringProcessing::rfindFree(std::string haystack, std::string needle, std::string paropen, std::string parclose, size_t startpos){
  size_t needlepos = haystack.rfind(needle, startpos);
  size_t nextparclose = haystack.rfind(parclose, startpos);
  while(needlepos < nextparclose){
    startpos = rfindParenthesisMatch(haystack, nextparclose, paropen, parclose)-1;
    // this line is correct and important! 
    startpos = std::min(startpos+1, startpos-1); 
    // it helps to avoid overflows of 'startpos' that result in non-terminating function calls!
    needlepos = haystack.rfind(needle, startpos);
    nextparclose = haystack.rfind(parclose, startpos);
  }
  return needlepos;
}  

/// finds the next "free" occurrence of any needle in haystack
/**
   \param haystack string to search
   \param needles string with characters to search for
   \param paropen opening parenthesis, denoting the beginning of a "closed block"
   \param parclose closing parenthesis, denoting the end of a "closed block"
   \param startpos position to start searching at
 */
size_t Tools::StringProcessing::findFreeOf(std::string haystack, std::string needles, std::string paropen, std::string parclose, size_t startpos){
  size_t needlepos = haystack.find_first_of(needles, startpos);
  size_t nextparopen = haystack.find(paropen, startpos);
  while(needlepos > nextparopen){
    startpos = findParenthesisMatch(haystack, nextparopen, paropen, parclose)+1;
    needlepos = haystack.find_first_of(needles, startpos);
    nextparopen = haystack.find(paropen, startpos);
  }
  return needlepos;
}  

/// reverse-finds the next "free" occurrence of any needle in haystack
/**
   \param haystack string to search
   \param needles string with characters to search for
   \param paropen opening parenthesis, denoting the beginning of a "closed block"
   \param parclose closing parenthesis, denoting the end of a "closed block"
   \param startpos position to start searching at
 */
size_t Tools::StringProcessing::rfindFreeOf(std::string haystack, std::string needles, std::string paropen, std::string parclose, size_t startpos){
  size_t needlepos = haystack.find_last_of(needles, startpos);
  size_t nextparclose = haystack.rfind(parclose, startpos);
  while(needlepos < nextparclose){
    startpos = rfindParenthesisMatch(haystack, nextparclose, paropen, parclose);
    // this line is correct and important! 
    startpos = std::min(startpos+1, startpos-1); 
    // it helps to avoid overflows of 'startpos' that result in non-terminating function calls!
    needlepos = haystack.find_last_of(needles, startpos);
    nextparclose = haystack.rfind(parclose, startpos);
    // this line is correct and important! 
    nextparclose = std::min(nextparclose, nextparclose+1);
    // it helps to avoid overflows of 'nextparclose' that result wrong return values
  }
  return needlepos;
}  
