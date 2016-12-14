#include "gtest/gtest.h"
#include "bit_parsing/bit_parser.h"

using namespace Tools::BitParsing;

/*************************************
 ** conversion without using offset **
 *************************************/

TEST(toBits, boolValue){
  std::bitset<1> result;
  bool value = true;
  bool error = toBits(result, value);
  EXPECT_EQ(error, false);
  if(error){
    std::cout << "error testing toBit with bool = true!" << std::endl;
  }else{
    ASSERT_EQ(result.size(), 1);
    EXPECT_EQ(result[0], value);
  }
  result.reset();
  value = false;
  error = toBits(result, value);
  EXPECT_EQ(error, false);
  if(error){
    std::cout << "error testing toBit with bool = true!" << std::endl;
  }else{
    ASSERT_EQ(result.size(), 1);
    EXPECT_EQ(result[0], value);
  }
}

TEST(toBits, intValue){
  std::bitset<sizeof(int)*8> result;
  int value = 0;
  bool error = toBits(result, value);
  EXPECT_EQ(error, false);
  if(error){
    std::cout << "error testing toBit with int = 0!" << std::endl;
  }else{
    ASSERT_EQ(result.size(), sizeof(int)*8);
    for(size_t i = 0; i < result.size(); ++i){
      EXPECT_EQ(result[i], false);
    }
  }
  result.reset();
  value = 1;
  error = toBits(result, value);
  EXPECT_EQ(error, false);
  if(error){
    std::cout << "error testing toBit with bool = true!" << std::endl;
  }else{
    ASSERT_EQ(result.size(), sizeof(int)*8);
    EXPECT_EQ(result[0], true);
    for(size_t i = 1; i < result.size(); ++i){
          EXPECT_EQ(result[i], false);
    }
  }
  result.reset();
  value = 127;
  error = toBits(result, value);
  EXPECT_EQ(error, false);
  if(error){
    std::cout << "error testing toBit with bool = true!" << std::endl;
  }else{
    ASSERT_EQ(result.size(), sizeof(int)*8);
    for(size_t i = 0; i < 7; ++i){
      EXPECT_EQ(result[i], true);
    }
    for(int i = 7; i < int(result.size())-1; ++i){
          EXPECT_EQ(result[i], false);
    }
    EXPECT_EQ(result[result.size()-1], false);
  }
}

TEST(toBits, size_tValue){
  std::bitset<sizeof(size_t)*8> result;
  size_t value = 0;
  bool error = toBits(result, value);
  EXPECT_EQ(error, false);
  if(error){
    std::cout << "error testing toBit with size_t = 0!" << std::endl;
  }else{
    ASSERT_EQ(result.size(), sizeof(size_t)*8);
    for(size_t i = 0; i < result.size(); ++i){
      EXPECT_EQ(result[i], false);
    }
  }
  result.reset();
  value = 1;
  error = toBits(result, value);
  EXPECT_EQ(error, false);
  if(error){
    std::cout << "error testing toBit with bool = true!" << std::endl;
  }else{
    ASSERT_EQ(result.size(), sizeof(size_t)*8);
    EXPECT_EQ(result[0], true);
    for(size_t i = 1; i < result.size(); ++i){
          EXPECT_EQ(result[i], false);
    }
  }
  result.reset();
  value = 127;
  error = toBits(result, value);
  EXPECT_EQ(error, false);
  if(error){
    std::cout << "error testing toBit with bool = true!" << std::endl;
  }else{
    ASSERT_EQ(result.size(), sizeof(size_t)*8);
    for(size_t i = 0; i < 7; ++i){
      EXPECT_EQ(result[i], true);
    }
    for(int i = 7; i < int(result.size())-1; ++i){
          EXPECT_EQ(result[i], false);
    }
    EXPECT_EQ(result[result.size()-1], false);
  }
}

TEST(toBits, stringValue){
  std::bitset<sizeof(char)*8*3> result;
  std::vector<bool>expected = { false, true, true, false, false, false, false, true,
				false, true, true, false, false, false, true, false,
				false, true, true, false, false, false, true, true};
  std::string value = "abc";
  bool error = toBits<sizeof(char)*8*3, 3>(result, value);
  EXPECT_EQ(error, false);
  if(error){
    std::cout << "error testing toBit with string = abc!" << std::endl;
  }else{
    ASSERT_EQ(result.size(), sizeof(char)*8*3);
    ASSERT_EQ(result.size(), expected.size());
    for(size_t i = 0; i < result.size(); ++i){
      EXPECT_EQ(result[i], expected[i]);
    }
  }
}

TEST(toBits, charValue){
  std::bitset<sizeof(char)*8*3> result;
  std::vector<bool>expected = { false, true, true, false, false, false, false, true,
				false, true, true, false, false, false, true, false,
				false, true, true, false, false, false, true, true};
  char value[3] = {'a', 'b', 'c'};
  bool error = toBits(result, value);
  EXPECT_EQ(error, false);
  if(error){
    std::cout << "error testing toBit with const char* = abc!" << std::endl;
  }else{
    ASSERT_EQ(result.size(), sizeof(char)*8*3);
    ASSERT_EQ(result.size(), expected.size());
    for(size_t i = 0; i < result.size(); ++i){
      EXPECT_EQ(result[i], expected[i]);
    }
  }
}

TEST(fromBits, boolValue){
  bool value = true;
  bool result;
  std::bitset<1> bits;
  ASSERT_EQ(toBits(bits, value), false);
  ASSERT_EQ(fromBits(bits, result), false);
  EXPECT_EQ(result, value);

  value = false;
  bits.reset();
  ASSERT_EQ(toBits(bits, value), false);
  ASSERT_EQ(fromBits(bits, result), false);
  EXPECT_EQ(result, value);
}

TEST(fromBits, intValue){
  int value = 0;
  int result;
  std::bitset<sizeof(int)*8> bits;
  ASSERT_EQ(toBits(bits, value), false);
  ASSERT_EQ(fromBits(bits, result), false);
  EXPECT_EQ(result, value);

  value = 1;
  bits.reset();
  ASSERT_EQ(toBits(bits, value), false);
  ASSERT_EQ(fromBits(bits, result), false);
  EXPECT_EQ(result, value);

  value = 127;
  bits.reset();
  ASSERT_EQ(toBits(bits, value), false);
  ASSERT_EQ(fromBits(bits, result), false);
  EXPECT_EQ(result, value);
}

TEST(fromBits, size_tValue){
  size_t value = 0;
  int result;
  std::bitset<sizeof(size_t)*8> bits;
  ASSERT_EQ(toBits(bits, value), false);
  ASSERT_EQ(fromBits(bits, result), false);
  EXPECT_EQ(result, value);

  value = 1;
  bits.reset();
  ASSERT_EQ(toBits(bits, value), false);
  ASSERT_EQ(fromBits(bits, result), false);
  EXPECT_EQ(result, value);

  value = 127;
  bits.reset();
  ASSERT_EQ(toBits(bits, value), false);
  ASSERT_EQ(fromBits(bits, result), false);
  EXPECT_EQ(result, value);
}

TEST(fromBits, stringValue){
  std::string value = "abc";
  std::string result;
  std::bitset<sizeof(char)*8*3> bits;
  bool error = toBits<sizeof(char)*8*3, 3>(bits, value);
  ASSERT_EQ(error, false);
  error = fromBits<sizeof(char)*8*3, 3>(bits, result);
  ASSERT_EQ(error, false);
  ASSERT_EQ(result.size(), value.size());
  for(size_t i = 0; i < result.size(); ++i){
    EXPECT_EQ(result[i], value[i]);
  }
}

TEST(fromBits, charValue){
  char value[3] = {'a', 'b', 'c'};
  char result[3];
  std::bitset<sizeof(char)*8*3> bits;
  ASSERT_EQ(toBits(bits, value), false);
  ASSERT_EQ(fromBits(bits, result), false);
  for(size_t i = 0; i < 3; ++i){
    EXPECT_EQ(result[i], value[i]);
  }
}

/****************************
 ** conversion with offset **
 ****************************/

TEST(toAndFromBits, boolValue){
  std::bitset<10> bits;
  size_t length = 1;
  size_t offset = 3;
  bool value = true;
  bool result;

  ASSERT_EQ(toBits(bits, value, offset, length), false);
  ASSERT_EQ(fromBits(bits, result, offset, length), false);
  EXPECT_EQ(result, value);

  bits.reset();  
  offset = 7;
  ASSERT_EQ(toBits(bits, value, offset, length), false);
  ASSERT_EQ(fromBits(bits, result, offset, length), false);
  EXPECT_EQ(result, value);

  bits.reset();
  offset = 11;
  ASSERT_EQ(toBits(bits, value, offset, length), true);
  ASSERT_EQ(fromBits(bits, result, offset, length), true);
}


TEST(toAndFromBits, intValue){
  std::bitset<sizeof(int)*8*3> bits;
  size_t length = sizeof(int)*8;
  size_t offset = 3;
  int value = 127;
  int result;

  ASSERT_EQ(toBits(bits, value, offset, length), false);
  ASSERT_EQ(fromBits(bits, result, offset, length), false);
  EXPECT_EQ(result, value);

  bits.reset();  
  offset = 7;
  ASSERT_EQ(toBits(bits, value, offset, length), false);
  ASSERT_EQ(fromBits(bits, result, offset, length), false);
  EXPECT_EQ(result, value);

  bits.reset();
  offset = 120;
  ASSERT_EQ(toBits(bits, value, offset, length), true);
  ASSERT_EQ(fromBits(bits, result, offset, length), true);

  bits.reset();
  offset = 12;
  length = 7;
  ASSERT_EQ(toBits(bits, value, offset, length), false);
  ASSERT_EQ(fromBits(bits, result, offset, length), false);
  EXPECT_EQ(result, value);
}

TEST(toAndFromBits, stringValue){
  std::bitset<sizeof(char)*8*6> bits;
  const size_t numberOfBytes = 3;
  size_t offset = 2*8;
  std::string value = "abc";
  std::string result;

  bool error = toBits<sizeof(char)*8*6, numberOfBytes>(bits, value, offset);
  ASSERT_EQ(error, false);
  error = fromBits<sizeof(char)*8*6, numberOfBytes>(bits, result, offset);
  ASSERT_EQ(error, false);
  EXPECT_EQ(result, value);

  bits.reset();  
  offset = 3*8;
  error = toBits<sizeof(char)*8*6, numberOfBytes>(bits, value, offset);
  ASSERT_EQ(error, false);
  error = fromBits<sizeof(char)*8*6, numberOfBytes>(bits, result, offset);
  ASSERT_EQ(error, false);
  EXPECT_EQ(result, value);
  
  bits.reset();  
  offset = 4*8;
  error = toBits<sizeof(char)*8*6, numberOfBytes>(bits, value, offset);
  ASSERT_EQ(error, true);
  error = fromBits<sizeof(char)*8*6, numberOfBytes>(bits, result, offset);
  ASSERT_EQ(error, true);
}

TEST(toAndFromBits, charValue){
  std::bitset<sizeof(char)*8*6> bits;
  const size_t numberOfBytes = 3;
  size_t offset = 2*8;
  char value[3] = {'a', 'b', 'c'};
  char result[3];

  bool error = toBits<sizeof(char)*8*6, numberOfBytes>(bits, value, offset);
  ASSERT_EQ(error, false);
  error = fromBits<sizeof(char)*8*6, numberOfBytes>(bits, result, offset);
  ASSERT_EQ(error, false);
  for(size_t i = 0; i < numberOfBytes; ++i){
    EXPECT_EQ(result[i], value[i]);
  }

  bits.reset();  
  offset = 3*8;
  error = toBits<sizeof(char)*8*6, numberOfBytes>(bits, value, offset);
  ASSERT_EQ(error, false);
  error = fromBits<sizeof(char)*8*6, numberOfBytes>(bits, result, offset);
  ASSERT_EQ(error, false);
  for(size_t i = 0; i < numberOfBytes; ++i){
    EXPECT_EQ(result[i], value[i]);
  }
  
  bits.reset();  
  offset = 4*8;
  error = toBits<sizeof(char)*8*6, numberOfBytes>(bits, value, offset);
  ASSERT_EQ(error, true);
  error = fromBits<sizeof(char)*8*6, numberOfBytes>(bits, result, offset);
  ASSERT_EQ(error, true);
}
