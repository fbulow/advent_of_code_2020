#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <vector>
#include "read_input.hh"
#include "row.hh"
#include "navigator.hh"

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
};


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
    Row sut("Valve AA has flow rate=0; tunnels lead to valves DD, II, BB");
    EXPECT_THAT(sut.from, Eq("AA"));
    EXPECT_THAT(sut.rate, Eq(0));
    EXPECT_THAT(sut.to, Contains("DD"));
    EXPECT_THAT(sut.to, Contains("II"));
    EXPECT_THAT(sut.to, Contains("BB"));
    EXPECT_THAT(sut.to.size(), Eq(3));
  }
  {
    Row sut("Valve HH has flow rate=22; tunnel leads to valve GG");
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

