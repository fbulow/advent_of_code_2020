#include <gtest/gtest.h>
#include <iostream>

using namespace std;

template<class T=void>
auto solutionA(istream &in)
{
  return "Solution A not implemented";
}

int main(int narg, char** argv)
{
  testing::InitGoogleTest();
  if(RUN_ALL_TESTS())
    return -1;
  else
    {
      cout<<"solutionA: " <<solutionA(cin)<<endl;
      return 0;
    }
}
