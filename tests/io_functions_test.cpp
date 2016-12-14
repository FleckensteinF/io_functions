#include "gtest/gtest.h"
#include "io_functions/io_functions.h"

using namespace Tools;

TEST(fromVector, wrongDimensions) {
  std::vector<float> input = {0.f,0.f,0.f};
  Eigen::Matrix<float,1,2> result = IOFunctions::fromVector<Eigen::Matrix<float, 1, 2> >(input, "test");
  EXPECT_EQ(1, result(0,0));
  EXPECT_EQ(0, result(0,1));
}

TEST(fromVector, checkResult1Row) {
  std::vector<float> input = {0.f,1.f};
  Eigen::Matrix<float,1,2> result = IOFunctions::fromVector<Eigen::Matrix<float, 1, 2> >(input, "test");
  EXPECT_EQ(0, result(0,0));
  EXPECT_EQ(1, result(0,1));
}

TEST(fromVector, checkResult1Col) {
  std::vector<float> input = {0.f,1.f};
  Eigen::Matrix<float,2,1> result = IOFunctions::fromVector<Eigen::Matrix<float, 2, 1> >(input, "test");
  EXPECT_EQ(0, result(0,0));
  EXPECT_EQ(1, result(1,0));
}

TEST(fromVector, checkResultArbitrary) {
  std::vector<float> input = {0.f,1.f, 1.f,0.f};
  Eigen::Matrix<float,2,2> result = IOFunctions::fromVector<Eigen::Matrix<float, 2, 2> >(input, "test");
  EXPECT_EQ(0, result(0,0));
  EXPECT_EQ(1, result(0,1));
  EXPECT_EQ(1, result(1,0));
  EXPECT_EQ(0, result(1,1));
} 

TEST(toVector, checkResult){
  Eigen::Matrix<float, 2, 2> testMatrix(Eigen::Matrix2f::Identity());
  testMatrix(0,1) = 2;
  testMatrix(1,0) = 3;
  testMatrix(1,1) = 4;
  std::vector<float> result(4, 0.f);
  IOFunctions::toVector(result.begin(), testMatrix);
  EXPECT_NEAR(1, result[0], 1e-10);
  EXPECT_NEAR(2, result[1], 1e-10);
  EXPECT_NEAR(3, result[2], 1e-10);
  EXPECT_NEAR(4, result[3], 1e-10);

  result.resize(0);
  IOFunctions::toVector(result, testMatrix);
  EXPECT_NEAR(1, result[0], 1e-10);
  EXPECT_NEAR(2, result[1], 1e-10);
  EXPECT_NEAR(3, result[2], 1e-10);
  EXPECT_NEAR(4, result[3], 1e-10);
}

TEST(readFromFile, sizeTTest){
  std::vector<std::vector<size_t> > result;
  IOFunctions::readFromFile<size_t>("testmap.txt", result, ' ');
  ASSERT_EQ(12, result.size());
  EXPECT_EQ(5, result[0].size());
  EXPECT_EQ(5, result[1].size());
  EXPECT_EQ(5, result[2].size());
  EXPECT_EQ(5, result[3].size());
  EXPECT_EQ(5, result[4].size());
  EXPECT_EQ(5, result[5].size());
  EXPECT_EQ(5, result[6].size());
  EXPECT_EQ(5, result[7].size());
  EXPECT_EQ(5, result[8].size());
  EXPECT_EQ(5, result[9].size());
  EXPECT_EQ(5, result[10].size());
  EXPECT_EQ(5, result[11].size());  
}

TEST(readWriteToFile, vectorVector){
  std::vector<std::vector<float> > data(2), result;
  std::vector<float> buff(3);
  for(size_t i = 0; i < data.size(); ++i){
    for(size_t j = 0; j < buff.size(); ++j){
      buff[j] = i*buff.size()+j;
    }
    data[i] = buff;
  }
  
  std::string filename = "test.txt";
  IOFunctions::writeToFile<float>(filename, data, ' ');
  IOFunctions::readFromFile<float>(filename, result, ' ');

  ASSERT_EQ(data.size(), result.size());
  for(size_t i = 0; i < result.size(); ++i){
    ASSERT_EQ(data[i].size(), result[i].size());
    for(size_t j = 0; j < result[i].size(); ++j){
      EXPECT_EQ(data[i][j], result[i][j]);
    }
  }
}

class ReadWriteTest : public ::testing::Test{
protected:
  virtual void SetUp(){
    _filename = "test.txt";
    _dataPair.resize(2);
    std::vector<float> buff(3);
    for(size_t i = 0; i < _dataPair.size(); ++i){
      for(size_t j = 0; j < buff.size(); ++j){
	buff[j] = i*buff.size()+j;
      }
      _dataPair[i] = std::pair<std::string, std::vector<float> >("line_"+i, buff);
    }

    for(size_t j = 0; j < buff.size(); ++j){
      buff[j] = j;
    }
    _dataMap["line_1"] = buff;
    _dataMap["line_2"] = buff;

    _dataVector.resize(3);
    _dataVector[0] = buff;
    _dataVector[1] = buff;
    _dataVector[2] = buff;
  }

  std::string _filename;
  std::vector<std::pair<std::string, std::vector<float> > > _dataPair;
  std::map<std::string, std::vector<float> > _dataMap;
  std::vector<std::vector<float> > _dataVector;
};


TEST_F(ReadWriteTest, simpleVector){
  std::vector<int> result;
  std::vector<int> input;
  input.push_back(3);
  input.push_back(2);
  input.push_back(0);
  //std::string infoLine = "hello";
  //std::string resultingInfoLine;
  std::string filename = "vec.txt";
  IOFunctions::writeToFile<int>(filename, input, '\n');
  IOFunctions::readFromFile<int>(filename, result, '\n');
  
  //EXPECT_EQ(infoLine, resultingInfoLine);
  ASSERT_EQ(input.size(), result.size());
  for(size_t i = 0; i < result.size(); ++i){
    EXPECT_EQ(input[i], result[i]);
  }
}

TEST_F(ReadWriteTest, pairWithInfoLine){
  std::vector<std::pair<std::string, std::vector<float> > > result;
  std::string infoLine = "hello";
  std::string resultingInfoLine;
  IOFunctions::writeToFile<float>(_filename, _dataPair, ' ', infoLine);
  IOFunctions::readFromFile<float>(_filename, result, ' ', &resultingInfoLine);

  EXPECT_EQ(infoLine, resultingInfoLine);
  ASSERT_EQ(_dataPair.size(), result.size());
  for(size_t i = 0; i < result.size(); ++i){
    EXPECT_EQ(_dataPair[i].first, result[i].first);
    ASSERT_EQ(_dataPair[i].second.size(), result[i].second.size());
    for(size_t j = 0; j < result[i].second.size(); ++j){
      EXPECT_EQ(_dataPair[i].second[j], result[i].second[j]);
    }
  }
}

TEST_F(ReadWriteTest, pairWithoutInfoLine){
  std::vector<std::pair<std::string, std::vector<float> > > result;
  IOFunctions::writeToFile<float>(_filename, _dataPair, ' ');
  IOFunctions::readFromFile<float>(_filename, result, ' ');

  ASSERT_EQ(_dataPair.size(), result.size());
  for(size_t i = 0; i < result.size(); ++i){
    EXPECT_EQ(_dataPair[i].first, result[i].first);
    ASSERT_EQ(_dataPair[i].second.size(), result[i].second.size());
    for(size_t j = 0; j < result[i].second.size(); ++j){
      EXPECT_EQ(_dataPair[i].second[j], result[i].second[j]);
    }
  }
}

TEST_F(ReadWriteTest, vectorWithoutInfoLine){
  std::vector<std::vector<float> > result;
  IOFunctions::writeToFile<float>(_filename, _dataVector, ' ');
  IOFunctions::readFromFile<float>(_filename, result, ' ');

  ASSERT_EQ(_dataVector.size(), result.size());
  for(size_t i = 0; i < result.size(); ++i){
    ASSERT_EQ(_dataVector[i].size(), result[i].size());
    for(size_t j = 0; j < result[i].size(); ++j){
      EXPECT_EQ(_dataVector[i][j], result[i][j]);
    }
  }
}

TEST_F(ReadWriteTest, mapWithoutInfoLine){
  std::map<std::string, std::vector<float> > result;
  IOFunctions::writeToFile<float>(_filename, _dataMap, ' ');
  IOFunctions::readFromFile<float>(_filename, result, ' ');

  ASSERT_EQ(_dataMap.size(), result.size());
  std::map<std::string, std::vector<float> >::iterator it;
  std::vector<float> buff;
  for(it = result.begin(); it != result.end(); ++it){
    ASSERT_NE(_dataMap.end(), _dataMap.find(it->first));
    buff = _dataMap[it->first];
    ASSERT_EQ(it->second.size(), buff.size());
    for(size_t j = 0; j < it->second.size(); ++j){
      EXPECT_EQ(buff[j], it->second[j]);
    }
  }
}


TEST(stringOperations, endsWith){
  std::string test = "hallihallo";
  EXPECT_TRUE(IOFunctions::endsWith(test, "o"));
  EXPECT_TRUE(IOFunctions::endsWith(test, "allo"));
  EXPECT_FALSE(IOFunctions::endsWith(test, "i"));
  EXPECT_FALSE(IOFunctions::endsWith(test, "li"));
}

TEST(stringOperations, fileSuffix){
  std::string test1 = "hallo";
  std::string test2 = "halli.hallo";
  std::string test3 = "halle.halli.hallo";
  EXPECT_EQ("", IOFunctions::fileSuffix(test1));
  EXPECT_EQ("hallo", IOFunctions::fileSuffix(test2));
  EXPECT_EQ("hallo", IOFunctions::fileSuffix(test3));
}

TEST(stringOperations, fileName){
  std::string test1 = "ha.llo";
  std::string test2 = "halli/hallo.";
  std::string test3 = "halle/halli/hallo";
  EXPECT_EQ("ha", IOFunctions::fileName(test1));
  EXPECT_EQ("hallo", IOFunctions::fileName(test2));
  EXPECT_EQ("hallo", IOFunctions::fileName(test3));
}


TEST(stringOperations, containingFolderPathOf){
  std::string test1 = "hallo";
  std::string test2 = "halli/hallo";
  std::string test3 = "halle/halli/hallo";

  EXPECT_EQ("", IOFunctions::containingFolderPathOf(test1));
  EXPECT_EQ("halli", IOFunctions::containingFolderPathOf(test2));
  EXPECT_EQ("halle/halli", IOFunctions::containingFolderPathOf(test3));

}

TEST(stringOperations, containingFolderOf){
  std::string test1 = "hallo";
  std::string test2 = "halli/hallo";
  std::string test3 = "halle/halli/hallo";

  EXPECT_EQ("", IOFunctions::containingFolderOf(test1));
  EXPECT_EQ("halli", IOFunctions::containingFolderOf(test2));
  EXPECT_EQ("halli", IOFunctions::containingFolderOf(test3));

}

TEST(stringOperations, addTrailingSlash){
  std::string test1 = "directory";
  std::string test2 = "directory/";

  EXPECT_EQ(test2, IOFunctions::addTrailingSlash(test1));
  EXPECT_EQ(test2, IOFunctions::addTrailingSlash(test2));
}

TEST(stringOperations, stringSplit){
  std::string test1 = "hallo";
  std::string test2 = "halli.hallo";
  std::string test3 = "halle.halli.hallo";

  std::vector<std::string> result = IOFunctions::stringSplit(test1, ".");

  ASSERT_EQ(1, result.size());
  EXPECT_EQ(test1, result[0]);

  result = IOFunctions::stringSplit(test2, ".");
  ASSERT_EQ(2, result.size());
  EXPECT_EQ("halli", result[0]);
  EXPECT_EQ(test1, result[1]);

  result = IOFunctions::stringSplit(test3, ".");
  ASSERT_EQ(3, result.size());
  EXPECT_EQ("halle", result[0]);
  EXPECT_EQ("halli", result[1]);
  EXPECT_EQ(test1, result[2]);
}

//// don't know how to implement this wihtout creating
//// directories and files for testing...
//TEST(filesystemOperations, loadFilePathsFromDirectory){
//
////
////  // load paths to  all files in directory 
////  bool loadFilePathsFromDirectory(const std::string& directory, std::vector<std::string>& filePaths);
//
//}
//
//TEST(filesystemOperations, loadDirectory){
////
////  // loads directory with name directory
////  // returns true, if an error occured
////  // returns false otherwise
////  bool loadDirectory(const std::string& directory, boost::filesystem::path& directoryPath);
//
//}
//
//TEST(filesystemOperations, loadMakeDirectory){
////
////  // creates the directory if not already existent
////  void loadMakeDirectory(const std::string& directory, boost::filesystem::path& directoryPath);
////  void loadMakeDirectory(const std::string& directory);
////
//}


