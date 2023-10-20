#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "distances.hh"
#include "example.hh"
#include "valve_connection.hh"
#include <vector>
#include "solA.hh"
#include "total_volume.hh"
#include "regions.hh"
#include "path_iteration.hh"

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
  Path p({
    {2,  "DD"},
    {5,  "BB"},
    {9,  "JJ"},
    {17, "HH"},
    {21, "EE"},
    {24, "CC"}});
  
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



TEST(Regions, starts_as_outer)
{
  auto const ret  = Regions({"b", "c"}).outer();
  EXPECT_THAT(ret.size(), Eq(2));
  EXPECT_TRUE(ret.contains("b"));
  EXPECT_TRUE(ret.contains("c"));
}

TEST(Regions, starts_as_outer_start_at_b)
{
  auto const sut  = Regions({"b", "c"})
    .startAt("b");
  
  EXPECT_THAT(sut.edge().size(), Eq(1));
  EXPECT_TRUE(sut.edge().contains("b"));
  EXPECT_THAT(sut.outer().size(), Eq(1));
  EXPECT_TRUE(sut.outer().contains("c"));
}

TEST(pathIteration, isDone_no_regions_left)
{
  int callCount{0};
  pathIteration([&callCount](auto){callCount++;},
		0,
		[](auto, auto){return 1;},
		Regions ({"a"}).startAt("b"),
		Path().moveTo(0, "c"));
  EXPECT_THAT(callCount, Eq(1));
}

TEST(pathIteration, isDone_all_steps_are_too_long)
{
  int callCount{0};
  pathIteration([&callCount](auto){callCount++;},
		1,
		[](auto, auto){return 2;},
		Regions ({
		    "a",
		    "b",
		    "c"
		  }),
		"b"
		);
  EXPECT_THAT(callCount, Eq(1));
}

TEST(Path, moveTo_aa_distance_is_3_minutes_and_one_minute)
{
  auto sut = Path().moveTo(Minutes(3), "AA");
  EXPECT_THAT(sut.size(), 1);
  EXPECT_THAT(sut[0].open, Eq("AA"));
  EXPECT_THAT(sut[0].timePassed, Eq(4));//3+ one minute for opening the vault
}

TEST(Path, moveTo_aa_and_then_bb)
{
  auto sut = Path()
    .moveTo(Minutes(3), "AA")
    .moveTo(Minutes(2), "BB");
  EXPECT_THAT(sut.size(), 2);
  EXPECT_THAT(sut[1].open, Eq("BB"));
  EXPECT_THAT(sut[1].timePassed, Eq(7));//3+2+(2* one minute for opening the vault)
}

TEST(Regions, moveTo)
{
  auto const ret = 
  Regions({"a", "b", "c"})
    .startAt("a")
    .moveTo("b");

  EXPECT_THAT(ret.outer().size(), Eq(1));
  EXPECT_THAT(ret.edge().size(), Eq(1));
  EXPECT_THAT(ret.inner().size(), Eq(1));
  
}

TEST(pathIteration, can_go_to_a)
{
  /*  Possible paths {{1, b}, {3, a}} and {{3, a}}
   */
  std::vector<Path> vp;
  
  pathIteration([&vp](auto ret){vp.emplace_back(std::move(ret));},
		2,
		[](Valve a, Valve b){
		  if(a==b)
		    return 0;
		  if(((a=="b") and (b=="a"))
		     or
		     ((a=="a") and (b=="b")))
		    return 1;
		  else
		    return 2000;
		},
		Regions ({
		    "a",
		    "b",
		    "c"
		  }
		  ),
		"b");
  EXPECT_THAT(vp.size(), Eq(2));
  //  EXPECT_THAT(vp[0].size(), Eq(2));
}
TEST(pathIteration, just_move_to_a)
{
  std::vector<Path> vp;
  
  pathIteration([&vp](auto ret){vp.emplace_back(std::move(ret));},
		2,
		[](Valve a, Valve b){
		  if(a==b)
		    return 0;
		  if(((a=="b") and (b=="a"))
		     or
		     ((a=="a") and (b=="b")))
		    return 1;
		  else
		    return 2000;
		},
		Regions ({
		    "a",
		    "b",
		    "c"
		  }).startAt("b"),
		Path());
  EXPECT_THAT(vp.size(), Eq(1));
  EXPECT_THAT(vp[0].size(), Eq(1));
  EXPECT_THAT(vp[0][0].open , Eq("a"));
  EXPECT_THAT(vp[0][0].timePassed , Eq(2));
}



// #include<iterator>

// class AllPaths
// {
//   std::set<Path> paths_;
// public:
//   using Iterator = std::set<Path>::iterator;

//   Iterator begin() const { return paths_.begin(); }
//   Iterator end()   const { return paths_.end(); }
  
//   AllPaths(Valve start, std::function<Minutes(Valve const &, Valve const &)> distance, Minutes total=30)
//   {
//     pathIteration(std::inserter(paths_, paths_.end()),
// 		  total,
// 		  distance,
// 		  {start},
// 		  {});
//   }
// };
  



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
