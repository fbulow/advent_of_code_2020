#include "distance_table.hpp"
#include <gtest/gtest.h>
#include <iterator>

using Steps = DistanceTable::Steps;

DistanceTable::Nodes DistanceTable::get_nodes(char c) const
{
  Nodes ret;
  for(Distance const &x:data)
    {
      if(x.from == c)
        ret.push_back({x.to, x.steps});
      if(x.to == c)
        ret.push_back({x.from, x.steps});
    }
  return ret;
}



TEST(nodes, none)
{
  DistanceTable sut;
  ASSERT_EQ(0, sut.get_nodes('a').size());
}
TEST(Nodes, get_two)
{
  DistanceTable sut;

  sut.add_distance('a', 'b', 10);
  sut.add_distance('a', 'c', 5);

  EXPECT_EQ(2, sut.get_nodes('a').size());
  EXPECT_EQ(1, sut.get_nodes('b').size());
  EXPECT_EQ(1, sut.get_nodes('c').size());
}

void DistanceTable::remove(char c)
{
  auto n = get_nodes(c);
  for(auto b = n.begin(); b!= n.end(); advance(b,1))
    for(auto c = next(b); c!= n.end(); advance(c,1))
      add_distance(get<char>(*b), get<char>(*c), get<Steps>(*b)+get<Steps>(*c));
  
  // static vector<Distance> = data;
  // data.resize(0);
  // auto beg=data.begin();
  // while(beg!=data.end());
  // auto ret = find_if(beg, data.end(),
  //                    [from, to](Distance const &d)
  //                    {
  //                      return ( (d.from == min(from,to)) and 
  //                               (d.to == max(from,to)) );
  //                    });
  
}


void DistanceTable::add_distance(Distance d)
{
  auto it = find_if(data.begin(),
                    data.end(),
                    [d](Distance &x){
                      return (d.from==x.from) and (d.to==x.to);
                    });
  if(it == data.end())
    data.emplace_front(move(d));
  else
    it->steps = min(it->steps, d.steps);
}
void DistanceTable::add_distance(char from, char to, Steps distance)
{
  add_distance({ from, to, distance });
}

TEST(add_distance, keep_the_shortest)
{
  {
    DistanceTable sut;
    sut.add_distance('a', 'b', 1);
    sut.add_distance('a', 'b', 2);
    EXPECT_EQ(1, sut.get_distance('a','b'));
  }
  {
    DistanceTable sut;
    sut.add_distance('a', 'b', 2);
    sut.add_distance('a', 'b', 1);
    EXPECT_EQ(1, sut.get_distance('a','b'));
  }
}

Steps DistanceTable :: get_distance( char from, char to )
{
  auto ret = find_if(data.begin(), data.end(),
                 [from, to](Distance const &d)
                 {
                   return ( (d.from == min(from,to)) and 
                            (d.to == max(from,to)) );
                 });
  if(ret == data.end()) return 0;
  else
    return ret->steps;
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

TEST(DistanceTable, remove_destination)
{
  DistanceTable sut;

  sut.add_distance('a', 'b', 10);
  sut.add_distance('a', 'c', 5);
  sut.remove('a');

  EXPECT_EQ(15, sut.get_distance('b', 'c'));
}


TEST(DistanceTable, defaults_to_zero)
{
  DistanceTable sut;
  EXPECT_EQ(0, sut.get_distance('q', 'c'));
}
