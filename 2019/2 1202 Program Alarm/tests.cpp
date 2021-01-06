#include <gtest/gtest.h>
#include "main.cpp"
#include "gmock/gmock.h"

TEST(Intcode, ctor)
{
  {
    IntCode sut(ifstream(INPUT));
    EXPECT_EQ(1, sut.first());
  }
  {
    IntCode sut("1,9,10,3,2,3,11,0,99,30,40,50");
    EXPECT_EQ(1,  sut.first());
    EXPECT_EQ(50, sut.last());
    
  }
  {
    IntCode sut("1,9,10,3,2,3,11,0,99,30,40,50");
    EXPECT_TRUE(sut.step());
    EXPECT_EQ(IntCode("1,9,10,70,2,3,11,0,99,30,40,50", 4),
              sut);
    EXPECT_TRUE(sut.step());
    EXPECT_EQ(
              IntCode("3500,9,10,70,"
                      "2,3,11,0,"
                      "99,"
                      "30,40,50", 8),
              sut);
    EXPECT_FALSE(sut.step());//done

  }
}

TEST(solution, a)
{
  EXPECT_EQ(3224742, solutionA(INPUT));
}
