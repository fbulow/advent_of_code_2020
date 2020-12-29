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
