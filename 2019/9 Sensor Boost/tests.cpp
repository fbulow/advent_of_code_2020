#include <gtest/gtest.h>
#include "main.cpp"
#include "gmock/gmock.h"

TEST(solution, a)
{
  auto ans = solutionA(INPUT);
  cout<<"Solution a: "<<ans<<endl;
}

TEST(solution, b)
{
  auto ans = solutionB(INPUT);
  cout<<"Solution b: "<<ans<<endl;
}

