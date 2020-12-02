#include<gtest/gtest.h>
#include<vector>
#include "get_input.hpp"
#include "letter_count.hpp"
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

int solve(vector<RuleAndPassword> const & data)
{
  return count_if(data.begin(), data.end(), [](auto x){return check(x);});
}

TEST(solve, example_data)
{
  EXPECT_EQ(2, solve(example_input()));
}
