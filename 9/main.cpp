#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <fstream>
//#include <regex>
#include <iostream>
//#include <sstream>
//#include <numeric>

TEST(hello, world)
{
  EXPECT_TRUE(true);
}
using namespace std;


bool findSum(long int value, int count, auto begin, auto end)
{
  while(begin!=end)
    {
      if(count == 0)
	return end != find(begin, end, value);
      else
	{
	  if (findSum(value-*begin, count-1, next(begin), end))
	    return true;
	  else
	    advance(begin, 1);
	}
    }
  return false;
}
  
TEST(findSum, first)
{
  vector<long int> const sut{1,2,3,4};
  
  EXPECT_TRUE(findSum(3, 0, sut.begin(), sut.end()));
  EXPECT_TRUE(findSum(1, 0, sut.begin(), sut.end()));
  EXPECT_TRUE(findSum(4, 0, sut.begin(), sut.end()));

  EXPECT_FALSE(findSum(30, 0, sut.begin(), sut.end()));
}

TEST(findSum, second)
{
  vector<long int> const sut{1,2,3,4};
  
  EXPECT_TRUE(findSum(5, 1, sut.begin(), sut.end()));
  EXPECT_FALSE(findSum(1, 1, sut.begin(), sut.end()));
}


bool checkPremble(int premble, int count, auto begin, auto end)
{
  auto theOneToCheck{begin};
  advance(theOneToCheck, premble);
  assert(theOneToCheck<=end);
  return findSum(*theOneToCheck, count, begin, theOneToCheck);
}

TEST(checkPremble, first)
{
  vector<long int> const sut{1,2,3,40};
  
  EXPECT_TRUE(checkPremble(2, 1, sut.begin(), sut.end()));
  EXPECT_FALSE(checkPremble(3, 1, sut.begin(), sut.end()));
}

vector<long int> getData(istream &&in)
{
  vector<long int> ret;
  long int a;
  in>>a;
  while(!in.eof())
    {
      ret.push_back(a);
      in>>a;
    }
  return ret;
}

TEST(getInput, example)
{
  auto sut = getData(ifstream(EXAMPLE));
  EXPECT_EQ(35,  *sut.begin());
  EXPECT_EQ(576, *prev(sut.end())); //Last element....
}

TEST(a, example)
{
  auto sut = getData(ifstream(EXAMPLE));
  auto index = find(sut.begin(), sut.end(), 127);
  advance(index, -5);
  EXPECT_FALSE(checkPremble(5,
			    1,
			    index,
			    sut.end()));
}


long int solveA(vector<long int> const & data, int premble)
{
  int count = 1;
  auto b = data.begin();
  
  while(checkPremble(premble, count, b, data.end()))
    {
      advance(b,1);
    }
  advance(b, premble);
  return *b;
}

TEST(solveA, example)
{
  EXPECT_EQ(127, solveA(getData(ifstream(EXAMPLE)), 5));
}

constexpr auto answerA{258585477};

TEST(solveA, input)
{
  EXPECT_EQ(answerA, solveA(getData(ifstream(INPUT)), 25));
}

auto contSum(long int value, auto begin, auto end)
{
  assert(*begin > 0);
  assert(begin<end);
  
  if(value<0)
    return end;
  else if(value==*begin)
    return begin;
  else
    return contSum(value-*begin, next(begin), end);
}

long int solveB(long int value, auto const &data)
{
  auto b = data.begin();
  auto ans = contSum(value, b, data.end());
  while(ans==data.end())
    {
      advance(b, 1);
      ans = contSum(value, b, data.end());
    }
  advance(ans,1);
  return *min_element(b,ans)+
	 *max_element(b,ans);
}

TEST(sovleB, example)
{
  EXPECT_EQ(62, solveB(127, getData(ifstream(EXAMPLE))));
}

TEST(sovleB, input)
{
  EXPECT_TRUE(35321204 < solveB(answerA, getData(ifstream(INPUT))));
  cout<<"Answer b: " <<solveB(answerA, getData(ifstream(INPUT)))<<endl;
}

