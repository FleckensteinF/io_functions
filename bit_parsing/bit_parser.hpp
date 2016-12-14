#include <iostream>

//template<class ValueType>
//bool Tools::BitParsing::parseValue(const size_t& startBit, const size_t& length, const std::vector<bool>& bits, ValueType& result){
//  bool statusChanged = false;
//  std::vector<bool> extractedBits;
//  extractBits(startBit, length, bits, extractedBits);
//  ValueType buff;
//
//  if(fromBits<ValueType>(extractedBits, buff)){
//    return false;
//  }
//  
//  if(buff != result){
//    statusChanged = true;
//    result = buff;
//  }
//  return statusChanged;
//}
//
//template<class ValueType>
//bool Tools::BitParsing::toBits(std::bitset<64>& bits, const size_t& offset, const size_t& length, const ValueType& value){
//  const size_t valueSize = sizeof(ValueType)*8;
//  std::bitset<valueSize> buff(value);
//  int valueOffset = valueSize - length;
//  if(valueOffset < 0 ){
//    std::cout << "error converting ValueType to " << length << " bits, ValueType is too small!" << std::endl;
//    return true;
//  }
//  for(size_t i = 0; i < length; ++i){
//    bits[offset+i] = buff[valueOffset + i];
//  }
//  return false;
//}

template<size_t numberOfBits> 
bool Tools::BitParsing::fromBits(const std::bitset<numberOfBits>& bits, bool& value, const size_t& offset, const size_t& length){
  if(numberOfBits < offset+length){
    std::cout << "Error in Tools::BitParsing: bitset (" << numberOfBits << ") is smaller than offset (" << offset << ") + length (" << length << ")" << std::endl;
    return true;
  }
  value = bits[offset];
  return false;
}

template<size_t numberOfBits>
bool Tools::BitParsing::fromBits(const std::bitset<numberOfBits>& bits, int& value, const size_t& offset, const size_t& length){
  if(numberOfBits < offset+length){
    std::cout << "Error in Tools::BitParsing: bitset (" << numberOfBits << ") is smaller than offset (" << offset << ") + length (" << length << ")" << std::endl;
    return true;
  }
  std::bitset<numberOfBits> buff;
  for(size_t i = 0; i < length; ++i){
    buff[i] = bits[offset+i];
  }
  value = buff.to_ullong();
  return false;
}

template<size_t numberOfBits>
bool Tools::BitParsing::fromBits(const std::bitset<numberOfBits>& bits, size_t& value, const size_t& offset, const size_t& length){
  int buffValue;
  bool error = fromBits(bits, buffValue, offset, length);
  value = (size_t)buffValue;
  return error;
}

template<size_t numberOfBits, size_t numberOfBytes>
bool Tools::BitParsing::fromBits(const std::bitset<numberOfBits>& bits, std::string& value, const size_t& offset){
  char buff[numberOfBytes];
  if(fromBits(bits, buff, offset)){
    return true;
  }
  value = "";
  value.append(&buff[0], numberOfBytes);
  return false;
}

template<size_t numberOfBits, size_t numberOfBytes>
bool Tools::BitParsing::fromBits(const std::bitset<numberOfBits>& bits, char (&value)[numberOfBytes], const size_t& offset){
  size_t length = numberOfBytes*8;
  if(numberOfBits < offset+length){
    std::cout << "Error in Tools::BitParsing: bitset (" << numberOfBits << ") is smaller than offset (" << offset << ") + length (" << length << ")" << std::endl;
    return true;
  }
  for(size_t i = 0; i < numberOfBytes; ++i){
    // generate buff bitset
    std::bitset<8> buff;
    for(size_t j = 0; j < 8; ++j){
      buff[8-j-1] = bits[offset + 8*i+j];
    }
    value[i] = buff.to_ulong();
  }
  return false;
}

template<size_t numberOfBits>
bool Tools::BitParsing::toBits(std::bitset<numberOfBits>& bits, const bool& value, const size_t& offset, const size_t& length){
  if(numberOfBits < offset+length){
    std::cout << "Error in Tools::BitParsing: bitset (" << numberOfBits << ") is smaller than offset (" << offset << ") + length (" << length << ")" << std::endl;
    return true;
  }
  if(value){
    bits[offset] = 1;
  }else{
    bits[offset] = 0;
  }
  return false;
}

template<size_t numberOfBits>
bool Tools::BitParsing::toBits(std::bitset<numberOfBits>& bits, const int& value, const size_t& offset=0, const size_t& length=numberOfBits){
  if(numberOfBits < offset+length){
    std::cout << "Error in Tools::BitParsing: bitset (" << numberOfBits << ") is smaller than offset (" << offset << ") + length (" << length << ")" << std::endl;
    return true;
  }
  std::bitset<sizeof(int)*8> buff(value);
  //std::cout << value << " -> ";
  //std::cout << buff << std::endl;
  for(size_t i = 0; i < length; ++i){
    bits[offset+i] = buff[i];
  }
  return false;
}

template<size_t numberOfBits>
bool Tools::BitParsing::toBits(std::bitset<numberOfBits>& bits, const size_t& value, const size_t& offset, const size_t& length){
  int buff = value;
  return toBits<numberOfBits>(bits, buff, offset, length);
}

template<size_t numberOfBits>
bool Tools::BitParsing::toBits(std::bitset<numberOfBits>& bits, const float& value, const size_t& offset, const size_t& length){
  return true;
}

template<size_t numberOfBits>
bool Tools::BitParsing::toBits(std::bitset<numberOfBits>& bits, const double& value, const size_t& offset, const size_t& length){
  return true;
}

template<size_t numberOfBits, size_t numberOfBytes>
bool Tools::BitParsing::toBits(std::bitset<numberOfBits>& bits, const std::string& value, const size_t& offset){
  if(value.size() != numberOfBytes){
    std::cout << "Error in Tools::BitParsing: string (" << value.size() << ") is of length numberOfBytes (" << numberOfBytes << ")" << std::endl;
    return true;
  }
  char buff[numberOfBytes];
  for(size_t i = 0; i < numberOfBytes; ++i){
    buff[i] = value[i];
  }
  return toBits(bits, buff, offset);
}

template<size_t numberOfBits, size_t numberOfBytes>
bool Tools::BitParsing::toBits(std::bitset<numberOfBits>& bits, const char (&value)[numberOfBytes], const size_t& offset){
  size_t length = numberOfBytes*8;
  if(numberOfBits < offset+length){
    std::cout << "Error in Tools::BitParsing: bitset (" << numberOfBits << ") is smaller than offset (" << offset << ") + length (" << length << ")" << std::endl;
    return true;
  }
  std::bitset<numberOfBits> buff;
  for(size_t i = 0; i < numberOfBytes; ++i){
    std::bitset<sizeof(char)*8> oneChar(value[i]);
    for(size_t j = 0; j < 8; ++j){
      buff[8*i+j] = oneChar[8-j-1];
    }
  }
  for(size_t i = 0; i < length; ++i){
    bits[offset+i] = buff[i];
  }
  return false;
}
