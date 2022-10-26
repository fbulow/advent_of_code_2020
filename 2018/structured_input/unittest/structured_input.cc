#include<structured_input.hh>

#include<gtest/gtest.h>
#include<gmock/gmock.h>

using namespace std;
using namespace testing;

TEST(formated_read, no_exception_if_no_match_because_input_is_eof)
{
  istringstream in("ost");
  in>>"osten"; // Should not throw
}

TEST(formated_read, second_char_is_diff)
{
  istringstream in("ost");
  try
    {
    in>>"oSt";
    }
  catch(Missmatch &m)
    {
      EXPECT_THAT(m.expected(), Eq("oS"));
      EXPECT_THAT(m.got(),      Eq("os"));
    }
}

TEST(formated_read, space_is_not_ignored)
{
  {
    istringstream in(" aa");
    ASSERT_THROW(in>>"a", Missmatch);
  }
  {
    istringstream in(" aa");
    ASSERT_NO_THROW(in>>" a");
  }
  
}
