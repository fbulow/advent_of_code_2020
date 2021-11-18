#include "fast_forward.hpp"
#include <gtest/gtest.h>

TEST(fast_forward, one)
{
  string s("(NEEE|SSE(EE|N))$");
  ASSERT_EQ(5,
            distance(s.begin(),
                     to_closing_or_branch(s.begin(), s.end())));
}
