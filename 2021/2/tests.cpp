#include <gtest/gtest.h>
#include "main.cpp"


TEST(solution, a)
{
  ifstream in(INPUT);
  ASSERT_NE(0, solution_a(in));
}
TEST(solution, b)
{
  ifstream in(INPUT);
  ASSERT_NE(0, solution_b(in));
}
