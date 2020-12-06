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


vector<vector<string>> group(vector<string> const & data)
{
  vector<vector<string>> ret;

  auto a = data.begin();
  auto b = find(data.begin(), data.end(), "");
  assert(a!=b);

  while(b!=data.end())
    {
      ret.push_back({a, b});
      a=b;
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
  
  Ans(string const &s)
  {
    for(char c: s)
      insert(c);
  }
};


Ans agregateAnyOf(Ans a, Ans const &b)
{
    for(char x: b)
      a.insert(x);
    return a;
};


vector<Ans> getInput(vector<vector<string>> const & data, auto agregate=agregateAnyOf)
{
  vector<Ans> ret;
  for(auto const &grp:data)
    {
      Ans element;
      for (auto const &v: grp)
	element = agregateAnyOf(element, v);
      ret.push_back(element);
    }
  return ret;
}

vector<Ans> getInput(string const &filename, auto agregate=agregateAnyOf)
{
  return getInput(group(getRawInput(filename)),
		  agregate);
}

TEST(getInput, example)
{
  auto const sut = getInput(EXAMPLE, agregateAnyOf);
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
  EXPECT_EQ(11, solution(getInput(EXAMPLE, agregateAnyOf)));
}

TEST(solution_a, input)
{
  EXPECT_NE(6589, solution(getInput(INPUT, agregateAnyOf)));//Error, assuming no newline on last line of input.
  EXPECT_EQ(6596, solution(getInput(INPUT, agregateAnyOf)));
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


vector<Ans> getInputB(string const &filename)
{
  vector<Ans> ret;
  ifstream in(filename);
  assert(in.is_open());

  string line;
  getline(in, line);
  auto last = Ans(line);
  while(true)
    {
      if(line.empty())
	{
	  ret.push_back(last);

	  getline(in, line);
	  if(line.empty())
	    return ret;
	  else
	    last = Ans(line);
	}
      else
	{
	  last = stringIntersection(last, line);
	  getline(in, line);
	}

    }
  assert(false);
}

TEST(getInputB, example)
{
  auto const sut = getInputB(EXAMPLE);
  EXPECT_EQ(5, sut.size());
  EXPECT_EQ(3, sut[0].size());
  EXPECT_EQ(1, sut[2].size());
  EXPECT_EQ(1, sut[3].size());
  EXPECT_EQ(1, sut[4].size());

}

TEST(getInputB, example_one)
{
    auto const sut = getInputB(EXAMPLE);
    EXPECT_EQ(0, sut[1].size());
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
