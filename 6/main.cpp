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


using Ans = set<char>;

vector<Ans> getInput(string const &filename)
{
  vector<Ans> ret;
  ifstream in(filename);
  assert(in.is_open());
  
  Ans last;
  string line;
  while(getline(in, line))
    {
      if(line.empty())
	{
	  assert(not last.empty());
	  ret.push_back(last);
	  last.clear();
	}
      else
	for(char c:line)
	  last.insert(c);
    }
  ret.push_back(last);
    
  return ret;
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
