#include <gtest/gtest.h>
#include "main.cpp"
#include "gmock/gmock.h"
#include "coord.hpp"

TEST(solution, a)
{
  auto ans = solutionA(ifstream(INPUT));
  EXPECT_EQ(2016, ans);
  cout<<"Solution a: "<<ans<<endl;
  
}


TEST(solution, b)
{
  solutionB(ifstream(INPUT));
}
