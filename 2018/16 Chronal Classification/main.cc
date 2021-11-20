#include <gtest/gtest.h>
#include <iostream>
#include "operations.hh"

using namespace std;


auto solutionA(istream &in)
{
  unsigned int count{0};
  InputParser ip(in);
  while(in.good())
    {
      if(ip.possible()>2)
        count++;
      in>>ip;
    }
  return count;
}

int main(int narg, char** argv)
{
  testing::InitGoogleTest();
  if(RUN_ALL_TESTS())
    return -1;
  else
    {
      cout<<"Attepmting to read input from standard input."<<endl;
      cout<<"solutionA: " <<solutionA(cin)<<endl;
      return 0;
    }
}
