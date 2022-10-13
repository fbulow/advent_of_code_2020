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

Board example_a_board()
{
  Board b(2);

  b.put(2, 'A');
  b.put(2, 'B');

  b.put(4, 'D');
  b.put(4, 'C');

  b.put(6, 'C');
  b.put(6, 'B');

  b.put(8, 'A');
  b.put(8, 'D');
  return b;
}

TEST(DISABLED_solution_a, example)
{

  EXPECT_THAT(Solver(example_a_board()),
	      Eq(12521));

}

TEST(solution_a, step_by_step_right_score)
{
  auto sut = 
    example_a_board()
    .apply({6,3})
    .apply({4,5})
    .apply({5,6})
    .apply({4,5})
    .apply({3,4})
    .apply({2,3})
    .apply({3,4})

    .apply({8,7})
    .apply({8,9})

    .apply({7,8})
    .apply({5,8})

    .apply({9,2});
    ;

  cout<<sut<<endl;
  
  EXPECT_THAT(sut.score()
	      ,Eq(
		  12521
		  //40+400+3000+30+40+2003+7000+8
		  ));
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
	      Solver(b, 44175), Eq(44169));
}
