#include <gtest/gtest.h>
#include <vector>
#include <functional>
#include <string_view>
#include <fstream>
#include <iostream>
using namespace std;

TEST(hello, world)
{
  ASSERT_TRUE(true);
}


vector<string> getInput(string filename)
{
  vector<string> ret;
  ifstream in(filename);
  string line;
  optional<int> size;
  while(std::getline(in,line))
    {
      if(!size)
	size = line.size();
      else
	  assert(line.size()==size);
      ret.push_back(line);
    }
  return ret;
}

auto constexpr example = "/home/fbulow/proj/advent_of_code_2020/3/example.txt";

TEST(get_input, example)
{
  auto const sut = getInput(example);
  ASSERT_EQ('.', sut[0][0]);
  ASSERT_EQ('#', sut[0][2]);
  ASSERT_EQ(11, sut.size());
  for(auto x:sut)
      ASSERT_EQ(11, sut.size());
}

