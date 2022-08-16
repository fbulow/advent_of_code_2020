#include "result.hh"
#include <gtest/gtest.h>
#include <gmock/gmock.h>

using namespace testing;

TEST(Result, adding_to_invalid_makes_invalid)
{
  Result a;
  Result five(5);
  bool valid = a+five;

  EXPECT_THAT(valid, Eq(false));
}

void PrintTo(Result const &r, std::ostream *os)
{
  if(r)
    *os<< r.data;
  else
    *os<< false;
}
