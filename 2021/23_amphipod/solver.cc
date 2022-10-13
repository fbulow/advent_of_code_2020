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

TEST(solution_b, all_steps)
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

TEST(Solver, handles_a_fail)
{
  Board b(
"#############"
"#.A.A.......#"
"###B#.#.#.###"
"  #D#.#.#.#  "
"  #D#.#.#.#  "
"  #A#.#.#.#  "
"  #########  "
	  );
  EXPECT_FALSE(Solver(b));

}

TEST(DISABLED_solution_b, example)
{
  Board b(
"#############"
"#...........#"
"###B#C#B#D###"
"  #D#C#B#A#  "
"  #D#B#A#C#  "
"  #A#D#C#A#  "
"  #########  "
	  );
  EXPECT_THAT(
	      Solver(b), Eq(44169));
}
