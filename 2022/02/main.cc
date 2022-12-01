#include <AoC/getAllLines.hh>

using namespace std;




#include<gtest/gtest.h>
#include<gmock/gmock.h>

using namespace testing;

TEST(input, input_data_is_not_empty)
{
  ASSERT_THAT(getAllLines().size(), Gt(0));
}
