#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <limits>
#include <numeric>

using namespace std;

using Room = vector<string>;

Room getRoom(string const &filename)
{
  Room ret;
  ifstream in(filename);
  assert(in.is_open());
  string line;
  while(getline(in, line))
    ret.push_back(line);
  return ret;
}

TEST(hello, world)
{
  EXPECT_EQ(10, getRoom(EXAMPLE).size());
  auto i =0;
  EXPECT_EQ("L.LL.LL.LL", getRoom(EXAMPLE)[i++]);
  EXPECT_EQ("LLLLLLL.LL", getRoom(EXAMPLE)[i++]);
  EXPECT_EQ("L.L.L..L..", getRoom(EXAMPLE)[i++]);
  EXPECT_EQ("LLLL.LL.LL", getRoom(EXAMPLE)[i++]);
  EXPECT_EQ("L.LL.LL.LL", getRoom(EXAMPLE)[i++]);
  EXPECT_EQ("L.LLLLL.LL", getRoom(EXAMPLE)[i++]);
  EXPECT_EQ("..L.L.....", getRoom(EXAMPLE)[i++]);
  EXPECT_EQ("LLLLLLLLLL", getRoom(EXAMPLE)[i++]);
  EXPECT_EQ("L.LLLLLL.L", getRoom(EXAMPLE)[i++]);
  EXPECT_EQ("L.LLLLL.LL", getRoom(EXAMPLE)[i++]);
}

Room frameIt(Room other)
{
  auto c = other[0].size();
  Room ret(c+2);
  transform(other.begin(),
	    other.end(),
	    next(ret.begin()),
	    [](string const& x)
	    {
	      return "." + x + ".";
	    });

  auto emptyLine=string(ret[1].size(),'.');
  
  ret[0]		= emptyLine;
  ret[ret.size()-1]	= emptyLine;

  return ret;
  
}

TEST(frameIt, example)
{
  auto const sut = frameIt(getRoom(EXAMPLE));
  EXPECT_EQ(12, sut.size());
  auto i =0;
  EXPECT_EQ("............", sut[i++]);
  EXPECT_EQ(".L.LL.LL.LL.", sut[i++]);
  EXPECT_EQ(".LLLLLLL.LL.", sut[i++]);
  EXPECT_EQ(".L.L.L..L...", sut[i++]);
  EXPECT_EQ(".LLLL.LL.LL.", sut[i++]);
  EXPECT_EQ(".L.LL.LL.LL.", sut[i++]);
  EXPECT_EQ(".L.LLLLL.LL.", sut[i++]);
  EXPECT_EQ("...L.L......", sut[i++]);
  EXPECT_EQ(".LLLLLLLLLL.", sut[i++]);
  EXPECT_EQ(".L.LLLLLL.L.", sut[i++]);
  EXPECT_EQ(".L.LLLLL.LL.", sut[i++]);
  EXPECT_EQ("............", sut[i++]);
}
