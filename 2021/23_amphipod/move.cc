#include "move.hh"

unsigned int Move::distance() const
{
  return max(to,from) - min(to,from);
}


#include<gtest/gtest.h>
#include<gmock/gmock.h>
using namespace testing;

TEST(Move, distance)
{
  EXPECT_THAT(Move(3,2).distance(), Eq(1));
}
