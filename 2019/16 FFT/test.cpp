#include <gtest/gtest.h>
#include "main.cpp"
#include "gmock/gmock.h"
#include <iterator>
#include <iostream>
#include <fstream>
#include "summation.hpp" 
TEST(keep_one_digit, all)
{
  EXPECT_EQ(0, keep_one_digit(0));
  EXPECT_EQ(0, keep_one_digit(10));
  EXPECT_EQ(0, keep_one_digit(-10));

  EXPECT_EQ(1, keep_one_digit(1));
  EXPECT_EQ(1, keep_one_digit(-11));
}

TEST(example, pattern)
{
  Pattern sut({0,1,0,-1}, 2);

  ASSERT_EQ(0, sut());
  ASSERT_EQ(1, sut());
  ASSERT_EQ(1, sut());
  ASSERT_EQ(0, sut());
  ASSERT_EQ(0, sut());
  ASSERT_EQ(-1, sut());
  ASSERT_EQ(-1, sut());
  ASSERT_EQ(0, sut());
  ASSERT_EQ(0, sut());
  ASSERT_EQ(1, sut());
  ASSERT_EQ(1, sut());
  ASSERT_EQ(0, sut());
  ASSERT_EQ(0, sut());
  ASSERT_EQ(-1, sut());
  ASSERT_EQ(-1, sut());
}
TEST(example, verify_first_line)
{
  Pattern sut({0,1,0,-1}, 1);

  ASSERT_EQ(1, sut());
  ASSERT_EQ(0, sut());
}

TEST(example, phase)
{
  ASSERT_EQ(signal("48226158"), 
            phase("12345678", vector<int>{0, 1, 0, -1}));

  ASSERT_EQ(signal("34040438"), 
            phase("48226158", vector<int>{0, 1, 0, -1}));
}

TEST(examples, phases)
{

  ASSERT_EQ(signal("24176176"),
            solutionA("80871224585914546619083218645595"));

  ASSERT_EQ(signal("73745418"),
            solutionA("19617804207202209144916044189917"));

  
}

TEST(solution, A)
{
  ifstream in(INPUT);
  string data;
  in>>data;
  ASSERT_EQ(signal("17978331"),
            solutionA(data));
  
}

TEST(summation, size)
{
  {
    Summation sut({0});
    EXPECT_EQ(2, sut.size(1)); // First zero length
  }
  {
    Summation sut({0,0});
    EXPECT_EQ(3, sut.size(1)); // First zero length
  }
  {
    Summation sut({0,0});
    EXPECT_EQ(2, sut.size(2)); // First zero length
  }
  {
    Summation sut({0,0,0});
    EXPECT_EQ(2, sut.size(2)); // First zero length
  }

}
