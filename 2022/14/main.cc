#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <fstream>
#include <sstream>

#include "space.hh"


using namespace std;
using namespace testing;

void washLine(string &s)
{
  for(char &c:s)
    switch(c)
      {
      case '-':
      case '>':
      case ',':
	c=' ';
      default:
	{}
      }
}

TEST(Space, drawSequence)
{
  vector<Coord> data{{498,4},
		     {498,6},
		     {496,6}};
  Space sut;
  sut.drawSequence(data);
  EXPECT_THAT(sut.size(), Eq(5));
}


TEST(Space, drawLine)
{
  Space sut;
  Coord a(498,4);
  Coord b(498,6);
  Coord c(496,6);

  EXPECT_THAT(sut.size(), Eq(0));
  sut.drawLine(a,b);
  EXPECT_THAT(sut.size(), Eq(3));
  sut.drawLine(b,c);
  EXPECT_THAT(sut.size(), Eq(5));
}
  
TEST(washLine, example)
{
  string s = "503,4 -> 502,4";
  washLine(s);

  istringstream in(s);
  int a,b,c,d;
  in>>a>>b>>c>>d;

  EXPECT_THAT(a, Eq(503));
  EXPECT_THAT(b, Eq(4));
  EXPECT_THAT(c, Eq(502));
  EXPECT_THAT(d, Eq(4));
}
