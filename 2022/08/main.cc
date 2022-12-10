#include <AoC/getAllLines.hh>
#include <numeric>
#include <algorithm>
#include <sstream>

#include "tree.hh"
#include "tree_line.hh"
#include "sweep_line.hh"
#include "forest.hh"

using namespace std;

int solA(vector<string> const &data)
{
  Forrest f(data);
  return f.sweep().countVisible();
}

#include<gtest/gtest.h>
#include<gmock/gmock.h>

using namespace testing;

TEST(a, solA)
{
  EXPECT_THAT(
	      solA(getAllLines()),
	      Eq(1829));

}


TEST(example, solA)
{
  EXPECT_THAT(
	      solA(getAllLines(EXAMPLE)),
	      Eq(21));

}
  

TEST(Forrest, countVisible)
{
  Forrest sut(vector<string>{"00", "11"});
  EXPECT_THAT(sut.countVisible(), Eq(0));
  sut[0][0].tick();
  EXPECT_THAT(sut.countVisible(), Eq(1));
  sut[1][0].tick();
  EXPECT_THAT(sut.countVisible(), Eq(2));
  sut[1][0].tick();
  EXPECT_THAT(sut.countVisible(), Eq(2));
}

TEST(TreeLine, streamOut)
{
  TreeLine tl("012345");
  ostringstream out;
  out<<tl;
  EXPECT_EQ("012345", out.str());
}

TEST(Forrest, transpose)
{
  auto orig = Forrest ({
      TreeLine("30373")
      ,TreeLine("25512")});

  EXPECT_THAT(orig.toString(),
	      Eq(R"""(30373
25512
)"""));
  
  EXPECT_THAT(orig.transpose().toString(),
	      Eq(R"""(32
05
35
71
32
)"""));
  
}

TEST(Forrest, sweepLines)
{
  Forrest sut({
      TreeLine("30373")
      ,TreeLine("25512")});
  sut.sweepLines();
  EXPECT_TRUE	(sut[0][0].ticked());
  EXPECT_FALSE	(sut[0][1].ticked());
  EXPECT_FALSE	(sut[0][2].ticked());
  EXPECT_TRUE	(sut[0][3].ticked());
  EXPECT_TRUE	(sut[0][4].ticked());
    
  EXPECT_TRUE	(sut[1][0].ticked());
  EXPECT_TRUE	(sut[1][1].ticked());
  EXPECT_TRUE	(sut[1][2].ticked());
  EXPECT_FALSE	(sut[1][3].ticked());
  EXPECT_TRUE	(sut[1][4].ticked());
  
}

TEST(sweepLine, examples)
{
  {  
    TreeLine sut("5184");
    sweepLine(sut.begin(), sut.end());
    EXPECT_TRUE	(sut[0].ticked());
    EXPECT_FALSE	(sut[1].ticked());
    EXPECT_TRUE	(sut[2].ticked());
    EXPECT_FALSE	(sut[3].ticked());
  }
  {  
    TreeLine sut("5184");
    sweepLine(sut.rbegin(), sut.rend());
    EXPECT_FALSE (sut[0].ticked());
    EXPECT_FALSE (sut[1].ticked());
    EXPECT_TRUE	 (sut[2].ticked());
    EXPECT_TRUE  (sut[3].ticked());
  }
}


TEST(Tree, all)
{
  Tree sut('8');
  EXPECT_EQ('8', sut.value());

  ASSERT_FALSE(sut.ticked());
  sut.tick();
  ASSERT_TRUE(sut.ticked());

}

  
















