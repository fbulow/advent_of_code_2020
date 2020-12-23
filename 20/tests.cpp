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

TEST(Requirement, match)
{
  Tile const t({"Tile 1951:",
      "#.##...##.",
      "#.####...#",
      ".....#..##",
      "#...######",
      ".##.#....#",
      ".###.#####",
      "###.##.##.",
      ".###....#.",
      "..#.#..#.#",
      "#...##.#.."});
    
  Requirement r;
  EXPECT_TRUE(r.match(t));
  r.top=("#...##.#..");
  EXPECT_FALSE(r.match(t));
  r.top="#.##...##.";
  EXPECT_TRUE(r.match(t));
}

TEST(Puzzle, getRequirement)
{
  Puzzle sut(EXAMPLE);
  Coord const origin{0,0};
  {
    auto req = sut.getRequirements(origin);
    EXPECT_TRUE(req.right.empty());
    EXPECT_TRUE(req.left.empty());
    EXPECT_TRUE(req.bottom.empty());
    EXPECT_TRUE(req.top.empty());
    
    auto t1 = Pile(EXAMPLE).getTile(1951).value();
    EXPECT_TRUE(req.match(t1));
    sut.put(t1, origin);
  }

  {
    auto req = sut.getRequirements(origin.down());
    EXPECT_FALSE(req.top.empty());
  }
  {
    auto req = sut.getRequirements(origin.up());
    EXPECT_FALSE(req.bottom.empty());
  }
  {
    auto req = sut.getRequirements(origin.right());
    EXPECT_FALSE(req.left.empty());
  }
  {
    auto req = sut.getRequirements(origin.left());
    EXPECT_FALSE(req.right.empty());
  }
}

TEST(Puzzle, put_internal)
{
  Puzzle sut(EXAMPLE);
  Coord const origin{0,0};

  EXPECT_EQ(9, sut.pile.size());
  EXPECT_NO_THROW(sut.place(1951, origin));
  EXPECT_EQ(8, sut.pile.size());

  EXPECT_THROW(sut.place(1427, origin.right()), exception);//1427 is not adjecent to 1951.
  EXPECT_NO_THROW(sut.place(2311, origin.right()));
  EXPECT_NO_THROW(sut.place(2729, origin.up()));
  EXPECT_NO_THROW(sut.place(2971, origin.up().up()));
  EXPECT_NO_THROW(sut.place(1489, origin.up().up().right()));
}
  

