
#include <AoC/getAllLines.hh>
#include <sstream>

#include <gtest/gtest.h>
using namespace std;

TEST(getAllLines, filename)
{
  vector<string> sut;
  {
    ifstream in(INPUT);
    sut = getAllLines(in);
  }
  EXPECT_EQ(sut, getAllLines(INPUT));
}

TEST(getAllLines, getInput)
{
  istringstream in("input");
  auto sut = getAllLines(in);
  EXPECT_EQ(std::string("input"), sut[0]);
  EXPECT_EQ(1, sut.size());
}

TEST(getAllLines, getInput_ending_with_endl)
{
  istringstream in("input\n");
  auto sut = getAllLines<std::string>(in);
  EXPECT_EQ(2, sut.size());
  EXPECT_EQ(std::string("input"), sut[0]);
  EXPECT_EQ(std::string(""), sut[1]);
}

TEST(getAllLines, default_input_file)
{
  auto sut = getAllLines<std::string>();
  EXPECT_EQ(std::string("input"), sut[0]);
  EXPECT_EQ(1, sut.size());
}


class Integer{
  int v;
public:
  Integer(string s)
  {
    istringstream in(s);
    in>>v;
  }
  operator int () const{return v;}
};

TEST(getAllLines, getNumbers)
{
  istringstream in("100\n200");
  
  auto sut = getAllLines<Integer>(in);
  EXPECT_EQ(100, sut[0]);
  EXPECT_EQ(200, sut[1]);
}

