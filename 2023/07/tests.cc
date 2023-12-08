#include <algorithm>
#include <fstream>
#include <numeric>
#include <sstream>
#include <string>
#include <set>
#include <map>
#include <cassert>
#include <vector>
using namespace std;

using Int = long long unsigned int;
using Card = char;
using Type = int;
using Histogram = map<Card, int>;
struct Hand : string
{
  Hand() = default;
  Hand(char const * c)
    : string{c[0], c[1], c[2], c[3], c[4]}
  {}
  operator Histogram() const
  {
    map<Card, int> ret;
    for(Card c:*this)
      ret[c]++;
    return ret;
  }
};

ostream &operator<<(ostream &out, Hand const &h)
{
  string const &a = h;
  return out << a;
}

void PrintTo(Hand const &h, std::ostream* out)
{
  string const &s = h;
  (*out) << h;
}

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

auto largestCount(vector<int> const &s)
{
  return *s.rbegin();
}


Type type(vector<int> const &s)
{
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

Type type(Histogram const &h)
{
  vector<int> s;
  transform(h.begin(),
	    h.end(),
	    back_inserter(s),
	    [](auto const &x){return x.second;});
  sort(s.begin(), s.end());
  return type(s);
}

int cardValue(Card c, string_view s)
{
  return s.size()-s.find(c);
}

bool pairCompare(auto lh, auto rh, auto order)
{
  if(*lh==*rh)
    return pairCompare(next(lh), next(rh), order);
  else 
    return (cardValue(*lh, order) < cardValue(*rh, order));
}

bool rhHigherHasCard(Hand const & lh, Hand const & rh, string_view order)
{
  return pairCompare(lh.begin(), rh.begin(), order);
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
    return rhHigherHasCard(lhs, rhs, string_view("AKQJT98765432"));
}


auto signatureB(Histogram const &s)
{
  vector<int> ret;
  int jCount{0};
  for(auto const & x:s)
    if (x.first=='J')
      jCount+=x.second;
    else
      ret.push_back(x.second);
  if(ret.empty())
    ret.push_back(jCount);
  else
    {
      sort(ret.begin(), ret.end());
      (*ret.rbegin())+=jCount;
    }
  return ret;
}

Type typeB(Histogram s)
{
  return type(signatureB(s));
}


bool lessB(Hand const &lhs, Hand const &rhs)
{
  auto lt = typeB(lhs);
  auto rt = typeB(rhs);
  if(lt<rt)
    return true;
  else if (lt>rt)
    return false;
  else
    return rhHigherHasCard(lhs, rhs, string_view("AKQT98765432J"));
}

auto sol(istream &&in, auto &&m)
{
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

auto solB(istream &&in)
{
  auto lb = [](auto const& a, auto const& b){return lessB(a,b);};
  map<Hand, Int, decltype(lb)> s;
  return sol(move(in), move(s));
}

auto solA(istream &&in)
{
  return sol(move(in), map<Hand, Int>());
}


#include <gtest/gtest.h>
#include <gmock/gmock.h>

using namespace testing;

TEST(signatureB, several)
{
  EXPECT_THAT(signatureB(Hand("23456")), ElementsAre(1,1,1,1,1));
  EXPECT_THAT(signatureB(Hand("J3456")), ElementsAre(1,1,1,2));
  EXPECT_THAT(signatureB(Hand("22456")), ElementsAre(1,1,1,2));
}

TEST(solB, input)
{
  EXPECT_THAT(solB(ifstream(EXAMPLE)), Eq(5905));
  EXPECT_THAT(solB(ifstream(INPUT)), Eq(249515436));
}

TEST(lessB, examples)
{
  ASSERT_THAT(typeB(Hand("QQQJA")), Eq(Four_of_a_kind));  
  ASSERT_THAT(typeB(Hand("T55J5")), Eq(Four_of_a_kind));  
  EXPECT_TRUE(lessB("T55J5", "QQQJA"));

  EXPECT_THAT(typeB(Hand("T55J5")), Eq(Four_of_a_kind));
  EXPECT_TRUE(lessB("KK677", "T55J5"));
}

TEST(solB, example)
{
  auto lb = [](auto const& a, auto const& b){return lessB(a,b);};
  set<Hand, decltype(lb)> s{
    "32T3K",
    "KK677",
    "T55J5",
    "KTJJT",
    "QQQJA"
  };

  EXPECT_THAT(s, ElementsAre("32T3K", "KK677", "T55J5", "QQQJA", "KTJJT"));
}

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
  EXPECT_TRUE(rhHigherHasCard("23457", "234A7", string_view("AKQJT98765432")));
  EXPECT_FALSE(rhHigherHasCard("234A7", "23457", string_view("AKQJT98765432")));
}

TEST(cardValue, examples)
{
  auto cv = [](Card c){return cardValue(c, "AKQJT98765432");};
  
 EXPECT_THAT(cv('K'), Lt(cv('A')));
 EXPECT_THAT(cv('Q'), Lt(cv('K')));
 EXPECT_THAT(cv('J'), Lt(cv('Q')));
 EXPECT_THAT(cv('T'), Lt(cv('J')));
 EXPECT_THAT(cv('9'), Lt(cv('T')));
 EXPECT_THAT(cv('8'), Lt(cv('9')));
 EXPECT_THAT(cv('7'), Lt(cv('8')));
 EXPECT_THAT(cv('6'), Lt(cv('7')));
 EXPECT_THAT(cv('5'), Lt(cv('6')));
 EXPECT_THAT(cv('4'), Lt(cv('5')));
 EXPECT_THAT(cv('3'), Lt(cv('4')));
 EXPECT_THAT(cv('2'), Lt(cv('3')));
}

TEST(type, examples)
{
  EXPECT_THAT(type(Hand("AAAAA")), Eq(Five_of_a_kind));
  EXPECT_THAT(type(Hand("AA8AA")), Eq(Four_of_a_kind));
  EXPECT_THAT(type(Hand("23456")), Eq(High_card));
  EXPECT_THAT(type(Hand("23332")), Eq(Full_house));
  EXPECT_THAT(type(Hand("TTT98")), Eq(Three_of_a_kind));
  EXPECT_THAT(type(Hand("23432")), Eq(Two_pair));
  EXPECT_THAT(type(Hand("23456")), Eq(High_card));
}
