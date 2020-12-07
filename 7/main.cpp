#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <regex>
#include <iostream>
#include <sstream>
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

string getContainer(Words const &w)
{
  auto iter = find_if(w.cbegin(),
		      w.cend(),
		      [](auto const &x){return "bags"==x;});
  assert(*next(iter) == "contain");
  string ret=w[0];
  auto i = next(w.cbegin());
  while(i!=iter)
    {
      ret+=" ";
      ret+=*i;
      i = next(i);
    }
  return ret;
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
