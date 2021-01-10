#include <gtest/gtest.h>
#include "main.cpp"
#include "gmock/gmock.h"

TEST(solution, a)
{
  auto ans = solutionA(INPUT);
  ASSERT_EQ(9938601, ans);
  cout<<"Solution a: "<<ans<<endl;
}

TEST(example, compare_eight_position_mode)
{
  {
    IntCode sut(istringstream("3,9,8,9,10,9,4,9,99,-1,8"));
    sut.input.push(7);
    sut.run();
    EXPECT_EQ(0, sut.output.front());
  }
  {
    IntCode sut(istringstream("3,9,8,9,10,9,4,9,99,-1,8"));
    sut.input.push(8);
    sut.run();
    EXPECT_EQ(1, sut.output.front());
  }
  {
    IntCode sut(istringstream("3,9,8,9,10,9,4,9,99,-1,8"));
    sut.input.push(9);
    sut.run();
    EXPECT_EQ(0, sut.output.front());
  }

}

TEST(example, less_than_position_mode)
{
  //3,9,7,9,10,9,4,9,99,-1,8 - Using position mode, consider whether
  //the input is less than 8; output 1 (if it is) or 0 (if it is not).
  {
    IntCode sut(istringstream("3,9,7,9,10,9,4,9,99,-1,8"));
    sut.input.push(9);
    sut.run();
    EXPECT_EQ(0, sut.output.front());
  }
  {
    IntCode sut(istringstream("3,9,7,9,10,9,4,9,99,-1,8"));
    sut.input.push(8);
    sut.run();
    EXPECT_EQ(0, sut.output.front());
  }
  {
    IntCode sut(istringstream("3,9,7,9,10,9,4,9,99,-1,8"));
    sut.input.push(7);
    sut.run();
    EXPECT_EQ(1, sut.output.front());
  }  
}

TEST(examlple, c)
{
  //3,3,1108,-1,8,3,4,3,99 - Using immediate mode, consider whether
  //the input is equal to 8; output 1 (if it is) or 0 (if it is not).
  {
    IntCode sut(istringstream("3,3,1108,-1,8,3,4,3,99"));
    sut.input.push(7);
    sut.run();
    EXPECT_EQ(0, sut.output.front());
  }
  {
    IntCode sut(istringstream("3,3,1108,-1,8,3,4,3,99"));
    sut.input.push(8);
    sut.run();
    EXPECT_EQ(1, sut.output.front());
  }
}

TEST(example, d)
{
  //3,3,1107,-1,8,3,4,3,99 - Using immediate mode, consider whether
  //the input is less than 8; output 1 (if it is) or 0 (if it is not).
  {
    IntCode sut(istringstream("3,3,1107,-1,8,3,4,3,99"));
    sut.input.push(7);
    sut.run();
    EXPECT_EQ(1, sut.output.front());
  }
  {
    IntCode sut(istringstream("3,3,1107,-1,8,3,4,3,99"));
    sut.input.push(8);
    sut.run();
    EXPECT_EQ(0, sut.output.front());
  }


}
TEST(example, ef)
{
  //Here are some jump tests that take an input, then output 0 if the
  //input was zero or 1 if the input was non-zero:

  //3,12,6,12,15,1,13,14,13,4,13,99,-1,0,1,9 (using position mode)

  {
    IntCode sut(istringstream("3,12,6,12,15,1,13,14,13,4,13,99,-1,0,1,9"));
    sut.input.push(0);
    sut.run();
    EXPECT_EQ(0, sut.output.front());
  }
  {
    IntCode sut(istringstream("3,12,6,12,15,1,13,14,13,4,13,99,-1,0,1,9"));
    sut.input.push(1);
    sut.run();
    EXPECT_EQ(1, sut.output.front());
  }
  //3,3,1105,-1,9,1101,0,0,12,4,12,99,1 (using immediate mode)
  {
    IntCode sut(istringstream("3,3,1105,-1,9,1101,0,0,12,4,12,99,1"));
    sut.input.push(1);
    sut.run();
    EXPECT_EQ(1, sut.output.front());
  }
  {
    IntCode sut(istringstream("3,3,1105,-1,9,1101,0,0,12,4,12,99,1"));
    sut.input.push(0);
    sut.run();
    EXPECT_EQ(0, sut.output.front());
  }
}

TEST(example, the_larger_example)
{
// Here's a larger example:

// 3,21,1008,21,8,20,1005,20,22,107,8,21,20,1006,20,31,
// 1106,0,36,98,0,0,1002,21,125,20,4,20,1105,1,46,104,
// 999,1105,1,46,1101,1000,1,20,4,20,1105,1,46,98,99

  {
    IntCode sut(istringstream(
                              "3,21,1008,21,8,20,1005,20,22,107,8,21,20,1006,20,31,"
                              "1106,0,36,98,0,0,1002,21,125,20,4,20,1105,1,46,104,"
                              "999,1105,1,46,1101,1000,1,20,4,20,1105,1,46,98,99"
                              ));
    sut.input.push(7);
    sut.run();
    EXPECT_EQ(999, sut.output.front());
  }
  {
    IntCode sut(istringstream(
                              "3,21,1008,21,8,20,1005,20,22,107,8,21,20,1006,20,31,"
                              "1106,0,36,98,0,0,1002,21,125,20,4,20,1105,1,46,104,"
                              "999,1105,1,46,1101,1000,1,20,4,20,1105,1,46,98,99"
                              ));
    sut.input.push(8);
    sut.run();
    EXPECT_EQ(1000, sut.output.front());
  }
  {
    IntCode sut(istringstream(
                              "3,21,1008,21,8,20,1005,20,22,107,8,21,20,1006,20,31,"
                              "1106,0,36,98,0,0,1002,21,125,20,4,20,1105,1,46,104,"
                              "999,1105,1,46,1101,1000,1,20,4,20,1105,1,46,98,99"
                              ));
    sut.input.push(9);
    sut.run();
    EXPECT_EQ(1001, sut.output.front());
  }

  
}

TEST(solution, b)
{
  auto ans = solutionB(INPUT);
  ASSERT_EQ(4283952, ans);
  cout<<"Solution b: "<<ans<<endl;
}
