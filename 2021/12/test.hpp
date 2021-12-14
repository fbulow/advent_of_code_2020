#include "solution.hpp"
#include <gtest/gtest.h>

TEST(Topology, add)
{
  Topology sut;
  sut<<"GW-start";
  ASSERT_TRUE(sut["GW"].contains("start"));
  ASSERT_TRUE(sut["start"].contains("GW"));
  ASSERT_FALSE(sut["start"].contains("q"));
  sut<<"start-q";
  ASSERT_TRUE(sut["start"].contains("q"));
}

TEST(isSmall, both)
{
  ASSERT_FALSE(isSmall("GW"));
  ASSERT_TRUE(isSmall("cd"));
}

TEST(Path, both)
{
  auto sut = Path()+"hello";
  ASSERT_EQ( "hello", sut.location());
  ASSERT_FALSE( sut.contains("foo"));
  ASSERT_TRUE( sut.contains("hello"));
}

Data small()
{
  return {
    "start-A",
    "start-b",
    "A-c",
    "A-b",
    "b-d",
    "A-end",
    "b-end"};
}

TEST(travel, small)
{
  Topology topology;
  for(auto s:small())
    topology<<s;
  ASSERT_EQ(10, travel(topology, Path(), "start"));
}
