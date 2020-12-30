#include <gtest/gtest.h>
#include "main.cpp"


TEST(step, inverses)
{
  Coord origin;

  EXPECT_EQ(origin, step(step(origin, Di::e), Di::w));

  EXPECT_NE(origin, step(origin, Di::nw));
  EXPECT_EQ(origin, step(step(origin, Di::nw), Di::se));

  EXPECT_NE(origin, step(origin, Di::sw));
  EXPECT_EQ(origin, step(step(origin, Di::ne), Di::sw));
  
}

TEST(step, two_ways_west)
{
  Coord origin;

  EXPECT_EQ(step(origin, Di::w),
            step(step(origin, Di::nw), Di::sw));  
}

TEST(steps, list_argument)
{
  EXPECT_EQ(step({Di::w}),
            step({Di::nw, Di::sw}));
}

TEST(step, two_ways_north_west)
{

  EXPECT_EQ(step({Di::ne}),
            step({Di::nw, Di::ne, Di::se}));  
}

TEST(step, two_ways_south)
{
  EXPECT_EQ(step({Di::se, Di::sw}),
            step({Di::sw, Di::se}));
}

TEST(parseNav, one)
{
  EXPECT_EQ(Di::e, Nav("e")[0]);
  EXPECT_EQ(Di::w, Nav("w")[0]);
  EXPECT_EQ(Di::ne, Nav("ne")[0]);
  EXPECT_EQ(Di::nw, Nav("nw")[0]);

  EXPECT_EQ(1, Nav("nw").size());
  EXPECT_EQ(0, Nav("").size());
}

TEST(parseNav, complex)
{
  Nav sut("esew");
  EXPECT_EQ(3, sut.size());
  EXPECT_EQ(Di::e,  sut[0]);
  EXPECT_EQ(Di::se, sut[1]);
  EXPECT_EQ(Di::w,  sut[2]);
  
}

TEST(solution, a)
{
  ASSERT_EQ(10, solutionA(EXAMPLE));
  auto ans = solutionA(INPUT);
  EXPECT_EQ(263, ans);
  cout<<"Solution A: "<<ans<<endl;
}

TEST(HeatMap, santiyChecks_independent_points)
{
  BlackTiles bt;
  bt.toggle({0,0});
  {
    Heat sut(bt);
    EXPECT_EQ(7, sut.size());
    EXPECT_EQ(6, count_if(sut.begin(), sut.end(), [](auto &x){return x.second==1;}));
    EXPECT_EQ(1, count_if(sut.begin(), sut.end(), [](auto &x){return x.second==0;}));
  }
}
     
TEST(HeatMap, santiyChecks_near_points)
{
  BlackTiles bt;

  bt.toggle(step({}));
  bt.toggle(step({Di::w}));
  
  Heat sut(bt);
  EXPECT_EQ(10, sut.size());
  EXPECT_EQ(8,  count_if(sut.begin(), sut.end(), [](auto &x){return x.second==1;}));
  EXPECT_EQ(2,  count_if(sut.begin(), sut.end(), [](auto &x){return x.second==2;}));
}

TEST(nextDay, flip_to_black)
{
  BlackTiles bt;

  bt.toggle(step({}));
  bt.toggle(step({Di::w}));

  bt.nextDay();
  EXPECT_TRUE( bt.black(step({Di::nw})) );
  EXPECT_TRUE( bt.black(step({Di::sw})) );
  EXPECT_EQ(4, bt.countBlack());
}

TEST(nextDay, flip_to_white)
{
  BlackTiles bt;
  bt.toggle(step({}));
  EXPECT_EQ(1, bt.countBlack());
  bt.nextDay();
  EXPECT_EQ(0, bt.countBlack());
}

TEST(nextDay, examples)
{
  BlackTiles sut(EXAMPLE);
  EXPECT_EQ(10, sut.countBlack());

  sut.nextDay();
  EXPECT_EQ(15, sut.countBlack());

  sut.nextDay();
  EXPECT_EQ(12, sut.countBlack());

  sut.nextDay();
  EXPECT_EQ(25, sut.countBlack());

}


TEST(solution, b)
{
  ASSERT_EQ(2208, solutionB(EXAMPLE));
  cout<<"Solution B: "<<solutionB(INPUT)<<endl;
}
