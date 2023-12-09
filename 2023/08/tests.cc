
#include "impl.cc"

#include <gtest/gtest.h>
#include <gmock/gmock.h>
using namespace testing;

TEST(getPos, cases)
{
  EXPECT_THAT(getPos("AAA = (BBB, CCC)", 0), Eq("AAA"));
  EXPECT_THAT(getPos("AAA = (BBB, CCC)", 1), Eq("BBB"));
  EXPECT_THAT(getPos("AAA = (BBB, CCC)", 2), Eq("CCC"));
}

TEST(Navigation, example)
{
  Navigation sut("RL");

  EXPECT_THAT(sut.nxt(), Eq(1));
  EXPECT_THAT(sut.nxt(), Eq(0));
  EXPECT_THAT(sut.nxt(), Eq(1));
  EXPECT_THAT(sut.nxt(), Eq(0));
}

TEST(solA, example_and_input)
{
  ASSERT_THAT(Input(ifstream(EXAMPLE)).solA(), Eq(2));
  ASSERT_THAT(Input(ifstream(INPUT)).solA(), Eq(13301));
}

TEST(solB, example_and_input)
{
  istringstream example("LR\n"
			"\n"
			"11A = (11B, XXX)\n"
			"11B = (XXX, 11Z)\n"
			"11Z = (11B, XXX)\n"
			"22A = (22B, XXX)\n"
			"22B = (22C, 22C)\n"
			"22C = (22Z, 22Z)\n"
			"22Z = (22B, 22B)\n"
			"XXX = (XXX, XXX)\n");

  ASSERT_THAT(Input(move(example)).solB(), Eq(6));
  ASSERT_THAT(Input(ifstream(INPUT)).solB(), Eq(13301));
}

