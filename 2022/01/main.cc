#include <istream>
#include <sstream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cassert>

#include <AoC/getAllLines.hh>

using namespace std;

int getElfCalories(istream& input)
{
  if(input.eof())
    return 0;
  string s;
  getline(input, s);
  if(s.empty())
    return 0;
  int val;
  istringstream(s)>>val;
  if(input.fail())
    return 0;
  else
    return val+getElfCalories(input);
}

class PositiveIntOrEmpty{
  int value_;
public:
  PositiveIntOrEmpty(string const & s)
  {
    if(s.empty())
      value_=-1;
    else
      {
	istringstream in(s);
	in>>value_;
      }
  }

  int value() const {
    assert(not empty());
    return value_;
  }
  bool empty() const {return value_<0;}
};

struct ElfCalories:vector<int>
{
  ElfCalories(auto && data)
  {
    int nxt{0};
    for(auto x:data)
      if(x.empty())
	{
	  push_back(nxt);
	  nxt=0;
	}
      else
	nxt+=x.value();
  }
};



int solA(istream& input, int ret=0)
{
  ElfCalories  elfCalories(getAllLines<PositiveIntOrEmpty>(input));
  return *max_element(elfCalories.begin(), elfCalories.end());
}

int solB(istream& input)
{
  ElfCalories  elfCalories(getAllLines<PositiveIntOrEmpty>(input));
  partial_sort(elfCalories.begin(),
	       next(elfCalories.begin(),4),
	       elfCalories.end(),
	       [](int a, int b){
		 return a>b;});
  return accumulate(elfCalories.begin(),
		    next(elfCalories.begin(), 3),
		    0);
		    
}

#include<gtest/gtest.h>

TEST(getElfCalories, single)
{
  istringstream in("1000");
  EXPECT_EQ(1000, 
	    getElfCalories(in));
}

TEST(getElfCalories, two)
{
  istringstream in("1000\n2000");
  EXPECT_EQ(3000, 
	    getElfCalories(in));
}

TEST(getElfCalories, trailing_newline)
{
  istringstream in("1000\n");
  EXPECT_EQ(1000, 
	    getElfCalories(in));
}

TEST(getElfCalories, two_groups)
{
  istringstream in("1000\n\n2000");
  EXPECT_EQ(1000, 
	    getElfCalories(in));
  EXPECT_EQ(2000, 
	    getElfCalories(in));
}

TEST(solution, A)
{
  ifstream input(INPUT);
  EXPECT_EQ(71924, solA(input));
}

TEST(examlpe, B)
{
  istringstream input(
		      R"(1000
2000
3000

4000

5000
6000

7000
8000
9000

10000
)");		      
  EXPECT_EQ(45000, solB(input));
}

TEST(solution, B)
{
  ifstream in(INPUT);
  EXPECT_EQ(210406, solB(in));
}

TEST(PositiveIntOrEmpty, empty_string_is_empty)
{
  PositiveIntOrEmpty sut("");
  ASSERT_TRUE(sut.empty());
}

TEST(PositiveIntOrEmpty, not_empty_if_string_is_a_number)
{
  PositiveIntOrEmpty sut("55");
  EXPECT_FALSE(sut.empty());
  EXPECT_EQ(55, sut.value());
}

