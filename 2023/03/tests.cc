#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <string>
#include <numeric>

using namespace std;

struct Coord{
  int row;
  int col;
};
ostream& operator<<(ostream& out, Coord const &n)
{
  return out <<"Coord{"<<n.row<<","<<n.col<<"}";
}

bool operator==(Coord const &a, Coord const &b)
{
  return (a.row==b.row) && (a.col==b.col);
}

using Positions = vector<Coord>;
Positions range(int row, int startCol, int endCol)
{
  Positions ret;
  ret.reserve(endCol-startCol);
  while(startCol < endCol)
    ret.emplace_back(row, startCol++);
  return ret;
}

struct Number{
  int value;
  int row;
  int minCol;
  int maxCol;

  bool adjacent(Coord const &c) const
  {
    return
      (c.col >= minCol)
      && (c.col <= maxCol)
      && (c.row <= row+1)
      && (c.row >= row-1)
      ;
  }
};


bool isInt(char c){return (c>='0') && (c<='9');}

struct Numbers : vector<Number>
{
  Numbers() = default;
  Numbers& read(int row, string const &s)
  {
    auto start = find_if(s.begin(),
			 s.end(),
			 isInt);

    while(start < s.end())
      {    
	auto end = find_if(start,
			   s.end(),
			   [](auto x){return !isInt(x);});

	int val;
	istringstream({start, end}) >>val;
	emplace_back(val
		     ,row
		     ,distance(s.begin(), start) - 1
		     ,distance(s.begin(), end)
		     );
	start = find_if(end,
			s.end(),
			isInt);
      }
    return *this;
  }
};

bool isSymbol(char c)
{
  if(c=='.')
    return false;
  else
    return !isInt(c);
  
}

struct Symbols : Positions
{
  Symbols() = default;
  Symbols& read(int row, string const & s)
  {
    int col =0;
    for(char c:s)
      {
	if(isSymbol(c))
	  emplace_back(row, col);
	col++;
      }
    return *this;
  }
};

template<class T>
auto solA(T &&in)
{
  Symbols s;
  Numbers n;
  string str;
  getline(in, str);
  int row = 0;
  while(!str.empty())
    {
      n.read(row, str);
      s.read(row, str);

      str.clear();
      getline(in, str);
      row++;
    }

  auto adjacentToSymbol = [s](Number const & number)
  {
    return any_of(s.begin(),
		  s.end(),
		  [number](Coord const & c)
		  {return number.adjacent(c);});
  };

  int ret{0};
  for(auto const &num: n)
    if(adjacentToSymbol(num))
      ret+=num.value;
  return ret;
}


using namespace testing;

TEST(Input, example)
{
  ifstream in(EXAMPLE);
  EXPECT_THAT( solA(in), Eq(4361));
  EXPECT_THAT( solA(ifstream(INPUT)), Eq(526404));
}

TEST(Symbols, ctor)
{
  EXPECT_THAT(Symbols().read(0, "...2.."), ElementsAre());
  EXPECT_THAT(Symbols().read(0, ".*..2."), ElementsAre(Coord{0, 1}));
  EXPECT_THAT(Symbols().read(1, ".*..2."), ElementsAre(Coord{1, 1}));
  EXPECT_THAT(Symbols().read(1, "**..2"), ElementsAre(Coord{1,0}, Coord{1, 1}));
}

TEST(Positions, ctor)
{
  EXPECT_THAT(range(2, 5, 6), ElementsAre(Coord{2, 5}));
}

TEST(Numbers, row)
{
  auto sut = Numbers();
  sut.read(0, ".114..");
  ASSERT_THAT(sut.size(), Eq(1));
  EXPECT_THAT(sut[0].value, Eq(114));

  EXPECT_TRUE(sut[0].adjacent({0,0}));
  EXPECT_FALSE(sut[0].adjacent({0,5}));
  EXPECT_FALSE(sut[0].adjacent({2,0}));
}

TEST(Numbers, empty_row)
{
  auto sut = Numbers().read(0, "...");
  ASSERT_TRUE(sut.empty());
}

TEST(Numbers, two_numbers)
{
  auto sut = Numbers().read(0, "2.3");
  ASSERT_THAT(sut.size(), Eq(2));
}
