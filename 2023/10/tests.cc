
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

  template<class MAP>
  Navigation(MAP && m_)
  :m(std::forward<MAP>(m_))
    ,p(findS(m))
    ,d(initialDir(m, p))
  {}
  
  void step()
  {
    //Update position and then update direction
    p = p.move(d);
    d = dirFromTile(m.at(p), d);
  }
};

struct NavigationA : Navigation
{
  NavigationA(Map const & m)
    :NavigationA(Navigation(m))
  {}
  NavigationA(istream && in)
    :NavigationA(Map(std::move(in)))
  {}
  NavigationA(Navigation&& n)
    :Navigation(std::move(n))
  {}
  
  long int count{0};
  auto ans() const {return furthestDistance(count);}
  void step(){count++;Navigation::step();}
};

struct NavigationB : Navigation
{
  NavigationB(Map const & m)
    :NavigationB(Navigation(m))
  {}
  NavigationB(istream && in)
    :NavigationB(Map(std::move(in)))
  {}
  NavigationB(Navigation&& n)
    :Navigation(std::move(n))
  {}
  
  void step(){;Navigation::step();}
  int ans() 
  {
    return 0;
  }
};


long int sol(auto n)
{

  auto initialPos = n.p;

  n.step();
  
  while(n.p != initialPos)
    n.step();
  
  return n.ans();
}

long int solA(NavigationA n)
{
  return sol(n);
}

long int solB(NavigationB n)
{
  return sol(n);
}

using Quadrant = int;

struct LoopCounter
{
  int count{0};
  int quadrant{0};

  LoopCounter& push(Quadrant q)
  {
    if(quadrant==0)
      {}
    else if(quadrant==1 && q==4)
      count--;
    else if(quadrant==4 && q==1)
      count++;
    else if(q>quadrant)
      count++;
    else if(q<quadrant)
      count--;
    quadrant=q;
    return *this;
  }
};


/**/

#include <gtest/gtest.h>
#include <gmock/gmock.h>

using namespace testing;

TEST(LoopCounter, examples)
{
  // 1|2
  // -+-
  // 4|3

  auto sut = LoopCounter();
  sut.push(1);
  EXPECT_THAT(sut.count, Eq(0));
  sut.push(2);
  EXPECT_THAT(sut.count, Eq(1));
  sut.push(1);
  EXPECT_THAT(sut.count, Eq(0));
  sut.push(4);
  EXPECT_THAT(sut.count, Eq(-1));
  sut.push(1);
  EXPECT_THAT(sut.count, Eq(0));
}

TEST(DISABLED_solB, example)
{
  ASSERT_THAT(solB(ifstream(EXAMPLE)), Eq(10));
  EXPECT_THAT(solB(ifstream(INPUT)), Eq(0));
}

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
