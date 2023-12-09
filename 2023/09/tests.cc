
#include "impl.cc"

#include <gtest/gtest.h>
#include <gmock/gmock.h>
using namespace testing;

TEST(nextValue, example)
{
    EXPECT_THAT(nextValue({0, 0}), Eq(0));
    EXPECT_THAT(nextValue({1, 1}), Eq(1));
    EXPECT_THAT(nextValue({0, 1, 2}), Eq(3));

    EXPECT_THAT(nextValue({0, 3, 6, 9, 12, 15}), Eq(18));
}

TEST(solA, example)
{
  ASSERT_THAT(
	      solA(ifstream(EXAMPLE)),
	      Eq(114));
  ASSERT_THAT(
	      solA(ifstream(INPUT)),
	      Eq(1772145754));
}


TEST(solB, example)
{
  ASSERT_THAT(
	      solB(ifstream(EXAMPLE)),
	      Eq(2));
  ASSERT_THAT(
	      solB(ifstream(INPUT)),
	      Eq(867));
}

