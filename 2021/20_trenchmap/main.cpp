#include<fstream>
#include <gtest/gtest.h>
#include "impl.hh"




uint solutionA(Key k, Board b)
{
  assert(*k.begin());
  assert(not *prev(k.end()));

  cout<<k
      <<endl
      <<k.invertedInput().invertedInput()<<endl;
  
  return iteration(k.invertedInput(),
                   iteration(k.inverted(), b)).size();
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
