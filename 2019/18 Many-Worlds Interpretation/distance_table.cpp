#include "distance_table.hpp"
#include <gtest/gtest.h>


using Steps = DistanceTable::Steps;

void DistanceTable::add_distance(char from, char to, Steps distance)
{
  data.push_back({from, to, distance});
}

Steps DistanceTable :: get_distance( char from, char to )
{
  return find_if(data.begin(), data.end(),
                 [from, to](Distance const &d)
                 {
                   return ( (d.from == min(from,to)) and 
                            (d.to == max(from,to)) );
                 })->steps;
}

TEST(ctor, no_arg)
{
  DistanceTable sut;
}

TEST(DistanceTable, add_distance)
{
  DistanceTable sut;

  sut.add_distance('a', 'b', 10);

  EXPECT_EQ(10, sut.get_distance('a', 'b'));
  EXPECT_EQ(10, sut.get_distance('b', 'a'));

  sut.add_distance('a', 'c', 5);
  EXPECT_EQ(5, sut.get_distance('a', 'c'));

}


TEST(DistanceTable, defaults_to_zero)
{
  DistanceTable sut;
  EXPECT_EQ(0, sut.get_distance('q', 'c'));
}
