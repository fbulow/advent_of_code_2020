#include <gtest/gtest.h>
#include"impl.hh"

TEST(Key, read)
{
  istringstream in("#..#");
  Key sut;
  in>>sut;
  EXPECT_EQ(true,  sut[0]);
  EXPECT_EQ(false, sut[1]);
  EXPECT_EQ(false, sut[2]);
  EXPECT_EQ(true,  sut[3]);
}

TEST(Board, read)
{
  Board sut;
  istringstream in(".#\n"
                   "..\n"
                   "#.\n");
  in>>sut;
  EXPECT_EQ(2, sut.size());
  EXPECT_TRUE(sut.contains(Coord(0,1)));
  EXPECT_TRUE(sut.contains(Coord(2,0)));
}

TEST(Key, invert)
{
  ;
  Key sut("#..#");

  EXPECT_EQ(true,  sut[0]);
  EXPECT_EQ(false, sut[1]);
  EXPECT_EQ(false, sut[2]);
  EXPECT_EQ(true,  sut[3]);

  sut.invert();

  EXPECT_EQ(not true,  sut[0]);
  EXPECT_EQ(not false, sut[1]);
  EXPECT_EQ(not false, sut[2]);
  EXPECT_EQ(not true,  sut[3]);

}

TEST(Board, check)
{
  Accumulator sut;
  sut.poke(Coord{Row{0},Col{0}});
  EXPECT_EQ(9, sut.size());
  EXPECT_TRUE(sut.contains(Coord(Row{-1},Col{-1})));
  EXPECT_TRUE(sut.contains(Coord(Row{-1},Col{ 0})));
  EXPECT_TRUE(sut.contains(Coord(Row{-1},Col{ 1})));
  EXPECT_TRUE(sut.contains(Coord(Row{ 0},Col{-1})));
  EXPECT_TRUE(sut.contains(Coord(Row{ 0},Col{ 0})));
  EXPECT_TRUE(sut.contains(Coord(Row{ 0},Col{ 1})));
  EXPECT_TRUE(sut.contains(Coord(Row{ 1},Col{-1})));
  EXPECT_TRUE(sut.contains(Coord(Row{ 1},Col{ 0})));
  EXPECT_TRUE(sut.contains(Coord(Row{ 1},Col{ 1})));
}

TEST(KeyIndex, ctor)
{
  KeyIndex sut(Coord{Row{1}, Col{1}},
               Board("..#\n"
                     "...\n"
                     ".#.\n"));
  EXPECT_EQ(KeyIndex(0b001000010), sut);
               
}

TEST(iteration, example)
{
  Key k("..#.#..#####.#.#.#.###.##.....###.##.#..###.####..#####..#....#..#..##..###..######.###...####..#..#####..##..#.#####...##.#.#..#.##..#.#......#.###.######.###.####...#.##.##..#..#..#####.....#.#....###..#.##......#.....#..#..#..##..#...##.######.####.####.#.#...#.......#..#.#.#...####.##.#......#..#...##.#.##..#...##.#.##..###.#......#.#.......#.#.#.####.###.##...#.....####.#..#..#.##.#....##..#.####....##...##..#...#......#.#.......#.......##..####..#...#.#.#...##..#.#..###..#####........#..####......#..#");

  Board b("#..#.\n"
          "#....\n"
          "##..#\n"
          "..#..\n"
          "..###\n");

  b=iteration(k,b);
  EXPECT_EQ(".##.##.\n"
            "#..#.#.\n"
            "##.#..#\n"
            "####..#\n"
            ".#..##.\n"
            "..##..#\n"
            "...#.#.\n",
            b.str());

  b=iteration(k,b);
  EXPECT_EQ(".......#.\n"
            ".#..#.#..\n"
            "#.#...###\n"
            "#...##.#.\n"
            "#.....#.#\n"
            ".#.#####.\n"
            "..#.#####\n"
            "...##.##.\n"
            "....###..\n",            
            b.str());
}
