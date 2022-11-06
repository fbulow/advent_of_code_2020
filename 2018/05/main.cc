#include<string>
#include<fstream>
#include<set>
#include<limits>
using namespace std;

bool isPair(char a, char b)
{
  return max(a,b)-min(a,b) == ('a'-'A');
}


int solA(auto read, auto write, auto writeBegin, auto readEnd)
{
  while(read!=readEnd)
    {
      if(isPair(*prev(write), *read))
	{
	  advance(write, -1);
	  advance(read, +1);
	}
      else
	{
	  *write=*read;
	  advance(write,+1);
	  advance(read, +1);
	}
    }
  return distance(writeBegin, write);
}
int solA(string& data)
{
  auto size = solA(next(data.begin()),
		   next(data.begin()),
		   data.begin(),
		   data.end());
  data.resize(size);
  return size;
}


#include<ranges>

set<char> allChars(string const & data)
{
  auto d = data|
    ranges::views::transform(
			     [](char c)->char
			     {
			       return c + (c>='a'?0:'a'-'A');
			     });
  return {d.begin(), d.end()};
}

void copyRemove(char toRemove, string const & source, string &dest)
{
  dest.clear();
  for (char c :
	 source|ranges::views::filter([toRemove](char c){return (c!=toRemove) and (not isPair(c,toRemove));}))
    dest.push_back(c);
}

int solB(string const &data)
{
  string s(data);
  auto lowest = numeric_limits<int>::max();
  for(auto c:allChars(data))
    {
      s.clear();
      copyRemove(c, data, s);
      lowest = min(lowest, solA(s));
    }
  return lowest;
}


#include<gtest/gtest.h>
#include<gmock/gmock.h>
using namespace testing;

TEST(copyRemove, example)
{
  string s;
  copyRemove('a', "CAabB", s);
  EXPECT_THAT(s, Eq("CbB"));
}

TEST(allChars, example)
{
  auto sut = allChars("aAbBC");
  EXPECT_THAT(sut, ElementsAre('a', 'b', 'c'));
}

TEST(isPair, a_and_A)
{
  EXPECT_TRUE(isPair('a', 'A'));
  EXPECT_TRUE(isPair('A', 'a'));
  EXPECT_FALSE(isPair('b', 'A'));
}

TEST(examples, aA)
{
    string data("aA");
    EXPECT_THAT(solA(data), Eq(0));
    EXPECT_THAT(data, Eq(""));
}

TEST(examples_a, dabAcCaCBAcCcaDA)
{
    string data("dabAcCaCBAcCcaDA");
    ASSERT_THAT(solA(data), Eq(10));
    ASSERT_THAT(data, Eq("dabCBAcaDA"));
    ifstream in(INPUT);
    in>>data;
    {
      string tmp(data);
      cout<<"Solution a: "<<solA(tmp);
    }
    cout<<"Solution b: "<<solB(data);
}

TEST(examples_b, dabAcCaCBAcCcaDA)
{
    string data("dabAcCaCBAcCcaDA");
    EXPECT_THAT(solB(data), Eq(4));
}

