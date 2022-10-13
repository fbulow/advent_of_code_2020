#include "solver.hh"
#include "board.hh"

#include<gtest/gtest.h>
#include<gmock/gmock.h>
using namespace testing;

TEST(solution_b, one_step)
{
  Board b(
"#############"
"#..........D#"
"###A#B#C#.###"
"  #A#B#C#D#  "
"  #A#B#C#D#  "
"  #A#B#C#D#  "
"  #########  ");
  EXPECT_THAT(
	      Solver(b), Eq(3000));
}
