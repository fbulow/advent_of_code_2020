#include <gtest/gtest.h>
#include "main.cpp"

TEST(rule, ctor_known)
{
  Tile sut({
      "Tile 1621:",
      ".#.##...#.",
      "#..#..#.#.",
      "#.#..#..##",
      ".....#..#.",
      ".#..#...##",
      "#....#...#",
      ".#........",
      "#.#.#....#",
      "...#...#..",
      ".#..#....#"});

  EXPECT_EQ(1621, sut.nr);
  EXPECT_EQ(".#.##...#.", sut.top);
  EXPECT_EQ(".#..#....#", sut.bottom);
  EXPECT_EQ(".##..#.#..", sut.left);
  EXPECT_EQ("..#.##.#.#", sut.right);
}

