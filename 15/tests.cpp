#include <gtest/gtest.h>
#include "main.cpp"


TEST(a,a)
{
  Spoken s{0,3,6};
  ASSERT_EQ(6, s.last());
}


TEST(a,b)
{
  Spoken s{0,3,6};
  ASSERT_EQ(6, s.last());
  s.turn();
  ASSERT_EQ(0, s.last());
}

TEST(a,bb)
{
  Spoken s{0,3,6,0};
  s.turn();
  ASSERT_EQ(3, s.last());
  s.turn();
  ASSERT_EQ(3, s.last());
}


TEST(solve, a)
{
  ASSERT_EQ(436, solveA({0,3,6}));
  cout<<"solve a: "<< solveA({0,20,7,16,1,18,15})<<endl;
}

TEST(solve, b)
{
  cout<<"solve b: "<< solveB({0,20,7,16,1,18,15})<<endl;
}
