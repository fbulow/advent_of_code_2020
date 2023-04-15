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
  struct Navigator : public Mother<::Navigator, Destinations, Valve>
  {
    Navigator()
      :Parent(Destinations{}, Valve(""))
    {}
  };
};

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
  Navigator sut({"BB", "CC"}, "AA");
  EXPECT_THAT(sut.getDestinations(),
	      ElementsAre("BB","CC"));
  EXPECT_THAT(sut.getLocation(),
	      Eq("AA"));
  
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

