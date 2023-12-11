
#include "impl.cc"

Dir dirFromTile(Tile standingOn, Dir lastMoved)
{
  switch(standingOn)
    {
    case '|':
    case '-':
      return lastMoved;
    case 'L':
      if(lastMoved=='S')
	return 'E';
      else
	return 'N';
    case 'J':
      if(lastMoved=='S')
	return 'W';
      else
	return 'N';
    case '7':
      if(lastMoved=='N')
	return 'W';
      else
	return 'S';
    case 'F':
      if(lastMoved=='N')
	return 'E';
      else
	return 'S';

    }
  return '.';
}

struct Navigation{
  Map m;
  Pos p;
  Dir d;
  
  void step()
  {
    //Update position and then update direction
    p = p.move(d);
    d = dirFromTile(m.at(p), d);
  }
};

long int solA(Map const & m)
{
  auto initialPos = findS(m);

  Navigation n{m, initialPos, initialDir(m, initialPos)};

  long int count{1};
  n.step();
  
  while(n.p != initialPos)
    {
      n.step();
      count++;
    }
  
  return furthestDistance(count);
}

long int solA(istream &&in)
{
  Map m;
  string row;
  while(getline(in,row))
    m.push_back(row);
  return solA(m);
}

/**/

#include <gtest/gtest.h>
#include <gmock/gmock.h>

using namespace testing;

TEST(dirFromTile, example)
{
  EXPECT_THAT(dirFromTile('|', 'N'), Eq('N'));
  EXPECT_THAT(dirFromTile('-', 'E'), Eq('E'));
  EXPECT_THAT(dirFromTile('L', 'S'), Eq('E'));
  EXPECT_THAT(dirFromTile('L', 'W'), Eq('N'));
}

TEST(solA, example)
{
  {
    auto m = Map{
	".....",
	".S-7.",
	".|.|.",
	".L-J.",
	"....."};
    EXPECT_THAT(solA(m), Eq(4));
  }

  {
    auto m = Map{
      "..F7.",
      ".FJ|.",
      "SJ.L7",
      "|F--J",
      "LJ..."};
    EXPECT_THAT(solA(m), Eq(8));
  }
  
  EXPECT_THAT(solA(ifstream(INPUT)), Eq(6613));
}

TEST(initialDir, N)
{
  auto m = Map{
    ".....",
    ".S-7.",
    ".|.|.",
    ".L-J.",
    "....."};
  EXPECT_THAT(initialDir(m, {1,1}), AnyOf(Eq('E'), Eq('S')));
}


TEST(isValidMove, N)
{
  auto m = Map{
    ".....",
    ".F-7.",
    ".|.|.",
    ".L-J.",
    "....."};

    EXPECT_FALSE(isValidMove(m, {1,1}, 'N'));
    EXPECT_TRUE(isValidMove(m, {1,1}, 'E'));
}

TEST(furthestDistance, example)
{
  EXPECT_THAT(
	      furthestDistance(8),
	      Eq(4));
}

TEST(nextDir, example)
{
  EXPECT_THAT(nextDir('N'), Eq('E'));
  EXPECT_THAT(nextDir('E'), Eq('S'));
  EXPECT_THAT(nextDir('S'), Eq('W'));
  EXPECT_THAT(nextDir('W'), Eq('N'));
}

TEST(nextValue, example)
{
  auto m = Map{
    ".....",
    ".S-7.",
    ".|.|.",
    ".L-J.",
    "....."};

  auto pos = findS(m);
  EXPECT_THAT(pos.row(), Eq(1));
  EXPECT_THAT(pos.col(), Eq(1));

}
