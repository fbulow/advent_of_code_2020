#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <limits>
//#include <regex>
//#include <sstream>
#include <numeric>

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

// MUST always pick smallest adaptor, otherwise the smallest one can never be connected;

set<Joltage> allAdaptors(istream &&in)
{
  set<Joltage> ret;
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


Joltage solveA(string filename)
{
  auto const sut = allJoltages(ifstream(filename));
  vector<Joltage> diffs(sut.size());
  adjacent_difference(sut.begin(), sut.end(), diffs.begin());

  auto occurences =
    [&diffs](auto value)
    {
      return count(diffs.begin(), diffs.end(), value);
    };
  
  return occurences(1)*occurences(3);
}

TEST(solutionA, example)
{
  EXPECT_EQ(35, solveA(EXAMPLE_SMALL));
  cout<<"Solution A: "<< solveA(INPUT)<<endl;
}

unsigned long int solveB(string filename)
{
  auto v = getData(ifstream(filename));
  auto device = deviceAdaptor(v);
  v.push_back(device);

  vector<unsigned long int> data(8+device); //Allocation, use with offset.
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
