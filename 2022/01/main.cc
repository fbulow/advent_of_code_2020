#include <istream>
#include <sstream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <numeric>

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

int solA(istream& input, int ret=0)
{
  auto next = getElfCalories(input);
  if(input.eof())
    return ret;
  else
    return solA(input, max(ret, next));
}

int solB(istream& input)
{
  vector<int> values;
  while(not input.eof())
    values.push_back(getElfCalories(input));
  partial_sort(values.begin(),
	       next(values.begin(),4),
	       values.end(),
	       [](int a, int b){
		 return a>b;});
  return accumulate(values.begin(),
		    next(values.begin(), 3),
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
