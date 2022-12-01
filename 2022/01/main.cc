#include "PositiveIntOrEmpty.hh"

#include <algorithm>
#include <numeric>

#include <AoC/getAllLines.hh>

using namespace std;


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

