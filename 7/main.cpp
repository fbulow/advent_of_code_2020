#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <regex>
#include <iostream>
#include <sstream>
#include <numeric>
#include <cassert>
#include <fstream>
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

Words getContainer(Words const &w)
{
  auto iter = find_if(w.cbegin(),
		      w.cend(),
		      [](auto const &x){return "bags"==x;});
  assert(*next(iter) == "contain");
  return {w.cbegin(), iter};
}



Words getContainer(string const &str)
{
  return getContainer(getWords(str));
}

TEST(getContainer, first)
{
  EXPECT_EQ("light red",
	    join(getContainer("light red bags contain 1 bright white bag, 2 muted yellow bags.")));
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


using Color = array<string,2>;
struct Bags
{
  unsigned int count;
  Color color;
};

struct Rule
{
  Color container;
  vector<Bags> contents;
  Rule(Words const &w)
    :container([&](){ //evaluated immediately!
      auto a = getContainer(w);
      assert(2 == a.size());
      return Color{a[0], a[1]};}())
    ,contents([&](){ //evaluated immediately!
      vector<Bags> ret;
      for(auto x:splitContents(getContents(w)))
	{
	  if(not (x[0]=="no" and x[1]=="other"))
	    ret.emplace_back(
			     Bags{
			       (unsigned int) stoi(x[0]),
			       Color{x[1], x[2]}});
	}
      return ret;}())
  {}
  Rule(string const &s)
    :Rule(getWords(s))
  {}
  bool containsColor(Color const &c) const
  {
    return find_if(contents.begin(),
		   contents.end(),
		   [&c](auto x){
		     return x.color==c;}) != contents.end();
  }
  bool containsColorSet(set<Color> const &sc) const
  {
    return sc.end() != find_if(sc.begin(),
			       sc.end(),
			       [this](auto&c){return containsColor(c);});
  }
};

TEST(Rule, ctor)
{
  Rule sut("muted yellow bags contain 2 shiny gold bags, 9 faded blue bags.");
  {
    Color ref{"muted","yellow"};
    EXPECT_EQ(ref, sut.container);
  }
  {
    Color ref{"shiny","gold"};
    EXPECT_EQ(ref, sut.contents[0].color);
    EXPECT_EQ(2, sut.contents[0].count);
  }
  {
    Color ref{"faded", "blue"};
    EXPECT_EQ(ref, sut.contents[1].color);
    EXPECT_EQ(9, sut.contents[1].count);
  }
}

TEST(Rule, ctor_empty)
{
  Rule sut("faded blue bags contain no other bags.");
  EXPECT_TRUE(sut.contents.empty());
  
}

TEST(Rule, containsColor)
{
  Rule sut("muted yellow bags contain 2 shiny gold bags, 9 faded blue bags.");
  EXPECT_TRUE(sut.containsColor({"shiny", "gold"}));
  EXPECT_FALSE(sut.containsColor({"faded", "yellow"}));
  EXPECT_TRUE(sut.containsColor({"faded", "blue"}));
}

TEST(Rule, containsColorSet)
{
  Rule sut("muted yellow bags contain 2 shiny gold bags, 9 faded blue bags.");
  EXPECT_TRUE(sut.containsColorSet({Color{"shiny", "gold"}}));
  EXPECT_FALSE(sut.containsColorSet({Color{"", ""}}));
  EXPECT_TRUE(sut.containsColorSet({Color{"", ""}, Color{"shiny", "gold"}}));
}

set<Color> canContain(vector<Rule> const & rules, set<Color> &cs)
{
  auto before = cs.size();
  for (auto const &r: rules)
    if(r.containsColorSet(cs))
      cs.insert(r.container);
  if(before == cs.size())
    return cs;
  else
    return canContain(rules, cs);
}


TEST(canContain, a)
{
  vector<Rule> data{
    Rule("light red bags contain 1 bright white bag, 2 muted yellow bags."),
    Rule("dark orange bags contain 3 bright white bags, 4 muted yellow bags."),
    Rule("bright white bags contain 1 shiny gold bag."),
    Rule("muted yellow bags contain 2 shiny gold bags, 9 faded blue bags."),
    Rule("shiny gold bags contain 1 dark olive bag, 2 vibrant plum bags."),
    Rule("dark olive bags contain 3 faded blue bags, 4 dotted black bags."),
    Rule("vibrant plum bags contain 5 faded blue bags, 6 dotted black bags."),
    Rule("faded blue bags contain no other bags."),
    Rule("dotted black bags contain no other bags.")};


  set<Color> cs{Color{"shiny", "gold"}};
  EXPECT_EQ(4,
	    canContain(data, cs).size()-1); //-1 for the initial bag.
}

vector<string> getInput(string const &filename)
{
  vector<string> ret;
  ifstream in(filename);
  assert(in.is_open());
  string line;
  while(getline(in, line))
      ret.push_back(line);
  
  return ret;
}


TEST(canContain, file_input)
{
  vector<Rule> data;
  for(string &s: getInput(EXAMPLE))
    data.emplace_back(s);

  set<Color> cs{Color{"shiny", "gold"}};
  EXPECT_EQ(4,
	    canContain(data, cs).size()-1); //-1 for the initial bag.
}

TEST(solution, a)
{
  vector<Rule> data;
  for(string &s: getInput(INPUT))
    data.emplace_back(s);

  set<Color> cs{Color{"shiny", "gold"}};
  EXPECT_EQ(172,
	    canContain(data, cs).size()-1); //-1 for the initial bag.
}


unsigned int countBags(Color const &c, vector<Rule> const &r)
{
  unsigned int ret{1};//1 = this bag
  for(Bags const& b: find_if(r.begin(),
			     r.end(),
			     [&c](auto x){return x.container == c;})->contents)
    {
      ret+= b.count * countBags(b.color, r);
    }
  return ret;
}

TEST(example, b)
{
  vector<Rule> data;
  for(string &s: getInput(EXAMPLE))
    data.emplace_back(s);
  EXPECT_EQ(32, countBags({"shiny", "gold"}, data)-1);
}

TEST(solution, b)
{
  vector<Rule> data;
  for(string &s: getInput(INPUT))
    data.emplace_back(s);
  EXPECT_EQ(39645, countBags({"shiny", "gold"}, data)-1);
}
