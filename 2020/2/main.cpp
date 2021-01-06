#include<gtest/gtest.h>
#include<vector>
#include "get_input.hpp"
#include "letter_count.hpp"
#include <functional>
using namespace std;

TEST(hello, world)
{
  ASSERT_TRUE(true);
}

TEST(get_input, example_input)
{
  auto const sut = example_input();

  EXPECT_EQ(1, sut[0].rule.min);
  EXPECT_EQ(3, sut[0].rule.max);
  EXPECT_EQ('a', sut[0].rule.letter);
  
}

TEST(letter_count, example)
{
  EXPECT_EQ(5, letter_count('a', "aaxaaa"));
}

bool check(RuleAndPassword const &x)
{
  auto c = letter_count(x.rule.letter, x.password);
  return (c>=x.rule.min) and (c<=x.rule.max);
}

TEST(check, pass)
{
  {
    auto sut = example_input()[0];
    EXPECT_TRUE(check(sut));
  }
  {
    auto sut = example_input()[2];
    EXPECT_TRUE(check(sut));
  }
}

TEST(check, fail)
{
  auto sut = example_input()[1];
  EXPECT_FALSE(check(sut));
}

int solve(vector<RuleAndPassword> const & data,
	  function<bool(RuleAndPassword const &)> check = check)
{
  return count_if(data.begin(), data.end(), check);
}

TEST(solve, example_data)
{
  EXPECT_EQ(2, solve(example_input()));
}


TEST(solve_a, input)
{
  EXPECT_EQ(640, solve(input()));
}

bool check_toboggan(RuleAndPassword const &x)
{
  return
    (x.password[x.rule.min-1] == x.rule.letter)
    xor
    (x.password[x.rule.max-1] == x.rule.letter);
}


TEST(check_toboggan, example_input)
{
  {
    auto sut = example_input()[0];
    EXPECT_TRUE(check_toboggan(sut));
  }
  {
    auto sut = example_input()[1];
    EXPECT_FALSE(check_toboggan(sut));
  }
  {
    auto sut = example_input()[2];
    EXPECT_FALSE(check_toboggan(sut));
  }
  
}
TEST(solve_b, example_data)
{
  EXPECT_EQ(1, solve(example_input(), check_toboggan));
}

TEST(solve_b, input)
{
  EXPECT_EQ(640, solve(input(), check_toboggan));
}
