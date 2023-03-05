#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <fstream>
#include <sstream>

#include "space.hh"


using namespace std;
using namespace testing;


int solutionA(string filename)
{
  auto empty = Space(filename);
  auto sut = empty;
  auto before = sut.size();
  sut.dropSnowflake({500,0});
  return sut.size() - before;
}

TEST(solutionA, example)
{
  EXPECT_THAT(solutionA(EXAMPLE), Eq(24));
  EXPECT_THAT(solutionA(INPUT),   Eq(674));
}

TEST(Space, lowestPoint)
{
  auto sut = Space(EXAMPLE);
  EXPECT_THAT(sut.lowestPoint(), Eq(9));
}

TEST(Space_ctor, drawSequence)
{
  auto sut = Space(EXAMPLE);
  ostringstream out;
  for(int y=0; y<=9; y++)
    {
      for(int x=494; x<=503; x++)
	out<<char( sut.contains({x,y})?'#':'.' );
      out << endl;
    }

  EXPECT_THAT(out.str(), Eq("..........\n"
			    "..........\n"
			    "..........\n"
			    "..........\n"
			    "....#...##\n"
			    "....#...#.\n"
			    "..###...#.\n"
			    "........#.\n"
			    "........#.\n"
			    "#########.\n"));
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
