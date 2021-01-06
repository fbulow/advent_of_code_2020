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
  char get(int row, int column) const
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
  EXPECT_EQ('.', sut.get(0,0));
  EXPECT_EQ('#', sut.get(0,2));
  EXPECT_EQ(11, sut.size());
  for(auto x:sut)
      ASSERT_EQ(11, sut.size());
}

bool hit(Hill const &data, unsigned int row, unsigned int column)
{
  return data.get(row,column)=='#';
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
  
  void operator+=(Direction const & d)
  {
    row+=d.down;
    column+=d.right;
  }
};


TEST(step, make_steps)
{
  auto const sut = Position{0,0} + Direction{3,1};
  EXPECT_EQ(1, sut.row);
  EXPECT_EQ(3, sut.column);
}

TEST(step, make_step_increment)
{
  auto sut = Position{0,0};
  sut+=Direction{3,1};
  EXPECT_EQ(1, sut.row);
  EXPECT_EQ(3, sut.column);
}



unsigned int solve(Hill const &h, Direction const & d)
{
  unsigned int count{0};
  Position p{0,0};
  while(p.row < h.size())
    {
      if(hit(h, p.row, p.column))
	count++;
      p+=d;
    }
  return count;
}

TEST(a, solve)
{
  ASSERT_EQ(7, solve(getInput(example), {3,1}));
}

auto constexpr input = "/home/fbulow/proj/advent_of_code_2020/3/input";

TEST(input, solve)
{
  ASSERT_EQ(237, solve(getInput(input), {3,1}));
}

unsigned int multipleSlopes(Hill const &h)
{
  unsigned int ret = 1;
  for(auto d : {Direction{1,1},
		Direction{3,1},
		Direction{5, 1},
		Direction{7, 1},
		Direction{1, 2}})
    ret*=solve(h, d);
  return ret;
}

TEST(multipleSlopes, example)
{
  ASSERT_EQ(336, multipleSlopes(getInput(example)));
}

TEST(multipleSlopes, input)
{
  ASSERT_EQ(2106818610, multipleSlopes(getInput(input)));
}
