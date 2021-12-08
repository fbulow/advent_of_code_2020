#include <gtest/gtest.h>
#include "solution.cpp"

TEST(example, read)
{
  istringstream in("16,1");
  auto sut = input(in);
  cout<<sut[0]<<" "<<*prev(sut.end())<<endl;
  EXPECT_EQ(2, sut.size());
  EXPECT_EQ(16, *sut.begin());
  EXPECT_EQ(1, *prev(sut.end()));
}

TEST(example, read_newline)
{
  istringstream in("16,1\n");
  auto sut = input(in);
  cout<<sut[0]<<" "<<*prev(sut.end())<<endl;
  EXPECT_EQ(2, sut.size());
  EXPECT_EQ(16, *sut.begin());
  EXPECT_EQ(1, *prev(sut.end()));
}

TEST(example, one)
{
  istringstream in("16,1,2,0,4,2,7,1,2,14");
  auto sut = input(in);
  cout<<sut[0]<<" "<<*prev(sut.end())<<endl;
  EXPECT_EQ(10, sut.size());
  EXPECT_EQ(16, *sut.begin());
  EXPECT_EQ(14, *prev(sut.end()));
}

TEST(example, one)
{
  istringstream in("16,1,2,0,4,2,7,1,2,14");
  auto sut = input(in);
  cout<<sut[0]<<" "<<*prev(sut.end())<<endl;
  EXPECT_EQ(10, sut.size());
  EXPECT_EQ(16, *sut.begin());
  EXPECT_EQ(14, *prev(sut.end()));
}


