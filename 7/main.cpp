#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <regex>
#include <iostream>
#include <sstream>
#include <numeric>
TEST(hello, world)
{
  EXPECT_TRUE(true);
}
using namespace std;

vector<string> getWords(istream &in)
{
  vector<string> ret{};
  string word;
  while(in>> word)
      ret.push_back(word);
  return ret;
}

using Words = vector<string>;

Words getWords(string const & str)
{
  istringstream tmp(str);
  return getWords(tmp);
}

TEST(getWords, empty)
{
  EXPECT_EQ(0,
	    getWords("").size());
}

TEST(getWords, first)
{
  auto const sut = getWords("bags.");
  ASSERT_EQ(1,
	    sut.size());
  EXPECT_EQ("bags.",
	    sut[0]);
}

string join(auto b, auto e)
{
  string ret={};
  return accumulate(b,
		    e,
		    ret,
		    [](auto a, auto b)
		    {
		      if(a.empty())
			return b;
		      else
			return a+" "+b;});
}

string join(auto a)
{
  return join(a.cbegin(), a.cend());
}

string getContainer(Words const &w)
{
  auto iter = find_if(w.cbegin(),
		      w.cend(),
		      [](auto const &x){return "bags"==x;});
  assert(*next(iter) == "contain");
  return join(w.cbegin(), iter);
}



string getContainer(string const &str)
{
  return getContainer(getWords(str));
}

TEST(getContainer, first)
{
  EXPECT_EQ("light red",
	    getContainer("light red bags contain 1 bright white bag, 2 muted yellow bags."));
}

Words getContents(Words const &w)
{
  auto iter = find_if(w.cbegin(),
		      w.cend(),
		      [](auto const &x){return "bags"==x;});
  assert(*next(iter) == "contain");

  advance(iter,2);
  return Words(iter, w.cend());
}

Words getContents(string const &str)
{  
  return getContents(getWords(str));
}

TEST(getContents, first)
{
  EXPECT_EQ("1 bright white bag, 2 muted yellow bags.",
	    join(getContents("light red bags contain 1 bright white bag, 2 muted yellow bags.")));
  EXPECT_EQ("1 shiny gold bag.",
	    join(getContents("bright white bags contain 1 shiny gold bag.")));
}

