#include<algorithm>
#include<iostream>
#include<fstream>
#include<functional>
#include<numeric>
#include<algorithm>
#include<optional>
#include<cassert>
#include<memory>
#include"strong_type.hpp"
#include<set>
#include<map>
#include<sstream>
#include <gtest/gtest.h>
#include <vector>

using namespace std;

#include "input.hpp"
#include "test.hpp"
#include "solution.hpp"

unsigned int manhattan(auto a, auto b)
{
  
  return
    abs(a.x-b.x)+
    abs(a.y-b.y)+
    abs(a.z-b.z);

}

auto solution_b(Data const & in)
{
  unsigned int ret =0;
  for(auto const &a:in)
    for(auto const &b:in)
      ret = max(ret, manhattan(a.scanner,b.scanner));
  return ret;
}

auto solution_a(Data &in)
{
  set<Coord> points;
  auto sut = to_absolute(in);
  for(auto const x: sut)
    for(Coord c:x.beacons)
      points.insert(c);
  
  cout<< points.size() <<endl
      << solution_b(sut)<<endl;
}

TEST(solution_a, example)
{
  //  auto d = input_example();
  //  EXPECT_EQ(79, solution_a(d));
}



int main(int argc, char** argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  auto ret = RUN_ALL_TESTS();
  if(ret!=0)
    return ret;
  else
    {
      ifstream in(INPUT);
      auto data = input(in);
      solution_a(data);
    }
}

