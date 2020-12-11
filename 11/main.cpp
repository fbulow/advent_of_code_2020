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
  Coord operator+(Coord const &other ) const
  {
    Coord ret = *this;
    ret+=other;
    return ret;
  }
  void operator+=(Coord const &other )
  {
    row+=other.row;
    column+=other.column;
  }
  auto operator<=>(const Coord&) const = default;
  
};

TEST(Coord, less_than)
{
  EXPECT_TRUE(Coord(1,0) > Coord(0,0) );
}

vector<Coord> const & directions(){
  static vector<Coord>ret {
    Coord{-1, -1},
    Coord{-1,  0},
    Coord{-1, +1},
    Coord{ 0, -1},
    Coord{ 0, +1},
    Coord{+1, -1},
    Coord{+1,  0},
    Coord{+1, +1}};
  return ret;
}

char nearSeat(Coord start, Room const &r, Coord const &dir)
{
  start+=dir;
  return r[start.row][start.column];
}

int countAdjecent(Room const &r, Coord const &c, auto ns)
{
  auto d = directions();
  
  return count_if(d.begin(),
		  d.end(),
		  [=](auto direction)
		  {
		    return '#' == ns(c, r, direction);
		  });
}
int countAdjecentA(Room const &r, Coord const &c)
{
  return countAdjecent(r, c, nearSeat);
}


void step(Room const &r, Room &ret, auto countAdjecent)
{
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
}

Room step(Room const &r, auto countAdjecent)
{
  Room ret(r);
  step(r,ret, countAdjecent);
  return ret;
}

Room stepA(Room const &r)
{
  return step(r,countAdjecentA);
}
	   

TEST(step, one)
{
  auto sut = stepA(frameIt(getRoom(EXAMPLE)));
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
TEST(stepA, two)
{
  auto sut = stepA(stepA(frameIt(getRoom(EXAMPLE))));

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

TEST(stepA, three)
{
  auto sut = stepA(stepA(stepA(frameIt(getRoom(EXAMPLE)))));

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


int solve(string filename, auto countAdjecent)
{
  auto a = frameIt(getRoom(filename));
  auto b = step(a, countAdjecent);
  while(a!=b)
    {
      step(b,a, countAdjecent);
      step(a,b, countAdjecent);
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

int solveA(string filename)
{
  return solve(filename, countAdjecentA);
}

TEST(solve, a)
{
  EXPECT_EQ(37, solveA(EXAMPLE));
  //  EXPECT_EQ(2254, solveA(INPUT));//Strangely slow.
}

bool onBoard(Coord const &c, Room const &r)
{
  return
    (0 <= c.row)    and (c.row < r.size()) and
    (0 <= c.column) and (c.column < r[0].size());
}

char nextSeat(Coord start, Room const &r, Coord const &dir)
{
  start+=dir;
  while(onBoard(start, r))
    if(r[start.row][start.column] != '.')
      return r[start.row][start.column];
    else
      start+= dir;
  return '.';
}

TEST(nextSeat, stickprov)
{
  Room sut{
    "...."s,
    ".L.."s,
    "...."s,
    ".#.L."s
  };
  EXPECT_EQ('#', nextSeat({1,1}, sut, {1,0}));
  EXPECT_EQ('.', nextSeat({1,1}, sut, {-1,0}));
  EXPECT_EQ('L', nextSeat({1,1}, sut, {1,1}));
}
