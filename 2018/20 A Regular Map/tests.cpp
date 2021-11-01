#include <gtest/gtest.h>
#include "main.cpp"
#include <fstream>
#include <sstream>

TEST(minSteps, empty)
{
  ASSERT_EQ(0, minSteps("$^"));
}

TEST(minSteps, one)
{
  ASSERT_EQ(1, minSteps("^N$"));
}

TEST(minSteps, one_paren)
{
  ASSERT_EQ(1, minSteps("^(N|)$"));
}

TEST(minSteps, fcn_as_argument)
{
  auto fcn = []()
  {
    static int i=0;
    switch(i++)
      {
      case 0:
        return '^';
      case 1:
        return 'N';
      case 2:
        return '$';
      }
    return '\n';
  };
  
  EXPECT_EQ(1, minSteps(fcn,0));
}

TEST(examples, all)
{
    // In the first example (^WNE$), this would be the north-east corner 3 doors away.
  EXPECT_EQ(3, minSteps("^WNE$"));
    // In the second example (^ENWWW(NEEE|SSE(EE|N))$), this would be the south-east corner 10 doors away.
  EXPECT_EQ(10, minSteps("^ENWWW(NEEE|SSE(EE|N))$"));
  // In the third example (^ENNWSWW(NEWS|)SSSEEN(WNSE|)EE(SWEN|)NNN$), this would be the north-east corner 18 doors away.

  //EXPECT_EQ(18, minSteps("^ENNWSWW(NEWS|)SSSEEN(WNSE|)EE(SWEN|)NNN$"));

}

TEST(examples, substr)
{
  EXPECT_EQ(10, minSteps("^(WNSE|)EE(SWEN|)$"));
  //EXPECT_EQ(6, minSteps("^EE(SWEN|)$"));
  //  EXPECT_EQ(6, minSteps("^(WNSE|)EE$"));
                          
}
