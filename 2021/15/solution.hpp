#pragma once
#include<iostream>
#include<fstream>
#include<functional>
#include<numeric>
#include<algorithm>
#include<optional>
#include<cassert>
#include<memory>
#include"strong_type.hpp"
#include<set>
#include<map>

#include"board.hpp"
#include"cavern.hpp"
#include"cost.hpp"

using namespace std;

bool onBoard(Coord const& ij, int const& Nrows, int const& Ncolumns)
{
  return (ij.row >=0)
    and  (ij.col >=0)
    and  (ij.row < Nrows)
    and  (ij.col < Ncolumns);
}

TEST(onBoard, all)
{
  EXPECT_FALSE(onBoard({-1, 0}, 10, 11));
  EXPECT_FALSE(onBoard({ 0,-1}, 10, 11));
  EXPECT_FALSE(onBoard({-1,-1}, 10, 11));
  EXPECT_FALSE(onBoard({-1,-1}, 10, 11));

  EXPECT_FALSE(onBoard({0,11}, 10, 11));
  EXPECT_FALSE(onBoard({10,0}, 10, 11));

  EXPECT_TRUE(onBoard({0,10}, 10, 11));
  EXPECT_TRUE(onBoard({9,0}, 10, 11));
  EXPECT_TRUE(onBoard({0,1}, 10, 11));
}


vector<Coord> iter_order(int N)
{
  vector<Coord> ret;
  ret.reserve(N*N-2);
  for(int n=1;n<(2*N);n++)
    {
      for (int row = 0; row<=n; row++)
        {
          Coord c{row, n-row};
          if(onBoard(c, N,N) and c!=Coord(0,0))
            ret.push_back(c);
        }
    }
  return ret;
}

TEST(iter_order_, all)
{
  EXPECT_EQ(3, iter_order(2).size());
  EXPECT_EQ(8, iter_order(3).size());
}

vector<Coord> iter_order(int Nrows, int Ncolumns)
{
  assert(Nrows == Ncolumns);
  return iter_order(Nrows);
}

  
vector<Coord> iter_order(Board<auto> const &b)
{
  return iter_order(b.Nrows(), b.Ncols());
}


int shortest_to(Coord ij, Cost const &cost)
{
  auto ret = optional<int>{};
  for (Coord c: cost.adjacent(ij))
    {
      auto v = cost[c];// Only care about the value..
      if(v)
        ret = min( v.value(),
                   ret.value_or(v.value()) );
    }
  return ret.value();
}

auto travel_south_east(Cavern const &cav,  Cost & c)
{
  c[{0,0}] = 0;
  auto const io = iter_order(c);
  for (Coord const &x: io)
      c[x] = shortest_to(x, c) + cav[x];
      
  return c.hash();
}

TEST(example, solve)
{
  auto cav = example();
  Cost sut(cav);
  cout << travel_south_east(cav,  sut)<<endl;
  cout << travel_south_east(cav,  sut)<<endl;
  cout << travel_south_east(cav,  sut)<<endl;
}
