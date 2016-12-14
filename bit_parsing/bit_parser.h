#ifndef _BIT_HELPER_H_
#define _BIT_HELPER_H_

#include <bitset>
#include <vector>

namespace Tools{

  // return value is true, if an error occured
  namespace BitParsing{
    //// extracts variable from bits at given startBit with given length
    //// stores result in variable result
    //// returns true, if an error occured
    //template<class ValueType, size_t numberOfBits>
    //  bool parseValue(const size_t& startBit, const size_t& length, const std::bitset<numberOfBits>& bits, ValueType& result);
    //
    //// extracts variable from bits at given startBit with given length
    //// stores result in variable result
    //// returns true, if an error occured
    //
    //template<size_t numberOfBits, size_t length>
    //  void extractBits(const size_t& startBit, const std::bitset<numberOfBits>& bits, std::bitset<length>& extractedBits);

    //template<typename ValueType, size_t numberOfBits=sizeof(ValueType)*8>
    //  bool fromBits(const std::bitset<numberOfBits>& bits, ValueType& value, const size_t& offset=0, const size_t& length=numberOfBits);
    template<size_t numberOfBits> 
      bool fromBits(const std::bitset<numberOfBits>& bits, bool& value, const size_t& offset=0, const size_t& length=numberOfBits);
    template<size_t numberOfBits>
      bool fromBits(const std::bitset<numberOfBits>& bits, int& value, const size_t& offset=0, const size_t& length=numberOfBits);
    template<size_t numberOfBits>
      bool fromBits(const std::bitset<numberOfBits>& bits, size_t& value, const size_t& offset=0, const size_t& length=numberOfBits);
    template<size_t numberOfBits>
      bool fromBits(const std::bitset<numberOfBits>& bits, float& value, const size_t& offset=0, const size_t& length=numberOfBits);
    template<size_t numberOfBits>
      bool fromBits(const std::bitset<numberOfBits>& bits, double& value, const size_t& offset=0, const size_t& length=numberOfBits);
    template<size_t numberOfBits, size_t numberOfBytes>
      bool fromBits(const std::bitset<numberOfBits>& bits, std::string& value, const size_t& offset=0);
    template<size_t numberOfBits, size_t numberOfBytes>
      bool fromBits(const std::bitset<numberOfBits>& bits, char (&value)[numberOfBytes], const size_t& offset=0);

    template<size_t numberOfBits=1>
      bool toBits(std::bitset<numberOfBits>& bits, const bool& value, const size_t& offset=0, const size_t& length=numberOfBits);
    template<size_t numberOfBits=sizeof(int)*8>
      bool toBits(std::bitset<numberOfBits>& bits, const int& value, const size_t& offset=0, const size_t& length=numberOfBits);
    template<size_t numberOfBits=sizeof(size_t)*8>
      bool toBits(std::bitset<numberOfBits>& bits, const size_t& value, const size_t& offset=0, const size_t& length=numberOfBits);
    template<size_t numberOfBits=sizeof(float)*8>
      bool toBits(std::bitset<numberOfBits>& bits, const float& value, const size_t& offset=0, const size_t& length=numberOfBits);
    template<size_t numberOfBits=sizeof(double)*8>
      bool toBits(std::bitset<numberOfBits>& bits, const double& value, const size_t& offset=0, const size_t& length=numberOfBits);
    template<size_t numberOfBits, size_t numberOfBytes>
      bool toBits(std::bitset<numberOfBits>& bits, const std::string& value, const size_t& offset=0);
    template<size_t numberOfBits, size_t numberOfBytes>
      bool toBits(std::bitset<numberOfBits>& bits, const char (&value)[numberOfBytes], const size_t& offset=0);
  };
};

#include "bit_parser.hpp"

#endif // _BIT_HELPER_H_
