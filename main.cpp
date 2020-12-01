#include<gtest/gtest.h>
#include<vector>
#include"solve.hpp"
#include"get_input.hpp"
using namespace std;

TEST(hello, world)
{
  ASSERT_TRUE(true);
}

TEST(one, get_input)
{
  ASSERT_FALSE(get_input().empty());
}

TEST(one, example)
{
  std::vector<int> input{
    1721,
    979,
    366,
    299,
    675,
    1456,
  };
  ASSERT_EQ(514579, solve(input));
}

TEST(one, solution)
{
  std::vector<int> input = get_input();
  ASSERT_EQ(864864, solve(input));
}

TEST(one, no_solution)
{
  ASSERT_FALSE(bool(solve(get_input(), 2, 0)));
}
