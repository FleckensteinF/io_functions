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

#include "func.h"
#include "string_ana.h"
#include "string_mod.h"
#include "type_conversion.h"

/// "hashes" a string to another one
/**
   removes all non-ascii and non-human-readable-character symbols
   \param str string to hash
   \return hashed string
*/
std::string Tools::StringProcessing::stringhash(std::string str){
  std::string result = "";
  char c;
  for(size_t i = 0; i < str.size(); i++){
    c = str[i];
    if(inRange((int)(c), 47, 58) || inRange((int)(c), 64, 91) || inRange((int)(c), 96,123)) result += c;
    //    else result += "_";
  }
  return result;
}

/// sanitizes a string
/**
   tries to replace all non-ascii-characters
   with worthy replacements (under developement)
   \param str string to sanitize
   \return sanitized string
*/
std::string Tools::StringProcessing::stringsanitize(std::string str){
  std::string result = "";
  std::string c;
  size_t pos = 0;
  while(pos < str.size()){
    if(str[pos] > 31){
      result += str[pos];
    } else if(str[pos] == -61){
      pos++;
      switch( (int)str[pos] ){
      case -92:
	c = "a";
	break;
      case -68: 
	c = "u";
	break;
      case -74:
	c = "o";
	break;
      case -124:
	c = "A";
	break;
      case -100: 
	c = "U";	
	break;
      case -106:
	c = "O";
	break;
      case -97:
	c = "S";
	break;
      default:
	c = " ";
      }
      result += c;
    }
    pos++;
  }
  return result;
}

/// strips "front" from the front and "back" from the back of string "str", if neccessary
/** \param front string stripped from the front
    \param back string stripped from the back
    \param str string to be stripped
*/
std::string Tools::StringProcessing::stringstrip(std::string str, std::string front, std::string back){
  size_t startpos = 0;
  size_t endpos = str.size();

  if(str.find(front) == 0) startpos = front.size();
  if(str.find(back) == (str.size() - back.size())) endpos = str.size() - back.size();

  return str.substr(startpos, endpos-startpos);
}

/// Returns a string with leading/trailing characters of a set stripped
/**
   \param str string to be stripped from characters
   \param sepSet array of characters (c-string of characters) to be stripped from str
   \returns stripped string
*/
std::string Tools::StringProcessing::stringtrim( std::string const& str, char const* sepSet ){
  std::string::size_type const first = str.find_first_not_of(sepSet);
  return ( first==std::string::npos ) ? std::string() : str.substr(first, str.find_last_not_of(sepSet)-first+1);
}

/// Compress a string
/** 
    Remove double whitespaces, tabs and newlines. 
    This is primarily intended for clean console output of formatted strings.
    \param str string to compress
    \return compressed string
*/
std::string Tools::StringProcessing::stringcompress(std::string str){
  std::string result;
  size_t pos = str.find_first_not_of("\t\n\r ");
  size_t newpos = 0;
  while(pos < str.size()){
    newpos = std::min(str.find_first_of("\t\n\r ", pos), str.size());
    result += str.substr(pos, newpos-pos) + " ";
    pos = str.find_first_not_of("\t\n\r ", newpos);
  }
  return stringtrim(result, " \t\n\r");
}

/// replace all occurences of a string within another one by something else
/**
   \param str string to process
   \param before string to replace
   \param after string to replace with
*/
std::string Tools::StringProcessing::stringreplace(std::string str, std::string before, std::string after){
  std::string newstr = "";
  size_t pos = 0;
  size_t newpos = str.find(before);
  while(newpos < str.size()){
    newstr += str.substr(pos, newpos-pos);
    newstr += after;
    pos = newpos+before.size();
    newpos = str.find(before, pos);
  }
  newstr += str.substr(pos);
  return newstr;
}

/// replace expressions in a string by others
/**
   \param str string to be processed
   \param rep replacements to be made (format: "foo1/bar1 foo2/bar2 ...")
   \return resulting string

   TODO: At some point, one might want to optimize this function.
   -- more flexibility
   -- more efficiency
   -- cleaner implementation
 */
std::string Tools::StringProcessing::stringreplace(std::string str, std::string rep){
  str = " "+str+" ";
  std::vector<std::string> replacement;
  std::vector<std::string> replacements = stringsplit(rep, " ");
  for(size_t i = 0; i <  replacements.size(); i++){
    replacement = stringsplit(replacements[i], "/");
    str = stringreplace(str, replacement[0], replacement[1]);
  }
  return stringtrim(str, " ");
}


/// remove expressions in a string
/**
   \param str string to be processed
   \param rem string to be removed
   \return resulting string

   TODO: At some point, one might want to optimize this function.
   -- more flexibility
   -- more efficiency
   -- cleaner implementation
 */
std::string Tools::StringProcessing::stringremove(std::string str, std::string rem){
  std::string result = "";
  size_t pos = str.find_first_not_of(rem);
  size_t newpos = 0;
  while(pos < str.size()){
    newpos = std::min(str.find_first_of(rem, pos), str.size());
    result += str.substr(pos, newpos-pos);
    pos = str.find_first_not_of(rem, newpos);
  }
  return result;
}

/// split a string at all occurrences of the delimiter and return a vector of results
/**
   \param str string to be split into chunks
   \param del delimter for the splitting (may be several characters long)
   \return vector of strings containing the chunks of str
*/
std::vector<std::string> Tools::StringProcessing::stringsplit(std::string str, std::string del){
  std::vector<std::string> split;
  std::string substr;
  if(del.size()>0){
    size_t oldpos = 0;
    size_t newpos = 0;
    while(newpos < str.size() && oldpos <= newpos){
      oldpos = newpos;
      newpos = str.find(del, oldpos);
      substr = str.substr(oldpos, std::min(str.size(),newpos)-oldpos);
      if(substr.size()>0) split.push_back(substr);
      if(newpos < str.size()) newpos += del.size();
    }
  }
  if(split.size() < 1) split.push_back(str);
  return split; 
}

/// split a string into little chunks
/**
   This version of the stringsplit function accepts one delimiter
   and respects parenthesis (e.g. does not split in a way that will break parenthesis matches)

   \param str string to split
   \param del delimiter
   \param paropen opening parenthesis (may be an arbitrary string)
   \param parclose closing parenthesis (may be an arbitrary string)
   \param splitatpar additionally split at parenthesis (default: false)
 */
std::vector<std::string> Tools::StringProcessing::stringsplit(std::string str, std::string del, std::string paropen, std::string parclose, bool splitatpar){
  std::vector<std::string> split;
  std::string substr;
  if(del.size()>0){
    size_t oldpos = 0;
    size_t newpos = 0;
    size_t nextparopen = str.size();
    while(newpos < str.size() && oldpos <= str.size()){
      // find the next opening brace
      nextparopen = str.find(paropen, oldpos);
      // find the next occurance of the delimiter
      newpos = std::min(str.find(del, oldpos), str.size());
      // as long as there are opening braces before the delimiter
      while(nextparopen < newpos){
	// proceed to the corresponding closing brace
	nextparopen = findParenthesisMatch(str, nextparopen, paropen, parclose);
	// place the pointer behind that one
	newpos = std::max(newpos, nextparopen);
	// find the next breakpoint
	newpos = std::min(str.find(del, newpos), str.size());
	// if there is any parenthesis left in the string, find the next opening one
	if(nextparopen < str.size()) nextparopen = str.find(paropen, nextparopen+1);
      }
      // extract the string
      substr = str.substr(oldpos, std::min(str.size(),newpos)-oldpos);
      // push it to the vector
      if(substr.size()>0) split.push_back(substr);
      // and continue
      oldpos = newpos+1;
    }
  }
  if(split.size() < 1) split.push_back(str);
  return split; 
}

/// split a string into little chunks
/**
   This version of the stringsplit function accepts a set of delimiters
   and respects parenthesis (e.g. does not split in a way that will break parenthesis matches)

   \param str string to split
   \param dels vector of delimiters
   \param paropen opening parenthesis (may be an arbitrary string)
   \param parclose closing parenthesis (may be an arbitrary string)
   \param splitatpar additionally split at parenthesis (default: false)
 */
std::vector<std::string> Tools::StringProcessing::stringsplit(std::string str, std::vector<std::string> dels, std::string paropen, std::string parclose, bool splitatpar){
  std::vector<std::string> split;
  std::string substr;

  if(dels.size()>0){
    size_t oldpos = 0;
    size_t newpos = 0;
    size_t tmppos = 0;
    size_t buf;
    size_t delsize;
    size_t nextparopen = str.size();
    while(newpos < str.size() && oldpos <= str.size()){
      nextparopen = str.find(paropen, oldpos);
      newpos = str.size();
      for(size_t i = 0; i < dels.size(); i++){
	if(dels[i].size() > 0){
	  buf = str.find(dels[i], oldpos);
	  if(buf < newpos){
	    newpos = buf;
	    delsize = std::max(dels[i].size(),(size_t)1);
	  }
	}
      }
      while(nextparopen < newpos){
	// set the parenthesis pointer to the next closing parenthesis
	nextparopen = findParenthesisMatch(str, nextparopen, paropen, parclose);
	// set the newpos pointer to the greater of itself and the next closing parenthesis 
	newpos = std::max(newpos, nextparopen+1);
	// find the next opening parenthesis after the closing one we just found
	if(nextparopen < str.size()) nextparopen = str.find(paropen, nextparopen+paropen.size());
	else nextparopen = -1;
	// store the new position in a buffer
	tmppos = newpos;
	// set the new position to the end of the string
	newpos = str.size();
	// find the first of the delimiters after the buffer position and store it to newpos
	for(size_t i = 0; i < dels.size(); i++){
	  if(dels[i].size() > 0){
	    buf = str.find(dels[i], tmppos);
	    if(buf < newpos){
	      newpos = buf;
	      delsize = std::max(dels[i].size(),(size_t)1);
	    }
	  }
	}
      }
      substr = str.substr(oldpos, std::min(str.size(),newpos)-oldpos);
      if(substr.size()>0){
	//	std::cout << "$:" << stringcompress(substr) << std::endl;
	split.push_back(substr);
      }
      if(newpos < str.size()) newpos+=delsize;
      //      std::cout << stringcompress(str.substr(newpos, 5)) << std::endl;
      oldpos = newpos;
    }
  }
  if(split.size() < 1) split.push_back(str);
  return split; 
}


/// abbreviates single words by one syllable
/**
   \param word passage to abbreviate
*/
std::string Tools::StringProcessing::word_abbreviate_ger(std::string word){
  size_t end = word.find_last_not_of(")]},.");
  size_t lastvocal = std::max(word.find_last_of("aeiouöäüAEIOUÖÄÜyYjJ", word.size()-2), word.find_first_of("bcdfghklmnpqrstvwxzBCDFGHKLMPQRSTVWXZ"));
  lastvocal = std::min(std::min(word.find_last_of("bcdfghklmnpqrstvwxzBCDFGHKLMPQRSTVWXZ", lastvocal), word.size())+1, lastvocal);
  std::string result = word.substr(0, lastvocal) + ".";
  if(end < word.size()){
    end = word.find_first_of(")]},", end);
    if(end < word.size()) result += word.substr(end);
  }
  return result;
}

/// abbreviates textual expressions to fit the desired length (in characters)
/**
   \param text text passage to abbreviate
   \param n maximum number of characters allowed
*/
std::string Tools::StringProcessing::text_abbreviate_ger(std::string text, size_t n){
  size_t pos = text.find_first_not_of(" \n\t");
  size_t nextpos = pos;
  std::vector<std::string> words;
  while(pos < text.size()){
    nextpos = text.find_first_of(" \n\t", pos);
    words.push_back(text.substr(pos, nextpos-pos));
    pos = text.find_first_not_of(" \n\t", nextpos);
  }
  size_t index = words.size()-1;
  size_t length = text.size();
  std::string newword;
  int diff = 0;
  while(length>n && index < words.size()){
    newword = word_abbreviate_ger(words[index]);
    diff = words[index].size() - newword.size();
    if(diff > 0){
      length -= diff;
      words[index] = newword;
     } else {
      index--;
    }
  }
  std::string result = "";
  for(size_t i = 0; i < words.size(); i++){
    result += words[i];
    result += " "; 
  }
  return stringtrim(result, " ");
}

std::string Tools::StringProcessing::parenthesisPartner(std::string p){
  if(p == "(") return ")";
  if(p == ")") return "(";
  if(p == "\"") return "\"";
  if(p == "'") return "'";
  if(p == "[") return "]";
  if(p == "]") return "[";
  if(p == "{") return "}";
  if(p == "}") return "{";
  return " ";
}

char Tools::StringProcessing::parenthesisPartner(char p){
  switch(p){
  case '(': return ')';
  case ')': return '(';
  case '"': return '"';
  case '\'': return '\'';
  case '[': return ']';
  case ']': return '[';
  case '{': return '}';
  case '}': return '{';
  }
  return ' ';

}

/// parses a string for arithmetic expressions, evaluating all of them
/**
   \par str string to parse
   \return string with all expressions evaluated
*/
std::string Tools::StringProcessing::aritheval(std::string str){
  std::string numbers = "1234567890";
  std::string separators = ",.\n\t ";
  std::string operators = "/+-*";
  std::string openpar = "(";
  std::string closepar = ")";

  std::string result;
  
  size_t pos = 0;
  // loop over the string
  while(pos < str.size()){
    // find the next expression in line
    size_t expstart = str.find_first_of(numbers+operators+separators+openpar,pos);
    if(expstart > str.size()){
      result+= str.substr(pos);
      return result;
    }
    size_t parstart = str.find_first_of(openpar,pos);
    size_t expend;
    // if the expression starts with an opening parenthesis - find the match
    // else find the last thing that looks like belonging to the expression
    if(expstart == parstart){
      expend = findParenthesisMatch(str,parstart,openpar,closepar);
    } else {
      expend = str.find_first_not_of(numbers+separators+operators+openpar+closepar,expstart);
    }
    if(expend > str.size()){
      expend = str.size();
    }
    // append everything before the expression to the string
    result += str.substr(pos,expstart-pos);
    // convert the expression into a number
    // using PEMDAS-capable strtofloat
    // and convert it back to a string
    bool forcesign = (str[expstart] == '+');
    result += floattostr(strtofloat(str.substr(expstart,expend-expstart)),forcesign);
    pos = expend;
  }
  // once done, return
  return result;
}
    

/// evaluates a textual expression containing arithmetic calculations
/**
  This function is capable of using the associative law in textual expressions.
  Its behaviour is best explained in an example:
  stringaritheval("text $(2*(moretext 5 even more text)+3) some text")
    = "text moretext 13 even more text some test";
  all expression subject to evaluation shall be enclosed in '$(' ... ')'

  \param s a textual expression containing "string arithmetics"
  \return the evaluated expression
*/

std::string Tools::StringProcessing::stringaritheval(std::string str){
  //  std::cout << "stringaritheval called with \"" << str << "\"!" << std::endl;
  std::string numbers = "1234567890";
  std::string separators = ",.\n\t ";
  std::string operators = "/+-*";
  std::string openpar = "([{";
  std::string closepar = ")]}";
  std::string quotes = "'\"";

  size_t strstart = 0;
  size_t expstart = 0;
  size_t strend = 0;
  size_t expend = 0;

  size_t numstart;
  size_t numend;

  std::string exphead;
  std::string exptail;

  std::string strhead;
  std::string strbody;
  std::string strtail;

  std::string newstr = "";

  while(true){
    // find the head of the expression (the part before the string)
    expstart  = str.find_first_of(numbers+openpar, expstart);
    if(expstart > str.size()){
        newstr += str.substr(expend);
	//	std::cout << "breaking - no expression, only \"" << str.substr(expend) << "\"!" << std::endl;
	break;
    }
    expstart = str.find_last_not_of(numbers+separators+operators+openpar, expstart)+1;
    expend = str.find_first_not_of(numbers+separators+operators+openpar+closepar, expstart);
    if(expend > str.size()){
        newstr += str.substr(expstart);
	//	std::cout << "breaking - expression reaches end of string, that is: \"" << str.substr(expstart) << "\"!" << std::endl;
	break;
    }
    exphead = str.substr(expstart,expend-expstart);

    // find the string encapsulated within the expression
    strstart = expend;
    strend = findParenthesisMatch(str, strstart, str[strstart], parenthesisPartner(str[strstart]));
    if(strend > str.size()){
        newstr += str.substr(strstart);
	//	std::cout << "breaking - stringbody reaches end of string, that is: \"" << str.substr(strstart) << std::endl;
	break;
    }
    strstart++;
    strbody = str.substr(strstart, strend-strstart);
    //    std::cout << "strbody: " << str.substr(strstart, strend-strstart) << std::endl;

    // find the tail of the expression (the part behind the string)
    exptail = "";
    expstart = std::min(strend+1, str.size());
    expstart  = str.find_first_of(numbers+openpar, expstart);
    if(expstart < str.size()){
      expstart = str.find_last_not_of(numbers+separators+operators+openpar, expstart)+1;
      expend = str.find_first_not_of(numbers+separators+operators+openpar+closepar, expstart);
      if(expend < str.size()){
	exptail = str.substr(expstart,expend-expstart);
      } else expend = str.size();
    }

    // concatenate everything
    //    std::cout << exphead << ":$" << strbody << "$:" << exptail << std::endl;
    numend = 0;
    numstart = 0; 
    // loop over the body of the string
    while(true){
      // looking for numbers
      numstart = strbody.find_first_of(numbers, numstart);
      if(numstart > strbody.size()){
	newstr += strbody.substr(numend);
	break;
      }
      newstr += strbody.substr(numend, numstart-numend);
      numend = std::min(strbody.find_first_not_of(numbers, numstart), strbody.size());
      // if you found anything that looks like a number
      // insert it into the expression and evaluate it, adding the result to newstr
      newstr += inttostr(strtoint(exphead+strbody.substr(numstart, numend-numstart)+exptail));
      // and increment the position
      numstart = numend+1;
    }

    // take care that the algorithm terminates properly when running against the end of the string
    expend = std::max(expend,expstart);
    strend = std::max(strend,strstart);
    expend = std::max(strend, expend);
    if(expend < str.size()){
      expstart = expend+1;
    } else break;
  }

  return newstr;
}

std::string Tools::StringProcessing::stringrepeval(std::string s){
  size_t defstart = s.find("{");
  if(defstart > s.size()) return s;
  size_t defend = findParenthesisMatch(s, defstart,"{", "}");
  //  std::cout << defstart << "," << defend << ":" << s.substr(defstart, defend-defstart) << std::endl;
  if(defend > s.size()) return "";
  std::string expression = s.substr(defend+1);
  //  std::cout << expression << std::endl;
  std::vector<std::string> defines = stringsplit(s.substr(defstart+1, defend-defstart-1), ";", "\"", "\"");
  for(size_t i = 0; i < defines.size(); i++){
    if(stringcontains(defines[i], "=")){
      expression = stringreplace(expression, stringtrim(defines[i].substr(0,defines[i].find("=")), "\""), stringtrim(defines[i].substr(defines[i].find("=")+1), "\""));
    }
  }
  return expression;
}

std::string Tools::StringProcessing::stringeval(std::string s){
  std::string functokens = "%$";
  
  size_t expstart = 0;
  size_t expend = 0;

  std::string newstr = "";
  std::string retval;

  // loop over the string
  while (true){
    // looking for occurances of function tokens
    expstart = s.find_first_of(functokens, expstart);
    if(expstart+3 < s.size() && (s[expstart+1] == '(')){
      // if any were found
      newstr += s.substr(expend, expstart - expend);
      // look for the end of the expression
      expend = findParenthesisMatch(s, expstart+1, "(" , ")");
      // pass the expression to the appropriate subfunction
      retval = s.substr(expstart+2, expend-expstart-2);
      if(s[expstart] == '$'){
	retval = stringaritheval(retval);
      } else if(s[expstart] == '%'){
	retval = stringrepeval(retval);
      }
      newstr += retval;
      // and set the string pointer to the end of the expression
      expend++;
      expstart = expend;
    } else {
      // we have reached the end of the string
      // collect everything that was not yet processed 
      newstr += s.substr(expend);
      break;
    }
  }
  // and return the result
  return newstr;
  
}


