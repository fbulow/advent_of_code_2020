#include <gtest/gtest.h>
#include "main.cpp"
#include "gmock/gmock.h"


TEST(solution, a)
{
  auto ans = solutionA(INPUT);
  ASSERT_EQ(277, ans);
  cout<<"Solution a: "<<ans<<endl;
  
}


// TEST(solution, b)
// {
//   auto ans = solutionB(Jupiter(INPUT));
//   EXPECT_EQ(402951477454512, ans);
//   cout<<"Solution b: "<<ans<<endl;
// }

