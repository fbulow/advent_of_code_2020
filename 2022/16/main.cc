#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "example.hh"


using namespace testing;

TEST(score, eval)
{
  auto input = example();
  EXPECT_THAT( 
	      Score()
	      .log(2 , input.flow("DD"))
	      .log(5 , input.flow("BB"))
	      .log(9 , input.flow("JJ"))
	      .log(17, input.flow("HH"))
	      .log(21, input.flow("EE"))
	      .log(24, input.flow("CC"))
	      .total(),
	      Eq(1651));
}

TEST(distance, example)
{
  EXPECT_THAT(distance(example(), "AA", "DD"),
	      Eq(1));
  EXPECT_THAT(distance(example(), "AA", "CC"),
	      Eq(2));
  EXPECT_THAT(distance(example(), "CC", "AA" ),
	      Eq(2));
}
