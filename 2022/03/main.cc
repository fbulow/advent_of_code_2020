#include <AoC/getAllLines.hh>
#include <algorithm>
#include <numeric>
#include <iterator>
#include <set>
#include <ranges>
#include <iterator>


using namespace std;


int priority(char c);

int sumUp(string const &s)
{
  return accumulate(s.begin(), s.end(),
		    int(0),
		    [](int ret, char nxt)
		    {
		      return ret+priority(nxt);
		    });
}
  

int priority(char c)
{
  
  // Lowercase item types a through z have priorities 1 through 26.
  // Uppercase item types A through Z have priorities 27 through 52.
  if(c<='Z')
    return c-'A'+27;
  else
    return c-'a'+1;
}

set<char> firstHalf(string const & line)
{
  auto middle = next(line.begin(),
		     line.size()/2);

  return {line.begin(), middle};
  
}

string commonLetters(vector<string> const & lines)
{
  string ret;
  for(auto & line:lines)
    {
      if(line.size()>0)
	{
	  auto firstCompartment = firstHalf(line);
	  
	  auto middle = next(line.begin(),
			     line.size()/2);

	  while(not firstCompartment.contains(*middle))
	    {
	      advance(middle,1);
	      if (middle>=line.end())
		break;
	    }
	  ret.push_back(*middle);
	}
    }
  
  return ret;
}

int solA(auto const &data)
{
  return sumUp(commonLetters(data));
}

optional<char> badge(set<char> const &a,
		     set<char> const &b,
		     set<char> const &c)
{
  set<char> ab;
  ranges::set_intersection(a,
			   b, inserter(ab,ab.end()));
  set<char> abc;
  ranges::set_intersection(ab,c, inserter(abc, abc.end()));
  if(abc.size()==1)
    return *abc.begin();
  else
    return {};
}


#include<gtest/gtest.h>
#include<gmock/gmock.h>

using namespace testing;

set<char> toSet(string const &s)
{
  return {s.begin(), s.end()};
}

TEST(badge, two_common)
{
  auto a = toSet("ade");
  auto b = toSet("bde");
  auto c = toSet("cde");


  auto sut = badge(a,b,c);
  EXPECT_FALSE(sut);
}


TEST(badge, example_1)
{
  auto a = toSet("vJrwpWtwJgWrhcsFMMfFFhFp");
  auto b = toSet("jqHRNqRjqzjGDLGLrsFMfFZSrLrFZsSL");
  auto c = toSet("PmmdzqPrVvPwwTWBwg");


  auto sut = badge(a,b,c);
  EXPECT_TRUE(sut);
  EXPECT_EQ('r', sut.value());
}




TEST(solA, real)
{
  EXPECT_EQ(7826, solA(getAllLines()));
}

TEST(solA, example)
{
  istringstream in(
		   R""(vJrwpWtwJgWrhcsFMMfFFhFp
jqHRNqRjqzjGDLGLrsFMfFZSrLrFZsSL
PmmdzqPrVvPwwTWBwg
wMqvLMZHhHMvwLHjbvcjnnSBnvTQFn
ttgJtRGJQctTZtZT
CrZsJsPPZsGzwwsLwLmpwMDw)"");


  EXPECT_EQ(157, solA(getAllLines(in)));
}


TEST(sumUp, example)
{
  EXPECT_EQ(157, sumUp("pLPvts"));
}

TEST(priority, all)
{
  // Lowercase item types a through z have priorities 1 through 26.
  // Uppercase item types A through Z have priorities 27 through 52.

  EXPECT_EQ(1, priority('a'));
  EXPECT_EQ(27, priority('A'));

  EXPECT_EQ(16, priority('p'));
  EXPECT_EQ(38, priority('L'));
  EXPECT_EQ(42, priority('P'));
  EXPECT_EQ(22, priority('v'));
  EXPECT_EQ(20, priority('t'));
  EXPECT_EQ(19, priority('s'));
  
}


TEST(firstHalf, all)
{
  auto sut = firstHalf("abcd");
  ASSERT_THAT(sut.size(), Eq(2));
  ASSERT_TRUE(sut.contains('a'));
  ASSERT_TRUE(sut.contains('b'));
  ASSERT_FALSE(sut.contains('c'));
  ASSERT_FALSE(sut.contains('d'));
    
}
TEST(commonLetters, vJrwpWtwJgWrhcsFMMfFFhFp)
{
  vector<string> sut{"vJrwpWtwJgWrhcsFMMfFFhFp"};
  EXPECT_THAT(commonLetters(sut), Eq("p"));
}


TEST(commonLetters, emptyToEmpty)
{
  vector<string> sut{""};
  EXPECT_THAT(commonLetters(sut), Eq(""));
}

TEST(commonLetters, aa)
{
  vector<string> sut{"aa"};
  EXPECT_THAT(commonLetters(sut), Eq("a"));
}

