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
  Room ret(other.size()+2);
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

struct Coord{
  int row;
  int column;
  Coord operator+(Coord const &other )
  {
    return {
      row+other.row,
      column+other.column};
  }
};

int countAdjecent(Room const &r, Coord const &c)
{
  vector<Coord> adjecent{
    {-1, -1},
    {-1,  0},
    {-1, +1},
    { 0, -1},
    { 0, +1},
    {+1, -1},
    {+1,  0},
    {+1, +1}};

  return count_if(adjecent.begin(),
		  adjecent.end(),
		  [=](auto coord)
		  {
		    auto checkSeat = coord+c;
		    return '#' == r[checkSeat.row][checkSeat.column];
		  });
    
}

Room step(Room const &r)
{
  Room ret{r};
  
  for(int row = 1; row < r.size()-1; row++)
    for(int column = 1; column < r[0].size()-1; column++)
      {
	if(r[row][column]!='.')
	  {
	    auto a = countAdjecent(r, {row,column});
	    if(0==a)
	      ret[row][column]='#';
	    else if(a>=4)
	      ret[row][column]='L';
	    else
	      ret[row][column]=r[row][column];
	  }
	else
	  ret[row][column]=r[row][column];
      }
  return ret;
}


TEST(step, one)
{
  auto sut = step(frameIt(getRoom(EXAMPLE)));
  auto i =0;
  
  EXPECT_EQ("............", sut[i++]);
  EXPECT_EQ(".#.##.##.##.", sut[i++]);
  EXPECT_EQ(".#######.##.", sut[i++]);
  EXPECT_EQ(".#.#.#..#...", sut[i++]);
  EXPECT_EQ(".####.##.##.", sut[i++]);
  EXPECT_EQ(".#.##.##.##.", sut[i++]);
  EXPECT_EQ(".#.#####.##.", sut[i++]);
  EXPECT_EQ("...#.#......", sut[i++]);
  EXPECT_EQ(".##########.", sut[i++]);
  EXPECT_EQ(".#.######.#.", sut[i++]);
  EXPECT_EQ(".#.#####.##.", sut[i++]);
  EXPECT_EQ("............", sut[i++]);
}
TEST(step, two)
{
  auto sut = step(step(frameIt(getRoom(EXAMPLE))));

  auto i=0;
  EXPECT_EQ("............", sut[i++]);
  EXPECT_EQ(".#.LL.L#.##.", sut[i++]);
  EXPECT_EQ(".#LLLLLL.L#.", sut[i++]);
  EXPECT_EQ(".L.L.L..L...", sut[i++]);
  EXPECT_EQ(".#LLL.LL.L#.", sut[i++]);
  EXPECT_EQ(".#.LL.LL.LL.", sut[i++]);
  EXPECT_EQ(".#.LLLL#.##.", sut[i++]);
  EXPECT_EQ("...L.L......", sut[i++]);
  EXPECT_EQ(".#LLLLLLLL#.", sut[i++]);
  EXPECT_EQ(".#.LLLLLL.L.", sut[i++]);
  EXPECT_EQ(".#.#LLLL.##.", sut[i++]);
  EXPECT_EQ("............", sut[i++]);
  
}

TEST(step, three)
{
  auto sut = step(step(step(frameIt(getRoom(EXAMPLE)))));

  auto i=0;
  EXPECT_EQ("............", sut[i++]);
  EXPECT_EQ(".#.##.L#.##.", sut[i++]);
  EXPECT_EQ(".#L###LL.L#.", sut[i++]);
  EXPECT_EQ(".L.#.#..#...", sut[i++]);
  EXPECT_EQ(".#L##.##.L#.", sut[i++]);
  EXPECT_EQ(".#.##.LL.LL.", sut[i++]);
  EXPECT_EQ(".#.###L#.##.", sut[i++]);
  EXPECT_EQ("...#.#......", sut[i++]);
  EXPECT_EQ(".#L######L#.", sut[i++]);
  EXPECT_EQ(".#.LL###L.L.", sut[i++]);
  EXPECT_EQ(".#.#L###.##.", sut[i++]);
  EXPECT_EQ("............", sut[i++]);
  
}

int solveA(string filename)
{
  auto a = frameIt(getRoom(filename));
  auto b = step(a);
  while(a!=b)
    {
      a=b;
      b=step(a);
    }
  vector<int> count(a.size());
  transform(a.begin(),
	    a.end(),
	    count.begin(),
	    [](string x){
	      return count_if(x.begin(),
			      x.end(),
			      [](auto c)
			      {
				return '#'==c;
			      });
	    });
  return accumulate(count.begin(), count.end(), 0);
}

TEST(solve, a)
{
  EXPECT_EQ(37, solveA(EXAMPLE));
  //cout<< "solveA "<<solveA(INPUT)<<endl;
}

