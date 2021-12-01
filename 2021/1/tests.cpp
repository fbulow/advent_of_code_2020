#include <gtest/gtest.h>
#include "main.cpp"

TEST(solution, a)
{
  ifstream in(INPUT);
  EXPECT_EQ(1529, solution_a(in));
}

TEST(example, b)
{
  string data{
    "199 "
    "200 "
    "208 "
    "210 "
    "200 "
    "207 "
    "240 "
    "269 "
    "260 "
    "263 "};
  auto in =istringstream(data);

  EXPECT_EQ(5, sliding_average_increases<3>(in));
}  

TEST(solution, b)
{
  ifstream in(INPUT);
  auto const ret =  solution_b(in);
  EXPECT_NE(1568, ret);
  EXPECT_EQ(1567, ret);
}
