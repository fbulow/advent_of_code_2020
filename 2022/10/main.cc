#include <gtest/gtest.h>
#include <gmock/gmock.h>
using namespace testing;

struct Signal{
  int cycle=1;
  int value=1;

  Signal noop() const
  {
    return {
      cycle+1,
      value
    };
  }
  Signal addx(int x) const
  {
    
    return {cycle+2,
	    x};
  }
};

TEST(noop, test)
{
  auto sut = Signal().noop();
  EXPECT_THAT(sut.cycle, Eq(2));
  EXPECT_THAT(sut.value, Eq(1));
}

TEST(addx, test)
{
  auto sut = Signal().addx(5);
  EXPECT_THAT(sut.cycle, Eq(3));
  EXPECT_THAT(sut.value, Eq(5));
}

