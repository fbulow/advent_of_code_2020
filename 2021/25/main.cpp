#include<iostream>
#include<fstream>
#include<sstream>
#include<functional>
#include<numeric>
#include<algorithm>
#include<optional>
#include<cassert>
#include<memory>
#include<set>
#include<map>
#include <gtest/gtest.h>
#include <limits>

using namespace std;

#include "solution.hpp"
#include "test.hpp"
#include "input.hpp"

auto solution_a(Data in, int max_count = numeric_limits<int>::max())
{
  int count{1};
  while(in.step())
    if((++count)==max_count)
      return numeric_limits<int>::max();
  return count;
}

TEST(solution_a_, example)
{
  istringstream in("v...>>.vv>\n"
                   ".vv>>.vv..\n"
                   ">>.>v>...v\n"
                   ">>v>>.>.v.\n"
                   "v>v.vv.v..\n"
                   ">.>>..v...\n"
                   ".vv..>.>v.\n"
                   "v.v..>>v.v\n"
                   "....v..v.>\n");

  auto data = input(in);
  EXPECT_EQ(9, data.Nrow);
  EXPECT_EQ(10, data.Ncol);
  
  EXPECT_EQ(58,
            solution_a(data, 1000));
  cout<<data.str();
}

auto solution_b(Data in)
{
  return "";
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

