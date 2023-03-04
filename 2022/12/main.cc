#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <fstream>
#include <string>
#include "read_input.hh"

using namespace testing;
using namespace std;


TEST(readInput, example)
{
  ifstream in(EXAMPLE);
  auto sut = readInput(in);

  EXPECT_THAT(sut[0], Eq("Sabqponm"));
  EXPECT_THAT(sut[1], Eq("abcryxxl"));
  EXPECT_THAT(sut[2], Eq("accszExk"));
  EXPECT_THAT(sut[3], Eq("acctuvwj"));
  EXPECT_THAT(sut[4], Eq("abdefghi"));
  EXPECT_THAT(sut.size(), Eq(5));
}
