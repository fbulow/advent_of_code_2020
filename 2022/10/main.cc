#include <gtest/gtest.h>
#include <gmock/gmock.h>
using namespace testing;

struct Signal{
  int cycle=1;
  int value=1;
  int strength=0;

  Signal noop() const
  {
    return {
      cycle+1,
      value,
      strength
    };
  }
};

TEST(noop, test)
{
  auto sut = Signal().noop();
  EXPECT_THAT(sut.cycle, Eq(2));
}
