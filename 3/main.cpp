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


struct Hill :public vector<string>
{
  int width{0};
  char get(int row, int column)
  {
    return operator[](row)[column%width];
  }
};

Hill getInput(string filename)
{
  Hill ret;
  ifstream in(filename);
  string line;
  while(std::getline(in,line))
    {
      if(ret.width==0)
	ret.width = line.size();
      else
	  assert(ret.width == line.size());
      ret.push_back(line);
    }
  return ret;
}

auto constexpr example = "/home/fbulow/proj/advent_of_code_2020/3/example.txt";

TEST(get_input, example)
{
  auto const sut = getInput(example);
  EXPECT_EQ('.', sut[0][0]);
  EXPECT_EQ('#', sut[0][2]);
  EXPECT_EQ(11, sut.size());
  for(auto x:sut)
      ASSERT_EQ(11, sut.size());
}

bool hit(Hill const &data, unsigned int row, unsigned int column)
{
  return data[row][column]=='#';
}

TEST(example, hit_and_miss)
{
  auto const sut = getInput(example);
  EXPECT_FALSE(hit(sut, 0, 0));
  EXPECT_FALSE(hit(sut, 0, 1));
  EXPECT_TRUE (hit(sut, 0, 2));
}

struct Direction{
  unsigned int right;
  unsigned int down;
};

struct Position{
  unsigned int row;
  unsigned int column;
  Position operator+(Direction const & d)
  {
    return {row+d.down, column+d.right};
  }
};


TEST(step, make_steps)
{
  auto const sut = Position{0,0} + Direction{3,1};
  EXPECT_EQ(1, sut.row);
  EXPECT_EQ(3, sut.column);
}


