#ifndef _STRING_MOD_H_
#define _STRING_MOD_H_

namespace Tools{
  namespace StringProcessing{
    // string modification functions
    std::string stringreplace(std::string str, std::string before, std::string after);
    std::string stringreplace(std::string str, std::string rep);
    std::vector<std::string> stringsplit(std::string str, std::string del = " ");
    std::vector<std::string> stringsplit(std::string str, std::string del, std::string paropen, std::string parclose, bool splitatpar = false);
    std::vector<std::string> stringsplit(std::string str, std::vector<std::string> dels, std::string paropen, std::string parclose, bool splitatpar = false);
    std::string stringcompress( std::string str);
    std::string stringremove(std::string str, std::string rem);
    std::string stringhash( std::string str );
    std::string stringsanitize(std::string str);
    std::string word_abbreviate_ger(std::string word);
    std::string text_abbreviate_ger(std::string text, size_t n);
    std::string parenthesisPartner(std::string p);
    char parenthesisPartner(char p);
    std::string aritheval(std::string str);
    std::string stringeval(std::string s);
    std::string stringrepeval(std::string s);
    std::string stringaritheval(std::string s);
    std::string stringstrip(std::string str, std::string front, std::string back);
    std::string stringtrim( std::string const& str, char const* sepSet );
  };
};
#endif // _STRING_MOD_H_
