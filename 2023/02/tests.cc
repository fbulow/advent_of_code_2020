#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <string>
#include <numeric>

using namespace std;

enum class Color {red, green, blue};

Color color(string const &s)
{
  if (s.starts_with("red"))
    return Color::red;
  else if (s.starts_with("green"))
    return Color::green;
  else if (s.starts_with("blue"))
    return Color::blue;
  else
    assert(false);
}

int possible(string s)
{
  istringstream in(s);
  string slask;
  in>>slask;
  assert(slask=="Game");
  string nrStr;
  in>>nrStr;//1:

  int count;
  string colorStr;
  in>>count>>colorStr;
  while(not colorStr.empty())
    {
      auto c = color(colorStr);
      if( (c==Color::red   && count>12) ||
	  (c==Color::green && count>13) ||
	  (c==Color::blue  && count>14) )
	return 0;
      colorStr.clear();
      in>>count>>colorStr;
    }
  int nr;
  istringstream(nrStr)>>nr;
  return nr;
}

int sol(istream &in, auto fcn)
{
  int ret{0};
  string s;
  getline(in,s);
  while(!s.empty())
    {
      ret+=fcn(s);
      getline(in,s);
    }
  return ret;
}

int solA(istream &in)
{
  return sol(in, possible);
}

int power(string s)
{
  istringstream in(s);
  string slask;
  in>>slask;
  assert(slask=="Game");
  string nrStr;
  in>>nrStr;//1:

  map<Color, int> ret;
  string colorStr;
  int count;
  in>>count>>colorStr;
  while(not colorStr.empty())
    {
      auto c = color(colorStr);
      ret[c] = max(ret[c], count);
      colorStr.clear();
      in>>count>>colorStr;
    }
  return accumulate(ret.begin(),
		    ret.end(),
		    1,
		    [](auto lhs, auto rhs)
		    {
		      return lhs * rhs.second;
		    });
}


int solB(istream &in)
{
  return sol(in, power);
}


using namespace testing;

TEST(possible, example)
{
  EXPECT_THAT(possible( "Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green" ), Eq(1));
  EXPECT_THAT(possible( "Game 2: 1 blue, 2 green; 3 green, 4 blue, 1 red; 1 green, 1 blue"), Eq(2));
  EXPECT_THAT(possible( "Game 3: 8 green, 6 blue, 20 red; 5 blue, 4 red, 13 green; 5 green, 1 red"), Eq(0));
  EXPECT_FALSE(possible( "Game 4: 1 green, 3 red, 6 blue; 3 green, 6 red; 3 green, 15 blue, 14 red"));
  EXPECT_TRUE(possible( "Game 5: 6 red, 1 blue, 3 green; 2 blue, 1 red, 2 green"));

  {
    ifstream in(EXAMPLE);
    EXPECT_THAT(solA(in), Eq(8));
  }

  {
    ifstream in(INPUT);
    EXPECT_THAT(solA(in), Eq(2541));
  }
  
}

TEST(power, example)
{
  EXPECT_THAT(power( "Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green" ), Eq(48));

  {
    ifstream in(EXAMPLE);
    EXPECT_THAT(solB(in), Eq(2286));
  }

  {
    ifstream in(INPUT);
    EXPECT_THAT(solB(in), Eq(66016));
  }
}
