#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <functional>
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

struct Rng{
  Int destStart;
  Int sourceStart;
  Int length;

  void onEdges(function<void(Int)> f) const
  {
    f(destStart-1);
    f(destStart);
    f(destStart+length);
    f(destStart+length+1);
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


class Map
{
public:
  std::vector<Rng> r_;
  Map invert() const
  {
    auto ret = Map();
    ret.r_.reserve(r_.size());
    transform(r_.rbegin(),
	      r_.rend(),
	      back_inserter(ret.r_),
	      [](Rng x)
	      {
		swap(x.destStart, x.sourceStart);
		return x;
	      });
    
    return ret;
  }
  
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

  void onEdges(function<void(Int)> f) const
  {
    for(auto &r: r_)
      r.onEdges(f);
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

using Maps = vector<Map>;

struct Input
{
  vector<Int> seeds;
  Maps maps;
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

Int solA(Input i)
{
  for(auto &s:i.seeds)
    s=pushThrough(s, i.maps);

  return *min_element(i.seeds.begin(), i.seeds.end());
}

Int solA(istream &&in)
{
  Input i;
  in>>i;

  return solA(i);
}

Maps inverse(Maps const &m)
{
  Maps ret(m.size());
  transform(m.rbegin(),
	    m.rend(),
	    ret.begin(),
	    [](Map const &m)
	    {
	      return m.invert();
	    });
  
  return ret;
}



class SeedRange
{
  Int min;
  Int max;
public:
  SeedRange(Int start, Int length)
    :min(start)
    ,max(start+length-1)
  {}

  
  void onEdges(function<void(Int)> f) const
  {
    f(min);
    f(max);
  }
  bool inside(Int x) const
  {
    return (x>=min) && (x<=max);
  }
};

void forEachSeedPair(vector<Int> seeds, function<void(Int start, Int length )>f)
{
  assert(seeds.size()%2==0);
  auto N = seeds.size()/2;
  for(size_t i = 0; i<N; i++)
    f(seeds[2*i], seeds[1+2*i]);
}

Int solB(istream &&in)
{
  Input a;
  in>>a;

  vector<SeedRange> seedRanges;
  forEachSeedPair(a.seeds,
		  [&seedRanges]
		  (Int a, Int b)
		  {
		    seedRanges.emplace_back(a,b);
		  });

  
  auto spam = inverse(a.maps);
  auto isOk = [spam, seedRanges](Int x)
  {
    auto seed = pushThrough(x, spam);
    return any_of(seedRanges.begin(),
		  seedRanges.end(),
		  [seed](SeedRange const &sr)
		  {
		    return sr.inside(seed);
		  });
  };
  
  Int ret = 1;
  while(!isOk(ret))
    ret++;
  return ret;
}

using namespace testing;

TEST(forEachSeedPair, example )
{
  vector<Int> ret;
  
  forEachSeedPair({79, 14, 55, 13},
		  [&ret]
		  (auto a,
		   auto b)
		  {ret.push_back(a+b);});
  EXPECT_THAT(ret, UnorderedElementsAre(79+14, 55+13));
}

TEST(SeedRange, onEdges)
{
  vector<Int> ret;
  auto sut =  SeedRange(79, 14);
  sut.onEdges([&ret](auto x){ret.push_back(x);});
  EXPECT_THAT(ret, UnorderedElementsAre(79, 92));
  
  EXPECT_FALSE(sut.inside(78));
  EXPECT_TRUE(sut.inside(79));
  EXPECT_TRUE(sut.inside(80));
  EXPECT_TRUE(sut.inside(92));
  EXPECT_FALSE(sut.inside(93));
}

TEST(solB, example)
{
  ASSERT_THAT(solB(ifstream(EXAMPLE)), Eq(46));
  auto ans = solB(ifstream(INPUT));
  ASSERT_THAT(ans, Lt(79552747));
  ASSERT_THAT(ans, Eq(52210644));
}


TEST(opt_Int, stream_to)
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
  ASSERT_THAT(solA(ifstream(EXAMPLE)), Eq(35));
  auto ans = solA(ifstream(INPUT));
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
TEST(pushThrough_inverse, exmaple)
{
  Input sut;
  ifstream(EXAMPLE)>>sut;

  EXPECT_THAT(pushThrough(79, sut.maps),
	      Eq(82));
  EXPECT_THAT(pushThrough(82, inverse(sut.maps)),
	      Eq(79));
}

TEST(range, example)
{
  Rng sut{50, 98, 2};
  EXPECT_THAT(sut(98), Eq(50));  
}

TEST(map, example)
{
  auto sut = Map()
    .addRange(50, 98, 2)
    .addRange(52, 50, 48);

  EXPECT_THAT(sut(0 ), Eq(0 ));
  EXPECT_THAT(sut(49), Eq(49));
  EXPECT_THAT(sut(50), Eq(52));
  EXPECT_THAT(sut(97), Eq(99));
  EXPECT_THAT(sut(98), Eq(50));

  auto s2 = sut.invert();
  
  EXPECT_THAT(s2(0 ), Eq(0 ));
  EXPECT_THAT(s2(49), Eq(49));
  EXPECT_THAT(s2(52), Eq(50));
  EXPECT_THAT(s2(99), Eq(97));
  EXPECT_THAT(s2(50), Eq(98));
}

TEST(Rng, onEdges)
{
  vector<Int> ret;
  Rng(50, 98, 2).onEdges([&ret](Int x){ret.push_back(x);});

  EXPECT_THAT(
	      ret,
	      UnorderedElementsAre(49, 50, 50+2, 50+2+1)
	      );
}
