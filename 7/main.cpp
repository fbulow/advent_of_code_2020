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

vector<Words> splitContents(auto&& begin,
			    auto&& end,
			    auto& ret)
{
  auto i = find(begin,
		end,
		[](string const &x){return ',' == x.back()
		    ;});
  if(i==end)
    return ret;
  else
      {
	ret.push_back({});//{begin,i});
	return splitContents(i, end, ret);
      }
}

vector<Words> splitContents(Words const &w)
{
  vector<Words> ret{};
  auto begin = w.begin();
  auto end = w.end();
  while(begin<end)
    {
      auto i = find_if(begin,
		       end,
		       [](string x){return x.back()==',' or x.back()=='.';});
      ret.push_back({begin,i});
      assert(ret.size()<100);
      begin = next(i);
    }
  return ret;
}


TEST(splitContets, word)
{
  auto const sut =
    getContents("bright white bags contain 1 shiny gold bag.");
  EXPECT_EQ(1, splitContents(sut).size());
}

TEST(splitContets, words)
{
  auto const sut = splitContents(getContents("muted yellow bags contain 2 shiny gold bags, 9 faded blue bags."));
  EXPECT_EQ(2, sut.size());

  {
    auto const ref = vector<string>{"2", "shiny", "gold"};
    EXPECT_EQ(ref, sut[0]);
  }

  {
    auto const ref = vector<string>{"9", "faded", "blue"};
    EXPECT_EQ(ref, sut[1]);
  }
}

