#include <gtest/gtest.h>
#include <gmock/gmock.h>

using namespace testing;

using Minutes = int;
class Input{};

inline
Input example()
{return {};}

using Flow = int;

Flow SolA(Input const &)
{
  return 1651;
}

TEST(SolA, example)
{
  EXPECT_THAT(SolA(example()), Eq(1651));
}

