#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "distances.hh"
#include "example.hh"
#include "valve_connection.hh"


using namespace testing;

TEST(score, eval)
{
  auto input = example();
  EXPECT_THAT( 
	      Score()
	      .log(2 , input.flow("DD"))
	      .log(5 , input.flow("BB"))
	      .log(9 , input.flow("JJ"))
	      .log(17, input.flow("HH"))
	      .log(21, input.flow("EE"))
	      .log(24, input.flow("CC"))
	      .total(),
	      Eq(1651));
}

TEST(distance, example)
{
  EXPECT_THAT(distance(example(), "AA", "DD"),
	      Eq(1));
  EXPECT_THAT(distance(example(), "AA", "CC"),
	      Eq(2));
  EXPECT_THAT(distance(example(), "CC", "AA" ),
	      Eq(2));
}

TEST(ValveConnection, from_is_less_than_to_right_order_in_ctor)
{
  ValveConnection const sut("AA", "BB", 55);
  EXPECT_THAT(sut.from (), Eq("AA"));
  EXPECT_THAT(sut.to   (), Eq("BB"));
  EXPECT_THAT(sut.steps(), Eq(55));
  
}

TEST(ValveConnection, from_is_less_than_to_wrong_order_in_ctor)
{
  ValveConnection const sut("BB", "AA", 55);
  EXPECT_THAT(sut.from (), Eq("AA"));
  EXPECT_THAT(sut.to   (), Eq("BB"));
  EXPECT_THAT(sut.steps(), Eq(55));
  
}

TEST(ValveConnection, less)
{
    ValveConnection a("BB", "AA", 55);
    ValveConnection b("BB", "AA", 55);
    EXPECT_FALSE(a<b);
    EXPECT_FALSE(b<a);
}

TEST(ValveConnection, not_same)
{
    ValveConnection a("BB", "AA", 55);
    ValveConnection b("BB", "A", 55);
    EXPECT_TRUE((a<b) || (b<a));
}



// TEST(distance_cache, jj_to_ii)
// {
//   auto sut = 
//     Distance( example(),
// 	      "JJ",
// 	      3
// 	      );
  
//   {
//     auto ans = sut.from(Valve("JJ"), Steps(1));

//     EXPECT_EQ(ans.size(), 1);
//     EXPECT_TRUE(ans.contains(ValveAndSteps("II", 1)));
//   }
//   {
//     auto ans = sut.from(Valve("JJ"), Steps(2));

//     EXPECT_EQ(ans.size(), 2);
//     EXPECT_TRUE(ans.contains(ValveAndSteps("II", 1)));
//     EXPECT_TRUE(ans.contains(ValveAndSteps("AA", 2)));
//   }
// }
