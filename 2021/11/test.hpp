#include "solution.hpp"
#include <gtest/gtest.h>

TEST(a,a)
{
  istringstream in(
              "1000000002\n"
              "0000000000\n"
              "0000000000\n"
              "0000000000\n"
              "0000000000\n"
              "0000000000\n"
              "0000000000\n"
              "0000000000\n"
              "0000000000\n"
              "3000000004\n");
  auto sut = input(in);
  
  
  EXPECT_EQ(1, sut(Row(0),Col(0)));
  EXPECT_EQ(2, sut(Row(0),Col(9)));
  EXPECT_EQ(3, sut(Row(9),Col(0)));
  EXPECT_EQ(4, sut(Row(9),Col(9)));
}

TEST(OctoProxy,assign_invalid)
{
  OctoProxy sut;
  EXPECT_EQ(0, sut);
  sut=2;
  EXPECT_EQ(0, sut);
}

TEST(OctoProxy,assign_valid)
{
  int n=3;
  OctoProxy sut(n);
  EXPECT_EQ(3, sut);
  sut=2;
  EXPECT_EQ(2, sut);
}

TEST(assing, invalid)
{
  istringstream in(
              "1000000002\n"
              "0000000000\n"
              "0000000000\n"
              "0000000000\n"
              "0000000000\n"
              "0000000000\n"
              "0000000000\n"
              "0000000000\n"
              "0000000000\n"
              "3000000004\n");
  auto sut = input(in);
  EXPECT_EQ(0, sut(Row(0),Col(10)));
  sut(Row(0),Col(10))=8;
  EXPECT_EQ(0, sut(Row(0),Col(10)));
}

TEST(assing, valid)
{
  istringstream in(
              "1000000002\n"
              "0000000000\n"
              "0000000000\n"
              "0000000000\n"
              "0000000000\n"
              "0000000000\n"
              "0000000000\n"
              "0000000000\n"
              "0000000000\n"
              "3000000004\n");
  auto sut = input(in);
  EXPECT_EQ(2, sut(Row(0),Col(9)));
  sut(Row(0),Row(9))=8;
  EXPECT_EQ(8, sut(Row(0),Col(9)));
}

TEST(step, single_simple_test)
{
  istringstream in(
                   "0000000000\n"
                   "0900000000\n"
                   "0000000000\n"
                   "0000000000\n"
                   "0000000000\n"
                   "0000000000\n"
                   "0000000000\n"
                   "0000000000\n"
                   "0000000000\n"
                   "0000000000\n"
                   );
  auto sut = input(in);
  step(sut);
  for(int i=0;i<10;i++)
    {
      for(int j=0;j<10;j++)
        cout<<sut(Row(i),Col(j));
      cout<<endl;
    }
  ASSERT_EQ(2, sut(Row(0), Col(0)));

}
TEST(step, single)
{
  istringstream in(
                   "5483143223\n"
                   "2745854711\n"
                   "5264556173\n"
                   "6141336146\n"
                   "6357385478\n"
                   "4167524645\n"
                   "2176841721\n"
                   "6882881134\n"
                   "4846848554\n"
                   "5283751526\n"
                   );
  auto sut = input(in);
  EXPECT_EQ(0,  step(sut));
  EXPECT_EQ(35, step(sut));
    
}

TEST(toal_flashes, simple_exaple)
{
  istringstream in(
                   "5483143223\n"
                   "2745854711\n"
                   "5264556173\n"
                   "6141336146\n"
                   "6357385478\n"
                   "4167524645\n"
                   "2176841721\n"
                   "6882881134\n"
                   "4846848554\n"
                   "5283751526\n"
                   );
  auto sut = input(in);
  EXPECT_EQ(204,  total_flashes(sut, 10));
  EXPECT_EQ(1656, total_flashes(sut, 100));
}
