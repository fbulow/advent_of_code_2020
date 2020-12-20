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

TEST(tile, rotate)
{
  Tile sut({
      "Tile 1621:",
      ".#........",
      ".........#",
      ".........#",
      "..........",
      "..........",
      "#.........",
      "#.........",
      "#.........",
      "#.........",
      "......###."});

  sut.rotate();
  
  Tile rot({
      "Tile 1621:",
      ".##.......",
      ".........#",
      ".........#",
      ".........#",
      "..........",
      "..........",
      "..........",
      "..........",
      "#.........",
      ".....####."});

  
  EXPECT_EQ(rot.top   , sut.top		);
  EXPECT_EQ(rot.bottom, sut.bottom	);
  EXPECT_EQ(rot.left  , sut.left	);
  EXPECT_EQ(rot.right , sut.right	);

    
}

TEST(tile, flip)
{
  Tile sut({
      "Tile 1621:",
      ".#........",
      ".........#",
      ".........#",
      "..........",
      "..........",
      "#.........",
      "#.........",
      "#.........",
      "#.........",
      "......###."});

  sut.flip();
  
  Tile ref({
      "Tile 1621:",
      "........#.",
      "#.........",
      "#.........",
      "..........",
      "..........",
      ".........#",
      ".........#",
      ".........#",
      ".........#",
      ".###......"});

  
  EXPECT_EQ(ref.top   , sut.top		);
  EXPECT_EQ(ref.bottom, sut.bottom	);
  EXPECT_EQ(ref.left  , sut.left	);
  EXPECT_EQ(ref.right , sut.right	);

    
}

