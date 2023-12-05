#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <optional>
#include <algorithm>
#include <fstream>
#include <numeric>
#include <sstream>
#include <string>
#include <set>
#include <limits>
using namespace std;

using Int = unsigned long long;

class Map
{
public:
  struct Range;
  std::vector<Range> r_;
  struct Range{
    Int destStart;
    Int sourceStart;
    Int length;

    Int back(Int x) const noexcept
    {
      return Range{sourceStart,
	  destStart,
	  length}(x);
      
    }
    Int operator()(Int x) const noexcept
    {
      auto d= x-sourceStart;
      if((d >=0) && (d<=length))
	return destStart+d;
      else
	return x;
    }
  };
public:
  Map() = default;
  Map& addRange(Int destStart,
		Int sourceStart,
		Int length)
  {
    r_.emplace_back(destStart,
		    sourceStart,
		    length);
    return *this;
  }
  Int operator()(Int i) const
  {
    for(auto &r: r_)
      {
	auto ri = r(i);
	if(i != ri)
	  return ri;
      }
    return i;
  }
};

struct Input
{
  vector<Int> seeds;
  vector<Map> maps;
};

istream & operator>>(istream &in, optional<Int> &n)
{
  Int slask;
  in>>slask;
  if(!in.fail())
    n = slask;
  else
    n.reset();
		
  return in;
}

istream& operator>>(istream& in, Input &x)
{
  string line;
  getline(in, line);
  istringstream seeds(line);
  string slask;
  seeds >> slask;
  auto seed = optional<Int>();
  seeds>>seed;
  while(seed)
    {
      x.seeds.push_back(seed.value());
      seed.reset();
      seeds>>seed;
    }
  getline(in, line);
  getline(in, line);
  getline(in, line);
  while(!line.empty())
    {
      x.maps.emplace_back();
      while(!line.empty())
	{
	  Int a,b,c;
	  istringstream(line) >> a>>b>>c;
	  x.maps.rbegin()->addRange(a,b,c);
	  getline(in, line);
	}
      getline(in, line);
      getline(in, line);
    }
  return in;
}

Int pushThrough(Int seed, vector<Map> const &maps)
{
  for(auto const &m :maps)
    seed = m(seed);
  return seed;
}


Int SolA(istream &&in)
{
  Input i;
  in>>i;
  
  for(auto &s:i.seeds)
    s=pushThrough(s, i.maps);

  return *min_element(i.seeds.begin(), i.seeds.end());
}


using namespace testing;

TEST(opt_Int, stream_toccccc)
{
  {
    optional<Int> sut;
    istringstream in("");
    in >> sut;
    EXPECT_FALSE(sut);
  }
  {
    optional<Int> sut;
    istringstream in("4");
    in >> sut;
    EXPECT_TRUE(sut);
    in >> sut;
    EXPECT_FALSE(sut);
  }
  {
    optional<Int> sut;
    istringstream in("4 ");
    in >> sut;
    EXPECT_TRUE(sut);
    in >> sut;
    EXPECT_FALSE(sut);
  }
}

TEST(solA, example)
{
  ASSERT_THAT(SolA(ifstream(EXAMPLE)), Eq(35));
  auto ans = SolA(ifstream(INPUT));
  ASSERT_THAT(ans, Gt(110956420));
  ASSERT_THAT(ans, Lt(2104394365));
  ASSERT_THAT(ans, Eq(340994526));
}

TEST(Input, example)
{
  Input sut;
  ifstream(EXAMPLE)>>sut;
  
  EXPECT_THAT(sut.seeds, ElementsAre(79, 14, 55, 13));
  EXPECT_THAT(sut.maps.size(), Eq(7));
}
TEST(pushThrough, exmaple)
{
  Input sut;
  ifstream(EXAMPLE)>>sut;

  EXPECT_THAT(pushThrough(79, sut.maps), Eq(82));
}

TEST(range, example)
{
  Map::Range sut{50, 98, 2};
  EXPECT_THAT(sut(98), Eq(50));  
}

TEST(map, example)
{
  auto sut = Map()
    .addRange(50, 98, 2)
    .addRange(52, 50, 48);

  EXPECT_THAT(sut(0),  Eq(0));
  EXPECT_THAT(sut(49), Eq(49));
  EXPECT_THAT(sut(50), Eq(52));
  EXPECT_THAT(sut(97), Eq(99));
  EXPECT_THAT(sut(98), Eq(50));
}

