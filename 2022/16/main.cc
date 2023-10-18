#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "distances.hh"
#include "example.hh"
#include "valve_connection.hh"
#include <vector>
#include "solA.hh"
#include "total_volume.hh"
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

TEST(totalFlow, example_valves)
{
  Path p{
    {2,  "DD"},
    {5,  "BB"},
    {9,  "JJ"},
    {17, "HH"},
    {21, "EE"},
    {24, "CC"}};
  
  std::map<Valve, Flow> flowRates{
    {"AA", 0},
    {"BB", 13},
    {"CC", 2},
    {"DD", 20},
    {"EE", 3},
    {"FF", 0},
    {"GG", 0},
    {"HH", 22},
    {"II", 0},
    {"JJ", 21}
  };

  EXPECT_THAT(totalVolume(p, flowRates),
	      1651);
  
}






TEST(SolA, zero_if_no_path)
{
  class : public PathGenerator{
    std::optional<Path> next() {return {};}
  } pg;

  EXPECT_EQ(0,
	    SolA(
		 [](auto const&){return 5;},
		 pg));
}

TEST(SolA, largest_value)
{
  class : public PathGenerator{
    int i{0};
    
  public:
    std::optional<Path> next() {
      switch(i++)
	{
	case 0:
	  return Path();
	case 1:
	  return Path();
	default:
	  return std::nullopt;
	}
    }
  } pg;

  int i{5};
  EXPECT_EQ(5,
	    SolA(
		 [&i](auto const&){return i--;},
		 pg));
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
//     EXPECT_TRUE(ans.contains(ValveConnection("JJ", "II", 1)));
//   }
//   {
//     auto ans = sut.from(Valve("JJ"), Steps(2));

//     EXPECT_EQ(ans.size(), 2);
//     EXPECT_TRUE(ans.contains(ValveConnection("JJ", "II", 1)));
//     EXPECT_TRUE(ans.contains(ValveConnection("JJ", "AA", 2)));
//   }
// }
