#include<fstream>
#include <gtest/gtest.h>
#include "impl.hh"


Board twoInversionSteps(Key const &k,
                       Board const& b)
{
  return iteration(k.invertedInput(),
                   iteration(k.inverted(), b));
}

  

uint solutionA(Key k, Board b)
{
  // This solution assumes that the "void space" toggles between . and
  // # in every move. This happens if the fist element is # and the
  // last is .
  assert(*k.begin());
  assert(not *prev(k.end()));
  return twoInversionSteps(k, b).size();
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

uint solutionB(Key k, Board b)
{
  // This solution assumes that the "void space" toggles between . and
  // # in every move. This happens if the fist element is # and the
  // last is .
  auto N=25;
  while((N--)>0)
    {
      b = twoInversionSteps(k, b);
    }
  return b.size();
}


TEST(solution, b)
{
  
  Key k;
  Board b;
  ifstream in(INPUT);
  in >>k>>b;
  auto ans = solutionB(k,b);
  EXPECT_EQ(17325, ans);
  cout<<"Solution B: "<<ans<<endl;
}

