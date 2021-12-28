#include <list>
#include<iostream>
#include<sstream>
#include <gtest/gtest.h>
#include <memory>
#include "strong_type.hpp"
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

using namespace std;

#include "input.hpp"
#include "test.hpp"
#include "solution.hpp"

using Data = vector<string>;

auto solution_a(Data const &in)
{
  return magnitude(addAll(in));
}
auto magnadd(string const &a, string const &b)
{
  SnailFishNumber A(a);
  A+=SnailFishNumber(b);
  A.reduce();
  return magnitude(A);
}
  
auto maxSum(string const &a, string const &b)
{
  return max(magnadd(a,b),
             magnadd(b,a));
  
}

auto solution_b(Data in)
{
  long int best=0;
  for(auto &a:in)
    for(auto &b:in)
      if(a!=b)
        best = max(best, maxSum(a,b));
  return best;
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
      cout<<"a: "<<solution_a(data)<<endl
          <<"b: "<<solution_b(data)<<endl;
    }
}

