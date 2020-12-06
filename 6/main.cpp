#include <gtest/gtest.h>

#include <fstream>

//#include <algorithm>
//#include <functional>
//#include <iostream>
//#include <regex>
//#include <string_view>
#include <vector>
#include<set>
#include<numeric>

using namespace std;

TEST(hello, world)
{
  ASSERT_TRUE(true);
}

vector<string> getRawInput(string const &filename)
{
  vector<string> ret;
  ifstream in(filename);
  assert(in.is_open());
  string line;
  while(getline(in, line))
    ret.push_back(line);
  return ret;
}

TEST(getRawInput, first)
{
  EXPECT_EQ(15, getRawInput(EXAMPLE).size());
}

using Group=vector<string>;

vector<Group> group(vector<string> const & data)
{
  vector<Group> ret;

  auto a = data.begin();
  auto b = find(data.begin(), data.end(), "");
  assert(a!=b);

  while(b!=data.end())
    {
      ret.push_back({a, b});
      a=find_if(b, data.end(), [](auto const &a){return not a.empty();});
      b = find(next(a), data.end(), "");
    }
  ret.push_back({a, b});
  return ret;
}

TEST(group, first)
{
  EXPECT_EQ(5, group(getRawInput(EXAMPLE)).size());
}

struct Ans : public set<char>
{
  Ans()
  {
  }

  Ans(Ans const & other)
    :set<char>(other)
  {}
  
  Ans(string const &s)
  {
    for(char c: s)
      insert(c);
  }

  Ans unionWith(Ans const& other) const
  {
    Ans ret;
    set_union(cbegin(), cend(),
	      other.cbegin(), other.cend(),
	      inserter(ret, ret.begin()));
    return ret;
  }

  Ans intersectWith(Ans const& other) const
  {
    Ans ret;
    set_intersection(cbegin(), cend(),
		     other.cbegin(), other.cend(),
		     inserter(ret, ret.begin()));
    return ret;
  }
  
};
TEST(Ans, intersectWith)
{
  Ans a;
  a = Ans("abd");
  EXPECT_EQ(2, Ans{"abc"}.intersectWith(Ans{"bcd"}).size());
}

TEST(Ans, unionWidth)
{
  Ans a;
  a = Ans("abd");
  EXPECT_EQ(4, Ans{"abc"}.unionWith(Ans{"bcd"}).size());
}


Ans reduceUnion(Group const &g)
{
  Ans ret;
  return reduce(g.cbegin(),
		g.cend(),
		ret,
		[](Ans const &a, Ans const &b){return a.unionWith(b);});
}

Ans agregateAnyOf(Ans a, Ans const &b)
{
    for(char x: b)
      a.insert(x);
    return a;
};


vector<Ans> agregateEach(vector<Group> const & data, auto reducer)
{
  vector<Ans> ret(data.size());
  transform(data.cbegin(), data.cend(),
	    ret.begin(),
	    reducer);
  return ret;
}

vector<Ans> getInput(string const &filename)
{
  return agregateEach(group(getRawInput(filename)), reduceUnion);
}

TEST(getInput, example)
{
  auto const sut = getInput(EXAMPLE);
  EXPECT_EQ(5, sut.size());
  EXPECT_EQ(3, sut[0].size());
  EXPECT_EQ(3, sut[1].size());
  EXPECT_EQ(3, sut[2].size());
  EXPECT_EQ(1, sut[3].size());
  EXPECT_EQ(1, sut[4].size());

  EXPECT_EQ(1, sut[4].size());
  
  EXPECT_TRUE(sut[4].contains('b'));
}

int solution(vector<Ans> const &data)
{
  vector<int> s(data.size());
  transform(data.begin(),
	    data.end(),
	    s.begin(),
	    [](Ans const &x){return x.size();});
  return accumulate(s.begin(), s.end(), 0);
}

TEST(solution, example)
{
  EXPECT_EQ(11, solution(getInput(EXAMPLE)));
}

TEST(solution_a, input)
{
  EXPECT_NE(6589, solution(getInput(INPUT)));//Error, assuming no newline on last line of input.
  EXPECT_EQ(6596, solution(getInput(INPUT)));
}

TEST(toAns, first)
{
  EXPECT_EQ(3, Ans("abc").size());
  EXPECT_EQ(0, Ans("").size());
}

Ans stringIntersection(Ans const & a, string const & s)
{
  Ans ret{};
  Ans b(s);
  set_intersection(a.begin(), a.end(),
		   b.begin(), b.end(),
		   std::inserter(ret, ret.end()));
  return ret;
}

TEST(stringIntersection, first)
{
  
  EXPECT_EQ(3, stringIntersection(Ans("abc"), "abc").size());
  EXPECT_EQ(3, stringIntersection(Ans("abc"), "abcd").size());
  EXPECT_EQ(2, stringIntersection(Ans("abc"), "ab").size());
}

ostream& operator<<(ostream& cout, Ans const &a)
{
  for(auto x:a)
    cout<<x;
  return cout;
}

ostream& operator<<(ostream& cout, Group const &g)
{
  cout<<"(";
  for(auto x:g)
    cout<<x<<", ";
  cout<<")";
  return cout;
}


Ans reduceIntersect(Group const &g)
{
  Ans ret=g[0];
  assert(ret.size() != 0);
  return reduce(next(g.cbegin()),
		g.cend(),
		ret,
		[](Ans const &a, Ans const &b){return a.intersectWith(b);});
}

vector<Ans> getInputB(string const &filename)
{
  return agregateEach(group(getRawInput(filename)), reduceIntersect);
}

TEST(getInputB, examplea)
{
  EXPECT_EQ(3, reduceIntersect({{"abc"}}).size());
  EXPECT_EQ(0, reduceIntersect({{"a"},
				{"b"},
				{"c"}}).size());
  EXPECT_EQ(1, reduceIntersect({{"ab"},
				{"ac"},
				}).size());
  EXPECT_EQ(1, reduceIntersect({{"a"},
				{"a"},
				{"a"},
				{"a"},
				}).size());

  EXPECT_EQ(1, reduceIntersect({{"b"}}).size());
}
TEST(getInputB, example)
{
  auto const sut = getInputB(EXAMPLE);
  //  EXPECT_EQ(5, sut.size());
  //  EXPECT_EQ(3, sut[0].size());
  //  EXPECT_EQ(0, sut[1].size());
  //  EXPECT_EQ(1, sut[2].size());
  EXPECT_EQ(1, sut[3].size());
  //  EXPECT_EQ(1, sut[4].size());
}

TEST(solution_b, example)
{
  EXPECT_EQ(6, solution(getInputB(EXAMPLE)));
}


TEST(solution_b, input)
{
  EXPECT_EQ(3219, solution(getInputB(INPUT)));
}

/**/
