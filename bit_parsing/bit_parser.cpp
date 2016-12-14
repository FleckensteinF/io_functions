#include "bit_parser.h"

/*bool Tools::BitParsing::stringToBits(const std::string& bytes, std::vector<bool>& bits){
  if(bytes.size() != 8){
    std::cerr << "error extracting bits: message has "  << bytes.size() << "bytes instead of 8!" << std::endl;
    return true;
  }
  bits.clear();  
  for(size_t i = 0; i < bytes.size(); ++i){
    std::bitset<8> buff(bytes.c_str()[i]);    
    for(size_t j = 0; j < buff.size(); ++j){
      bits.push_back(buff[j]);
    }
  }
  return false;
}

void Tools::BitParsing::extractBits(const size_t& startBit, const size_t& length, const std::vector<bool>& bits, std::vector<bool>& extractedBits){
  if(bits.size() < startBit+length){
    std::cout << "error: cannot extract " << startBit+length << " bit from " << bits.size() << " bits!" << std::endl;
    return;
  }
  extractedBits.clear();
  extractedBits.insert(extractedBits.begin(), bits.begin()+startBit, bits.begin()+startBit+length);  
}

template<>
bool Tools::BitParsing::fromBits(const std::vector<bool>& bits, bool& value){
  if(bits.size() != 1){
    std::cout << "error parsing " << bits.size() << " bits into one bool" << std::endl;
    return true;
  }
  value = bits[0];
  return false;
}

template<>
bool Tools::BitParsing::fromBits(const std::vector<bool>& bits, int& value){
  static const std::size_t maxSize = sizeof(unsigned long);
  if(bits.size() > maxSize){
    return true;
  }

  std::bitset<maxSize> bitset;
  for(size_t i = 0; i < bits.size(); ++i){
    bitset << bits[i];
  }
  value = int(bitset.to_ulong());
  return false;
}

template<>
bool Tools::BitParsing::fromBits(const std::vector<bool>& bits, size_t& value){

}

template<>
bool Tools::BitParsing::fromBits(const std::vector<bool>& bits, float& value){
  return false;
}

template<>
bool Tools::BitParsing::fromBits(const std::vector<bool>& bits, double& value){
  return false;
}

template<>
bool Tools::BitParsing::toBits(std::bitset<64>& bits, const size_t& offset, const size_t& length, const bool& value){
  if(length != 1){
    std::cout << "error converting bool to " << length << " bits, bool has length 1!" << std::endl;
    return true;
  }

  // recompute offset
  size_t offsetByte = offset/8;
  size_t offsetBit = offset % 8;
  size_t newOffset = offsetByte*8 + 8-offsetBit-1;
  
  bits[newOffset] = value;
  //bits[offset] = value;
  return false;
}
*/
