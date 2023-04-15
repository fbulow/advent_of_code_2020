#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <vector>
#include "read_input.hh"
#include "row.hh"
#include <ranges>
#include <algorithm>

using namespace testing;
using namespace std;

using Valve = string;
using Destinations = vector<Valve>;

class Navigator{
  Destinations destinations_;
public:
  Navigator(Destinations destinations)
    :destinations_(move(destinations))
  {}
  Destinations const & getDestinations() const
  {return destinations_;}
  Navigator goTo(Valve v) const
  {
    return Navigator(
		     [this, v] //Evaluated immediately!
		     {
		       assert( ! destinations_.empty() );
		       Destinations ret;
		       ret.reserve(destinations_.size()-1);
		       ranges::copy_if(destinations_, back_inserter(ret), [v](auto x){return x!=v;});
		       return ret;
		     }());

  }
};

TEST(Navigator, ctor)
{
  Navigator sut({"AA", "BB"});
  EXPECT_THAT(sut.getDestinations(),
	      ElementsAre("AA","BB"));

  EXPECT_THAT(sut.goTo("AA").getDestinations(),
	      ElementsAre("BB"));
}

TEST(Navigator, destination_removed_when_goto_is_reached)
{
  
  EXPECT_THAT(
	      Navigator({"AA", "BB"}).goTo("AA").getDestinations(),
	      ElementsAre("BB")
	      );
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

