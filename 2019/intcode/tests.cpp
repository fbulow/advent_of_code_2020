#include <gtest/gtest.h>
#include "intcode.hpp"
#include "gmock/gmock.h"

TEST(Intcode, ctor)
{
  {
    IntCode sut(istringstream("1,2,3"));
    EXPECT_EQ(1, sut.first());
    EXPECT_EQ(3, sut.last());
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

TEST(intcode, io)
{
  IntCode sut("3,0,4,0,99");
  sut.input.push(2222);
  while(sut.step())
    {}
  EXPECT_EQ(2222, sut.output.front());
}

TEST(mode, command)
{
  EXPECT_EQ(3,
            mode(1, 12345));
  EXPECT_EQ(2,
            mode(2, 12345));
  EXPECT_EQ(1,
            mode(3, 12345));

  
  EXPECT_EQ(0, mode(1, 1002));
  EXPECT_EQ(1, mode(2, 1002));
  EXPECT_EQ(0, mode(3, 1002));
  EXPECT_EQ(02, opcode(1002));
}

// TEST(intcode, relativeBase)
// {
//   IntCode sut{"109,19"};
//   sut.relativeBase = 2000;
//   sut.step();
//   EXPECT_EQ(sut.relativeBase, 2019);

//   sut[2]=204;
//   sut[3]=-34;
//   sut[1985] = 1111;
// }


// TEST(solution, a)
// {
//   EXPECT_EQ(3224742, solutionA(INPUT));
// }

// TEST(solution, b)
// {
//   EXPECT_EQ(7960, solutionB(INPUT));
// }
