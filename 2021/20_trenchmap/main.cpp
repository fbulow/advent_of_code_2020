#include<fstream>
#include <gtest/gtest.h>
#include "impl.hh"


uint twoInversionSteps(Key const &k,
                       Board const& b)
{
  return iteration(k.invertedInput(),
                   iteration(k.inverted(), b)).size();
}

  

uint solutionA(Key k, Board b)
{
  // This solution assumes that the "void space" toggles between . and
  // # in every move. This happens if the fist element is # and the
  // last is .
  assert(*k.begin());
  assert(not *prev(k.end()));
  return twoInversionSteps(k, b);
}


TEST(solution, a)
{
  
  Key k;
  Board b;
  ifstream in(INPUT);
  in >>k>>b;
  auto ans = solutionA(k,b);
  EXPECT_LT(5196, ans); // First try
  EXPECT_GT(5488, ans); // Second try
  EXPECT_EQ(5419, ans);
  cout<<"Solution A: "<<ans<<endl;
}
