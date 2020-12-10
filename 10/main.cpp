#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <limits>
//#include <regex>
//#include <sstream>
#include <numeric>

TEST(hello, world)
{
  EXPECT_TRUE(true);
}
using namespace std;

using Joltage  = unsigned int;
using Adaptors = vector<Joltage>;

Adaptors getData(istream &&in)
{
  Adaptors ret;
  long int v;
  in>>v;
  while(not in.eof())
    {
      assert(v<=numeric_limits<Joltage>::max());
      assert(v>=numeric_limits<Joltage>::min());
      ret.push_back(v);
      in>>v;
    }
  sort(ret.begin(), ret.end());
  set<Joltage> slask{ret.begin(), ret.end()};
  assert(slask.size() == ret.size());//No duplicates;
  
  
  return ret;
}



TEST(getData, example)
{
  EXPECT_EQ(11, getData(ifstream(EXAMPLE_SMALL)).size());
  EXPECT_EQ(94, getData(ifstream(INPUT)).size());
}

bool canConnect(Joltage outlet, Joltage adaptor)
{
  switch(adaptor-outlet)
    {
    case 1:
    case 2:
    case 3:
      return true;
    }
  return false;
}
  
TEST(can_connect, first)
{
  EXPECT_TRUE(canConnect(10, 11));
  EXPECT_FALSE(canConnect(11, 10));
}

bool isOk(Joltage outlet, auto adaptorsBegin, auto adaptorsEnd)
{
  if(adaptorsBegin==adaptorsEnd)
    return false;
  return canConnect(outlet, *adaptorsBegin);
}

TEST(isOk, first_too_low)
{
  auto sut=Adaptors{9};
  EXPECT_FALSE(isOk(10, sut.begin(), sut.end()));
}

TEST(isOk, first)
{
  auto sut=Adaptors{11};
  EXPECT_TRUE(isOk(10, sut.begin(), sut.end()));
}

// MUST always pick smallest adaptor, otherwise the smallest one can never be connected;

set<Joltage> allAdaptors(istream &&in)
{
    set<Joltage> ret;
  //  ret.insert(0);
  auto slask = getData(move(in));
  ret.insert(slask.begin(), slask.end());
  return ret;
}

Joltage deviceAdaptor(auto const &x)
{
  return 3 + *max_element(x.begin(), x.end());
}

set<Joltage> allJoltages(istream &&in)
{
  
  auto ret = allAdaptors(move(in));
  ret.insert(deviceAdaptor(ret));
  return ret;
}



Joltage solutionA(string filename)
{
  auto const sut = allJoltages(ifstream(filename));
  vector<Joltage> diffs(sut.size());
  adjacent_difference(sut.begin(), sut.end(), diffs.begin());
  auto ones   = count(diffs.begin(), diffs.end(), 1);
  auto threes = count(diffs.begin(), diffs.end(), 3);
  
  return ones*threes;
}

TEST(solutionA, example)
{
  EXPECT_EQ(35, solutionA(EXAMPLE_SMALL));
  cout<<"Solution A: "<< solutionA(INPUT)<<endl;
}

long unsigned int combinations(Joltage device, auto begin, auto end, map<Joltage, long unsigned int> &waysToGetThere)
{
  if(begin==end)
    {
      for(auto x:waysToGetThere)
	cout<<x.first<<", "<<x.second<<endl;
      cout<<endl;
      auto last = prev(waysToGetThere.end());
      if(not canConnect(last->first, device))
	return 0;
      else
	return last->second;
    }
  else if (canConnect(prev(waysToGetThere.end())->first, device))
    return 1 + combinations(device, next(begin), end, waysToGetThere);
  else
    {
      long unsigned int ways=0;
      for(Joltage j: {*begin-3, *begin-2, *begin-1})
	{
	  auto it = find_if(waysToGetThere.begin(), waysToGetThere.end(), [j](auto const &x){return x.first==j;});;
	  if(it!=waysToGetThere.end())
	    ways+=it->second;
	}
      waysToGetThere[*begin] = ways;
      return combinations(device, next(begin), end, waysToGetThere);
    }
}

long unsigned int combinations(Joltage outlet, Joltage device, set<Joltage> adaptors)
{
  map<Joltage, long unsigned int> waysToGetThere;
  waysToGetThere[outlet]=1;
  return combinations(device, adaptors.begin(), adaptors.end(), waysToGetThere);
}

TEST(combinations, example)
{
  EXPECT_EQ(1, combinations(10,  11, {}));
  EXPECT_EQ(0, combinations(10,  20, {}));
}

TEST(combinations, connect_or_not)
{
  EXPECT_EQ (2, combinations(10,  12, {11}));
}

unsigned long int solveB(string filename)
{
  auto v = getData(ifstream(filename));
  auto device = deviceAdaptor(v);
  v.push_back(device);

  vector<unsigned long int> data(8+device);
  assert(data.size()==8+device);
  for(auto &x: data)
    x=0;
  
  auto steps = data.data()+4;
  steps[0]=1;
  for(int x: v)
      steps[x] = steps[x-1] + steps[x-2]  + steps[x-3] ;
  
  return steps[device];
}

TEST(solve, b)
{
  EXPECT_EQ(8, solveB(EXAMPLE_SMALL));
  cout<<"Solution b: "<<solveB(INPUT)<<endl;;
  
}

/*
TEST(combinations, three)
{
  EXPECT_EQ (3, combinations(10,  14, {11,12}));
}


unsigned long int solutionB(string filename)
{
  auto data = allAdaptors(ifstream(filename));
  return combinations(0, deviceAdaptor(data), data);
}

TEST(solution, b)
{
  ASSERT_EQ(8, solutionB(EXAMPLE_SMALL));
  cout<< "Solution b "<<solutionB(INPUT)<<endl;
  EXPECT_TRUE(false);
}
*/
