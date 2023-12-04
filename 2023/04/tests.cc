#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <algorithm>
#include <fstream>
#include <numeric>
#include <sstream>
#include <string>
#include <set>
using namespace std;

using Int = long int;

Int doublePoints(Int ret)
{
  if (ret==0)
    return 1;
  else
    return ret*2;
}


template<auto stepUp>
Int points(string const &row)
{
  auto in = istringstream(row);
  string s;
  auto lhs = set<string>{} ;
  in
    >>s //Card
    >>s // 1:
    >>s; // first value
  
  while(s!="|")
    {
      lhs.insert(s);
      in>>s;
    }

  Int ret = {0};
  in>>s;
  while(!s.empty())
    {
      if(lhs.contains(s))
	ret = stepUp(ret);
      s.clear();
      in>>s;
    }
  return ret;
}

Int justCount(Int ret)
{
  return ret+1;
}

using namespace testing;

TEST(points, example)
{
  ASSERT_THAT(points<doublePoints>("Card 1: 41 48 83 86 17 | 83 86  6 31 17  9 48 53"),
	      Eq(8));
}

TEST(justCount, example)
{
  ASSERT_THAT(points<justCount>("Card 1: 41 48 83 86 17 | 83 86  6 31 17  9 48 53"),
	      Eq(4));
}

auto solA(auto && in)
{
  Int ret{0};
  string s;
  getline(in,s);
  while(!s.empty())
    {
      ret+=points<doublePoints>(s);
      s.clear();
      getline(in,s);
  }
  return ret;
}

TEST(solA, example)
{
  ASSERT_THAT(solA(ifstream(EXAMPLE)), Eq(13));
  EXPECT_THAT(solA(ifstream(INPUT)), Eq(22193));
}

struct Pile
{
  int wins;
  int cards{1};
};


void increase(vector<Pile>::iterator it, Pile p)
{
  while(p.wins>0)
    {
      it->cards += p.cards;
      advance(it,1);
      p.wins--;
    }
}

int iterate(vector<Pile>::iterator b, vector<Pile>::iterator e)
{
  if(b==e)
    return 0;
  else
    {
      increase(next(b), *b);
      return b->cards + iterate(next(b), e);
    }
}

auto solB(istream &&in)
{
  vector<Pile> piles;
  string s;
  getline(in,s);
  while(!s.empty())
    {
      piles.emplace_back(points<justCount>(s));
      s.clear();
      getline(in,s);
    }
  auto ret =  iterate(piles.begin(), piles.end());
  return ret;
}

TEST(solB, example)
{
  ASSERT_THAT(solB(ifstream(EXAMPLE)),	Eq(30));
  EXPECT_THAT(solB(ifstream(INPUT)),	Eq(5625994));
}
