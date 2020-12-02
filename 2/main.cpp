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
