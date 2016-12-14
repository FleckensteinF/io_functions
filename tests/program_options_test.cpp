#include "gtest/gtest.h"
#include "program_options/program_options.h"

using namespace Tools;

class ModeParserTest : public ::testing::Test{
protected:
  virtual void SetUp(){
    std::vector<std::vector<std::string> > values;
    _p1 = new ProgramOptions::ModeParser("empty", "e", "no options", values);

    std::vector<std::string> buff = {"optionA", "A", "oA"};
    values.push_back(buff);
    buff = {"optionB", "B"};
    values.push_back(buff);
    buff = {"optionC"};
    values.push_back(buff);
    _p2 = new ProgramOptions::ModeParser("alpha", "a", "select letter", values);

    values.clear();
    buff = {"option1", "o1", "1"};
    values.push_back(buff);
    buff = {"option2", "o2", "2"};
    values.push_back(buff);
    _p3 = new ProgramOptions::ModeParser("numeric", "n", "select number", values);
  }

  ProgramOptions::ModeParser *_p1, *_p2, *_p3;

};


TEST_F(ModeParserTest, setMode){
  _p1->setMode("hallo");
  EXPECT_EQ(ProgramOptions::ModeParser::invalid, _p1->mode);

  _p2->setMode("hallo");
  EXPECT_EQ(ProgramOptions::ModeParser::invalid, _p2->mode);
  _p2->setMode("optionA");
  EXPECT_EQ("optionA", _p2->mode);
  _p2->setMode("A");
  EXPECT_EQ("optionA", _p2->mode);
  _p2->setMode("oA");
  EXPECT_EQ("optionA", _p2->mode);
  _p2->setMode("optionB");
  EXPECT_EQ("optionB", _p2->mode);
  _p2->setMode("B");
  EXPECT_EQ("optionB", _p2->mode);
  _p2->setMode("optionC");
  EXPECT_EQ("optionC", _p2->mode);
}

TEST_F(ModeParserTest, checkForInvalidValue){
  _p1->setMode("hallo");
  EXPECT_TRUE(_p1->checkForInvalidValue());

  _p2->setMode("A");
  EXPECT_FALSE(_p2->checkForInvalidValue());
  _p2->setMode("D");
  EXPECT_TRUE(_p2->checkForInvalidValue());

  _p3->setMode("2");
  EXPECT_FALSE(_p3->checkForInvalidValue());
  _p3->setMode("4");
  EXPECT_TRUE(_p3->checkForInvalidValue());
}

class ProgramOptionsTest : public ModeParserTest{
protected:
  virtual void SetUp(){
    ModeParserTest::SetUp();
    _modeParsers = {*_p1, *_p2, *_p3};
    _argc1 = 4;
    _argv1 = (char**)malloc(_argc1 * sizeof(char*));
    _argv1[0] = strdup(std::string("program_name").c_str());
    _argv1[1] = strdup(std::string("--configPath").c_str());
    _argv1[2] = strdup(std::string("hello").c_str());
    _argv1[3] = strdup(std::string("-h").c_str());
     _programOptions1 = new ProgramOptions(_argc1, _argv1);

    _argc2 = 6;
    _argv2 = (char**)malloc(_argc2 * sizeof(char*));
    _argv2[0] = strdup(std::string("program_name").c_str());
    _argv2[1] = strdup(std::string("-h").c_str());
    _argv2[2] = strdup(std::string("--alpha").c_str());
    _argv2[3] = strdup(std::string("B").c_str());
    _argv2[4] = strdup(std::string("-n").c_str());
    _argv2[5] = strdup(std::string("4").c_str());
    _programOptions2 = new ProgramOptions(_argc2, _argv2, _modeParsers);
  }

  virtual void TearDown(){
    delete _programOptions1;
    delete _programOptions2;

    ModeParserTest::TearDown();

    for(int i = 0; i < _argc1; ++i){
      free(_argv1[i]);
    }
    free(_argv1);
    for(int i = 0; i < _argc2; ++i){
      free(_argv2[i]);
    }
    free(_argv2);
  }

  int _argc1, _argc2;
  char **_argv1, **_argv2;
  std::vector<ProgramOptions::ModeParser> _modeParsers;
  ProgramOptions *_programOptions1, *_programOptions2;
};

TEST_F(ProgramOptionsTest, get){
  EXPECT_EQ("hello",_programOptions1->get<std::string>(_programOptions1->configPath));
  EXPECT_TRUE(_programOptions1->invalidMode);

  EXPECT_EQ("optionB", _programOptions2->getMode(_p2->name()));
  EXPECT_EQ(ProgramOptions::ModeParser::invalid, _programOptions2->getMode(_p3->name()));
  EXPECT_TRUE(_programOptions2->invalidMode);
}
//// program options
//template <typename ReturnType> ReturnType get(const std::string& valueName) const;
//  std::string getMode(const std::string& valueName) const;
//  virtual void parse(const int argc, const char** argv);
//  // set the mode value and check for invalid values
//  void parseModeValues();
