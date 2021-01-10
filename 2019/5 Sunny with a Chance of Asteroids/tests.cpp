#include <gtest/gtest.h>
#include "main.cpp"
#include "gmock/gmock.h"

TEST(solution, a)
{
  auto ans = solutionA(INPUT);
  ASSERT_EQ(9938601, ans);
  cout<<"Solution a: "<<ans<<endl;
}
