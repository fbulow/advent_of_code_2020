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

int row(string const &bsp) //binary space partition
{
  return
    64*(bsp[0]=='B')+
    32*(bsp[1]=='B')+
    16*(bsp[2]=='B')+
    8*(bsp[3]=='B')+
    4*(bsp[4]=='B')+
    2*(bsp[5]=='B')+
    1*(bsp[6]=='B');
}

TEST(row, first)
{
  EXPECT_EQ(70, row("BFFFBBFRRR"));
}

int column(string const &bsp) //binary space partition
{
  char const one = 'R';
  return
    4*(bsp[7]==one)+
    2*(bsp[8]==one)+
    1*(bsp[9]==one);
}

TEST(column, first)
{
    EXPECT_EQ(7, column("BFFFBBFRRR"));
}


int seatId(string const &bsp) //binary space partition
{
  return row(bsp)*8+column(bsp);
}


TEST(Example, decode)
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


TEST(solution, a)
{
  auto const sut = getInput(input);
  int largest = seatId(sut[0]);
  for(auto const &x: sut)
    {
      auto s = seatId(x);
      if(largest<s)
	largest=s;
    }
  
  EXPECT_EQ(0, largest);
}

/*
TEST(solution, a)
{
  auto const sut = getInput(input);
  vector<int> c;
  c.reserve(sut.size());
  ASSERT_TRUE(c.empty());

  transform(sut.begin(),
	    sut.end(),
	    c.begin(),
	    decode);
  EXPECT_NE(136, *max_element(c.begin(), c.end()));
  
}
*/
