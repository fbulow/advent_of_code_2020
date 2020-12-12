#include <gtest/gtest.h>
#include "main.cpp"

using Room = vector<string>;

TEST(get, Instruction)
{
  Inst sut;
  istringstream in("F10");
  in>>sut;

  EXPECT_EQ('F', sut.cmd);
  EXPECT_EQ(10 , sut.arg);
}

TEST(get, input)
{
  Instructions sut(INPUT);
  EXPECT_EQ(790, sut.size());
  
}

TEST(Ship, rotate)
{
  Ship sut;
  EXPECT_EQ('E', sut.direction());

  sut.apply(Inst{'L', 90});
  EXPECT_EQ('N', sut.direction());

  sut.apply(Inst{'L', 90});
  EXPECT_EQ('W', sut.direction());

  sut.apply(Inst{'L', 90});
  EXPECT_EQ('S', sut.direction());

  sut.apply(Inst{'R', 90});
  EXPECT_EQ('W', sut.direction());
}


TEST(Pos, step)
{
  EXPECT_EQ(Pos(-1,0),
	    step(Pos(0,0), 'N', 1));
  EXPECT_EQ(Pos( 1,0),
	    step(Pos(0,0), 'S', 1));
  EXPECT_EQ(Pos( 0,-1),
	    step(Pos(0,0), 'W', 1));
  EXPECT_EQ(Pos( 0,1),
	    step(Pos(0,0), 'E', 1));

}

TEST(Ship, step)
{
  Ship sut;
  EXPECT_EQ(Pos(0,0), sut.pos());

  auto ref = step(sut.pos(), 'N', 1);
  
  sut.apply({'N', 1});
  EXPECT_EQ(ref, sut.pos());
  
  
}

TEST(Ship, stepForward)
{
  Ship sut;
  ASSERT_EQ(Pos(0,0), sut.pos());
  ASSERT_EQ('E', sut.direction());
  
  sut.apply({'F', 1});
  EXPECT_EQ(Pos(0,1), sut.pos());
  
}

TEST(Pos, manhattanMetric)
{
  EXPECT_EQ(0, manhattanMetric(Pos{0,0}));
  EXPECT_EQ(4, manhattanMetric(Pos{-4,0}));
  EXPECT_EQ(8, manhattanMetric(Pos{-4,4}));
  EXPECT_EQ(8, manhattanMetric(Pos{4,-4}));
}

TEST(Solve, a)
{
  EXPECT_EQ(25,   solveA(EXAMPLE));

  auto const ans = solveA(INPUT);
  cout<<"Solution A: "<<ans<<endl;
  EXPECT_EQ(2228, ans);
}

TEST(Solve, b)
{
  EXPECT_EQ(286,   solveB(EXAMPLE));

  auto const ans = solveB(INPUT);
  cout<<"Solution A: "<<ans<<endl;
  EXPECT_EQ(42908, ans);
}
