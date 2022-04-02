#include<fstream>
#include <gtest/gtest.h>
#include "impl.hh"




uint solutionA(Key k, Board b)
{
  assert(*k.begin());
  assert(not *prev(k.end()));

  k.invert();

  return iteration(k, iteration(k, b)).size();
}



TEST(solution, a)
{
  
  Key k;
  Board b;
  ifstream in(INPUT);
  in >>k>>b;
  auto ans = solutionA(k,b);
  EXPECT_LT(5196, ans);
  EXPECT_GT(5488, ans);
  cout<<"Ans: "<<ans<<endl;
}
