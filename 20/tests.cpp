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
  EXPECT_EQ(".#.##...#.", sut.top());
  EXPECT_EQ(".#..#....#", sut.bottom());
  EXPECT_EQ(".##..#.#..", sut.left());
  EXPECT_EQ("..#.##.#.#", sut.right());
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

  
  EXPECT_EQ(rot.top   (), sut.top 	());
  EXPECT_EQ(rot.bottom(), sut.bottom	());
  EXPECT_EQ(rot.left  (), sut.left	());
  EXPECT_EQ(rot.right (), sut.right	());

    
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
      "......###.",
      "#.........",
      "#.........",
      "#.........",
      "#.........",
      "..........",
      "..........",
      ".........#",
      ".........#",
      ".#........",
    });

  EXPECT_EQ(ref.top   (), sut.top	());
  EXPECT_EQ(ref.bottom(), sut.bottom	());
  EXPECT_EQ(ref.left  (), sut.left	());
  EXPECT_EQ(ref.right (), sut.right	());
}

TEST(Pile, read)
{
  Pile sut(EXAMPLE);
  EXPECT_EQ(9, sut.size());
}

// TEST(Puzzle, construct)
// {
//   Puzzle sut(Pile(EXAMPLE));

//   EXPECT_EQ(8, sut.p.size());
// }

TEST(maxSum, first)
{
  EXPECT_EQ(0b1001000000, encodeBinary("#..#......"));
  EXPECT_EQ(0b1001000000, bigKey("#..#......"));
  EXPECT_EQ(0b1001000000, bigKey("......#..#"));
}

TEST(isCorner, topLeft)
{
  auto ans = isCorner(Tile({"Tile 1951:",
		      "#.##...##.",
		      "#.####...#",
		      ".....#..##",
		      "#...######",
		      ".##.#....#",
		      ".###.#####",
		      "###.##.##.",
		      ".###....#.",
		      "..#.#..#.#",
		      "#...##.#.."}),
		 {
		   bigKey("#.##...##."),
		   bigKey("##.#..#..#")});

  ASSERT_TRUE(ans);
}

TEST(getEdges, example)
{
  Pile example(EXAMPLE);
  auto sut = getEdges(example);
  EXPECT_EQ(12, sut.size());

  EXPECT_TRUE(isCorner(example.getTile(1951).value(), sut));
  EXPECT_FALSE(isCorner(example.getTile(2729).value(), sut));
}


TEST(solve, a)
{
  EXPECT_EQ(20899048083289, solveA(EXAMPLE));
  auto ans = solveA(INPUT);
  EXPECT_EQ(30425930368573, ans);
  cout<<"Solution a: "<<ans<<endl;
}
