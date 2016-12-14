#ifndef _STRING_ANA_H_
#define _STRING_ANA_H_

namespace Tools{
  namespace StringProcessing{
    // string analysis functions
    bool strempty(std::string haystack);
    size_t stringcount(std::string haystack, std::string needle);
    bool stringcontains(std::string haystack, std::string needle);
    size_t findParenthesisMatch(std::string str, size_t nextpos, std::string paropen, std::string parclose);
    size_t findParenthesisMatch(std::string str, size_t nextpos, char paropen, char parclose);
    size_t rfindParenthesisMatch(std::string str, size_t nextpos, std::string paropen, std::string parclose);
    size_t rfindParenthesisMatch(std::string str, size_t nextpos, char paropen, char parclose);
    size_t findFree(std::string haystack, std::string needle, std::string paropen, std::string parclose, size_t startpos = 0);
    size_t rfindFree(std::string haystack, std::string needle, std::string paropen, std::string parclose, size_t startpos = -1);
    size_t findFreeOf(std::string haystack, std::string needles, std::string paropen, std::string parclose, size_t startpos = 0);
    size_t rfindFreeOf(std::string haystack, std::string needles, std::string paropen, std::string parclose, size_t startpos = -1);
  };
};
#endif // _STRING_ANA_H_
