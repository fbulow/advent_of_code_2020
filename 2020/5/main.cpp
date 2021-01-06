#include <gtest/gtest.h>

#include <algorithm>
#include <fstream>
//#include <functional>
#include <iostream>
//#include <regex>
//#include <string_view>
#include <vector>

using namespace std;

TEST(hello, world)
{
  ASSERT_TRUE(true);
}

unsigned int seatId(string const &bsp) //binary space partition
{
  unsigned int ret{0};
  for(char x:bsp)
    {
      ret*=2;
      if(x=='B' or x=='R')
	ret++;
    }

  return ret;
}


unsigned int row(string const &bsp) //binary space partition
{
  return seatId(bsp)/8;
}

unsigned int column(string const &bsp) //binary space partition
{
  return seatId(bsp)%8;
}

TEST(row, first)
{
  EXPECT_EQ(70, row("BFFFBBFRRR"));
}


TEST(column, first)
{
    EXPECT_EQ(7, column("BFFFBBFRRR"));
}

TEST(Example, seatId)
{
  EXPECT_EQ(357, seatId("FBFBBFFRLR"));
  EXPECT_EQ(567, seatId("BFFFBBFRRR"));
  EXPECT_EQ(119, seatId("FFFBBBFRRR"));
  
  
}

vector<string> getInput(string const &filename)
{
  vector<string> ret;
  ifstream in(filename);
  assert(in.is_open());
  string line;
  while(getline(in, line))
      ret.push_back(line);
  
  return ret;
}

TEST(getInput, first_and_last)
{
  auto const sut = getInput(input);
  EXPECT_EQ("FFBFFFBLLL", sut[0]);
  EXPECT_EQ("FBBBFFFLLR", sut[sut.size()-1]);
}


TEST(solution, a_and_b)
{
  auto const sut = getInput(input);
  vector<unsigned int> x;
  x.resize(sut.size());

  transform(sut.begin(),
	    sut.end(),
	    x.begin(),
	    seatId);
  ASSERT_EQ(880, *max_element(x.begin(), x.end())); //A

  sort(x.begin(), x.end());

  for(size_t i=1;i<x.size();i++)
    if((x[i]-x[i-1])==2)
      ASSERT_EQ(731, (x[i-1]+x[i])/2); //B
}

