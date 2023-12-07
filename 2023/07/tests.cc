#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <algorithm>
#include <fstream>
#include <numeric>
#include <sstream>
#include <string>
#include <set>
using namespace std;

using Int = long long unsigned int;

struct Hand : string
{
  Hand() = default;
  Hand(char const * c)
    : string{c[0], c[1], c[2], c[3], c[4]}
  {}
};

ostream &operator<<(ostream &out, Hand const &h)
{
  string const &a = h;
  return out << a;
}


using Card = char;
using Type = int;

constexpr Type High_card	= 1;
constexpr Type One_pair		= 2;
constexpr Type Two_pair		= 3;
constexpr Type Three_of_a_kind	= 4;
constexpr Type Full_house 	= 5;
constexpr Type Four_of_a_kind	= 6;
constexpr Type Five_of_a_kind	= 7;


int largestCount(map<Card, int> const &s)
{
  int ret = 0;
  for(auto &x: s)
    ret = max(ret, x.second);
  return ret;
}

Type type(Hand const&h)
{
  map<Card, int> s;
  for(Card c:h)
    s[c]++;
  switch(s.size())
    {
    case 1:
      return Five_of_a_kind;
    case 2:
      {
	switch(largestCount(s))
	  {
	  case 4:
	    return Four_of_a_kind;
	  case 3:
	    return Full_house;
	  }
      }
    case 3:
      {
	switch(largestCount(s))
	  {
	  case 3:
	    return Three_of_a_kind;
	  case 2:
	    return Two_pair;
	  }
      }
    case 5:
      return High_card;
    }

  
  return One_pair;
}

int cardValue(Card c)
{
  constexpr string_view  s("AKQJT98765432");
  return s.size()-s.find(c);
}

bool pairCompare(auto lh, auto rh)
{
  if(*lh==*rh)
    return pairCompare(next(lh), next(rh));
  else 
    return (cardValue(*lh) < cardValue(*rh));

}

bool rhHigherHasCard(Hand const & lh, Hand const & rh)
{
  auto l = lh.cbegin();
  auto r = rh.cbegin();

  return pairCompare(lh.begin(), rh.begin());
}

bool operator<(Hand const &lhs, Hand const &rhs)
{
  assert(lhs.size()==5);
  assert(rhs.size()==5);
  
  auto lt = type(lhs);
  auto rt = type(rhs);
  if(lt<rt)
    return true;
  else if (lt>rt)
    return false;
  else
    return rhHigherHasCard(lhs, rhs);
}

auto solA(istream &&in)
{
  map<Hand, Int> m;

  string s;
  Hand hand;
  Int bid;

  while(getline(in,s))
    {
      if(!s.empty());
      {
	istringstream in(s);
	in>> hand >> bid;
	m[hand] = bid;
      }
    }

  Int ret{0};
  int rank=1;

  auto it = m.begin();
  while(it!=m.end())
    ret += (rank++) * (it++)->second;
  return ret;
}


using namespace testing;

TEST(solA, example)
{
  ASSERT_THAT(solA(ifstream(EXAMPLE)), Eq(6440));
}

TEST(solA, input)
{
  auto ret = solA(ifstream(INPUT));
  ASSERT_THAT(ret, Gt(245604744));
  ASSERT_THAT(ret, Eq(248105065));
}

TEST(operatorLt_of_Hand, example)
{
  set<Hand> s{
    "32T3K",
    "T55J5",
    "KK677",
    "KTJJT",
    "QQQJA"};

  EXPECT_THAT(s, ElementsAre("32T3K", "KTJJT", "KK677", "T55J5", "QQQJA"));
}
TEST(operatorLt_of_Hand, own)
{
  EXPECT_TRUE( Hand("22226") < Hand("2222A"));
}

TEST(rhHigherHasCard, example)
{
  EXPECT_TRUE(rhHigherHasCard("23457", "234A7"));
  EXPECT_FALSE(rhHigherHasCard("234A7", "23457"));
}

TEST(cardValue, examples)
{
 EXPECT_THAT(cardValue('K'), Lt(cardValue('A')));
 EXPECT_THAT(cardValue('Q'), Lt(cardValue('K')));
 EXPECT_THAT(cardValue('J'), Lt(cardValue('Q')));
 EXPECT_THAT(cardValue('T'), Lt(cardValue('J')));
 EXPECT_THAT(cardValue('9'), Lt(cardValue('T')));
 EXPECT_THAT(cardValue('8'), Lt(cardValue('9')));
 EXPECT_THAT(cardValue('7'), Lt(cardValue('8')));
 EXPECT_THAT(cardValue('6'), Lt(cardValue('7')));
 EXPECT_THAT(cardValue('5'), Lt(cardValue('6')));
 EXPECT_THAT(cardValue('4'), Lt(cardValue('5')));
 EXPECT_THAT(cardValue('3'), Lt(cardValue('4')));
 EXPECT_THAT(cardValue('2'), Lt(cardValue('3')));
}

TEST(type, examples)
{
  EXPECT_THAT(type("AAAAA"), Eq(Five_of_a_kind));
  EXPECT_THAT(type("AA8AA"), Eq(Four_of_a_kind));
  EXPECT_THAT(type("23456"), Eq(High_card));
  EXPECT_THAT(type("23332"), Eq(Full_house));
  EXPECT_THAT(type("TTT98"), Eq(Three_of_a_kind));
  EXPECT_THAT(type("23432"), Eq(Two_pair));
  EXPECT_THAT(type("23456"), Eq(High_card));
}
