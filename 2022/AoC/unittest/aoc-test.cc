
#include <AoC/getAllLines.hh>
#include <sstream>

#include <gtest/gtest.h>
using namespace std;

TEST(getAllLines, getInput)
{
  istringstream in("input");
  auto sut = getAllLines<std::string>(in);
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
