#include <gtest/gtest.h>
#include "main.cpp"
#include "gmock/gmock.h"

TEST(Room, ctor)
{
  Room sut(READTEST);
  EXPECT_EQ(1, sut.count('a'));
  EXPECT_EQ(1, sut.count('b'));
  EXPECT_EQ(2, sut.count('c'));
  EXPECT_EQ(2, sut.count('d'));
  EXPECT_EQ(3, sut.count('e'));
}


TEST(Room, countVisible)
{
  {
    Room sut({
        ".......#.",
        "...#.....",
        ".#.......",
        ".........",
        "..#L....#",
        "....#....",
        ".........",
        "#........",
        "...#....."});

    ASSERT_EQ('L', sut[Coord(4,3)]);
    ASSERT_EQ(8, sut.countVisible(Coord(4,3)));
  }
  {
    Room sut({
        ".......#.",
        ".........",
        ".#.......",
        ".........",
        "..#L....#",
        "....#....",
        ".........",
        "#........",
        "...#....."});

    ASSERT_EQ('L', sut[Coord(4,3)]);
    ASSERT_EQ(7, sut.countVisible(Coord(4,3)));
    ASSERT_EQ(1, sut.countVisible(Coord(4,3), '.'));
  }
}

TEST(Room, visible)
{

    Room sut({
        ".......A.",
        "...B.....",
        ".c.......",
        ".........",
        "..DL....E",
        "....F....",
        ".........",
        "G........",
        "...H....."});

    ASSERT_EQ('A', sut.visible(Coord(4,3), Dir(-1,1)));
    
}
     

TEST(Room, eq)
{

    Room sut({
        ".......A.",
        "...B.....",
        ".c.......",
        ".........",
        "..DL....E",
        "....F....",
        ".........",
        "G........",
        "...H....."});

    ASSERT_EQ(sut, sut);
    
    Room removedL({
        ".......A.",
        "...B.....",
        ".c.......",
        ".........",
        "..D.....E",
        "....F....",
        ".........",
        "G........",
        "...H....."});

    ASSERT_FALSE(sut == removedL);
}

TEST(Cell, def)
{
  //If a seat is empty (L) and there are no occupied seats adjacent to
  //it, the seat becomes occupied.

  EXPECT_EQ('#', Cell('L', 0).nextState());

  EXPECT_EQ('L', Cell('L', 1).nextState());
  EXPECT_EQ('L', Cell('L', 2).nextState());
  EXPECT_EQ('L', Cell('L', 3).nextState());
  EXPECT_EQ('L', Cell('L', 4).nextState());
  EXPECT_EQ('L', Cell('L', 5).nextState());
  EXPECT_EQ('L', Cell('L', 6).nextState());
  
  //If a seat is occupied (#) and four or more seats adjacent to it
  //are also occupied, the seat becomes empty.

  //but...
  
  //Also, people seem to
  //be more tolerant than you expected: it now takes five or more
  //visible occupied seats for an occupied seat to become empty
  //(rather than four or more from the previous rules).
  
  EXPECT_EQ('#', Cell('#', 1).nextState());
  EXPECT_EQ('#', Cell('#', 2).nextState());
  EXPECT_EQ('#', Cell('#', 3).nextState());
  EXPECT_EQ('#', Cell('#', 4).nextState());
  EXPECT_EQ('L', Cell('#', 5).nextState());
  EXPECT_EQ('L', Cell('#', 6).nextState());

  //Otherwise, the seat's state does not change.
  EXPECT_EQ('.', Cell('.', 0).nextState());
  EXPECT_EQ('.', Cell('.', 1).nextState());
  EXPECT_EQ('.', Cell('.', 2).nextState());
  EXPECT_EQ('.', Cell('.', 3).nextState());
  EXPECT_EQ('.', Cell('.', 4).nextState());
  EXPECT_EQ('.', Cell('.', 5).nextState());
  EXPECT_EQ('.', Cell('.', 6).nextState());
}



TEST(solution, b)
{
  ASSERT_EQ(26, solutionB(EXAMPLE));
  cout<<"Solution b: "<<solutionB(INPUT)<<endl;
}


TEST(step, example)
{
  Room before({
      "L.LL.LL.LL",
      "LLLLLLL.LL",
      "L.L.L..L..",
      "LLLL.LL.LL",
      "L.LL.LL.LL",
      "L.LLLLL.LL",
      "..L.L.....",
      "LLLLLLLLLL",
      "L.LLLLLL.L",
      "L.LLLLL.LL"
    });

  Room after({
      "#.##.##.##",
      "#######.##",
      "#.#.#..#..",
      "####.##.##",
      "#.##.##.##",
      "#.#####.##",
      "..#.#.....",
      "##########",
      "#.######.#",
      "#.#####.##"
    });
  EXPECT_EQ(after, step(before));
}

TEST(step, failing)
{
  Room before({
      "#.##.##.##",
      "#######.##",
      "#.#.#..#..",
      "####.##.##",
      "#.##.##.##",
      "#.#####.##",
      "..#.#.....",
      "##########",
      "#.######.#",
      "#.#####.##"
    });

  Room after({
      "#.LL.LL.L#",
      "#LLLLLL.LL",
      "L.L.L..L..",
      "LLLL.LL.LL",
      "L.LL.LL.LL",
      "L.LLLLL.LL",
      "..L.L.....",
      "LLLLLLLLL#",
      "#.LLLLLL.L",
      "#.LLLLL.L#"});
  EXPECT_EQ(after, step(before));
}


