#include <AoC/getAllLines.hh>
#include <numeric>
#include <algorithm>
#include <sstream>
#include <ranges>
#include <iterator>

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

using namespace std;
using ranges::iota_view;

int visibleTrees(auto start, auto end)
{
  auto limit = start->value();
  int ret =0;
  start++;
  while(start!=end)
    {
      if(start->value()>=limit)
	return ret+1;
      else
	{
	  ret++;
	  start++;
	}
    }
    return ret;
}

int sweepLeft(TreeLine t, int col)
{
  return visibleTrees(next(t.rbegin(), t.size()-col-1), t.rend());
}

int sweepRight(TreeLine t, int col)
{
  return visibleTrees(next(t.begin(), col), t.end());
}

int sweepLeftAndRight(TreeLine t, int col)
{
  return sweepLeft(t, col) * sweepRight(t, col);
}

int scenicScore(Forrest a, int row, int col)
{
  auto original   = sweepLeftAndRight(a[row], col);
  auto transposed = sweepLeftAndRight(a.transpose()[col], row);
    
  return original * transposed;
    
}



int solB(vector<string> const &data)
{
  Forrest const a(data);
  int ret=0;
  for(int row = 0; row<a.size(); row++)
    for(int col =0; col<a[0].size(); col++)
      ret=max(ret, scenicScore(a, row, col));
  return ret;
}


#include<gtest/gtest.h>
#include<gmock/gmock.h>

using namespace testing;

TEST(b, real)
{
  EXPECT_THAT(solB(getAllLines()), Eq(291840));
}


TEST(b, example)
{
  EXPECT_THAT(solB(getAllLines(EXAMPLE)), Eq(8));
}

TEST(sweepLeftAndRight, example)
{
  TreeLine sut("33549");
  EXPECT_EQ(2 ,sweepLeft (sut, 2));
  EXPECT_EQ(2 ,sweepRight(sut, 2));
}

TEST(visibleTrees, example_right)
{
  TreeLine sut("33549");
  EXPECT_THAT(visibleTrees(sut.begin(), sut.end()),
	      Eq(1));
}

TEST(visibleTrees, example_left)
   {
     TreeLine sut("33549");
     EXPECT_THAT(visibleTrees(sut.rbegin(), sut.rend()),
		 Eq(4));
   }

TEST(visibleTrees, right_two_visible)
{
  TreeLine sut("549");
  EXPECT_EQ(2, visibleTrees(sut.begin(), sut.end()));

}

TEST(sweepLeft, example_)
{
  //            01234
  TreeLine sut("33549");

  EXPECT_EQ(1, sweepLeft(sut, 1));
}

TEST(sweepRight, example_right)
{
  //            01234
  TreeLine sut("33549");

  EXPECT_EQ(2, sweepRight(sut, 2));
}


TEST(scenicScore, example)
{
  Forrest sut(getAllLines(EXAMPLE));
  
  EXPECT_THAT(scenicScore(sut, 3, 2), Eq(8));
}

TEST(a, solA)
{
  EXPECT_THAT(
	      solA(getAllLines()),
	      Eq(1829));

}

TEST(a, example)
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

  
















