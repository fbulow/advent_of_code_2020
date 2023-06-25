#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <vector>
#include "read_input.hh"
#include "row.hh"
#include "navigator.hh"
#include "distance_list.hh"
#include "object_mother.hpp"
using namespace testing;
using namespace std;

namespace A{
  auto Navigator = []()
  {
    struct Navigator_ : ObjectMother<Navigator_, ::Navigator, ::Destinations, ::Valve, ::Steps>
    {
      Navigator_ wValve(Valve v){ return w(v); }
    };
    return Navigator_::defaultValues(
				     Destinations{},
				     Valve(""),
				     Steps(0));
  };

  auto Row = []
  {
    struct Row_: ObjectMother<Row_,
			      ::Row,
			      std::string, 
			      vector<std::string>,
			      int>
    {
      Row_ wFrom(string s) const
      {
	auto ret = clone();
	std::get<string>(ret.arg) = std::move(s);
	return ret;
      }
      
      Row_ addDest(std::string s) const
      {
	auto ret = clone();
	std::get<vector<string>>(ret.arg).emplace_back(std::move(s));
	return ret;
      }
    };
    return Row_::defaultValues(string(""), vector<std::string>{}, 0);
  };
};

TEST(Row, allValves)
{
  auto sut = A::Row()
    .wFrom("a")
    .addDest("b")
    .addDest("c")
    .get().allValves();

  EXPECT_THAT(sut.size(), Eq(3));
}

TEST(DistanceList, a_to_b_is_one)
{
  auto sut = DistanceList( vector<Row>{A::Row()
				       .w(string("a"))
				       .addDest("b")
				       .addDest("c")
				       .get()
    });
  EXPECT_EQ( 0, sut.steps("a", "a") );
  EXPECT_EQ( 1, sut.steps("a", "b") );
  EXPECT_EQ( 1, sut.steps("b", "a") );
  //  EXPECT_EQ( 2, sut.steps("b", "c") );
}


TEST(Navigator, goTo_reduces_steps_left)
{
  auto sut = A::Navigator()
    .w<Destinations>({"BB"})
    .w<Valve>("AA")
    .w<Steps>(10)
    .get();

  sut.add(Distance("AA", "BB", 2));

  EXPECT_THAT(sut.goTo("AA").getSteps(),
	      Eq(10-2-1) // Two for the move and one to open valve
	      );
}

TEST(Navigator, goTo_changes_location)
{
  auto sut = A::Navigator().w<Destinations>(Destinations{"AA", "BB"})
    .get();
  EXPECT_THAT(
	      sut.goTo("AA").getLocation(),
	      Eq("AA")
	      );
}

TEST(Navigator, destination_removed_when_goto_is_reached)
{
  auto sut = A::Navigator().w(Destinations{"AA", "BB"}).get();
  EXPECT_THAT(
	      sut.goTo("AA").getDestinations(),
	      ElementsAre("BB")
	      );
}

TEST(Navigator, ctor)
{
  Navigator sut({"BB", "CC"}, "AA", Steps(11));
  EXPECT_THAT(sut.getDestinations(),
	      ElementsAre("BB","CC"));
  EXPECT_THAT(sut.getLocation(),
	      Eq("AA"));
  EXPECT_THAT(sut.getSteps(),
	      Eq(11));
  
}

TEST(scrubbed, example)
{
  {
    auto sut = Row::fromString("Valve AA has flow rate=0; tunnels lead to valves DD, II, BB");
    EXPECT_THAT(sut.from, Eq("AA"));
    EXPECT_THAT(sut.rate, Eq(0));
    EXPECT_THAT(sut.to, Contains("DD"));
    EXPECT_THAT(sut.to, Contains("II"));
    EXPECT_THAT(sut.to, Contains("BB"));
    EXPECT_THAT(sut.to.size(), Eq(3));
  }
  {
    auto sut = Row::fromString("Valve HH has flow rate=22; tunnel leads to valve GG");
    EXPECT_THAT(sut.from, Eq("HH"));
    EXPECT_THAT(sut.rate, Eq(22));
    EXPECT_THAT(sut.to, Contains("GG"));
    EXPECT_THAT(sut.to.size(), Eq(1));
  }
}


TEST(readInput, example)
{
  auto sut = readInput(EXAMPLE);
  EXPECT_THAT(sut.size(), Eq(10));
}

