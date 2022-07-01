#pragma once
#include"board.hpp"
#include"input.hpp"
struct Cavern : Board<int>
{
  Cavern(int N)
  {
    d.reserve(N);
    for(auto i =0; i<N; i++)
      d.emplace_back(vector<int>(N, 0));
  }
  
  Cavern(vector<string> const &vs)
  {
    d.reserve(100);
    for(auto const &s: vs)
      {
        d.emplace_back([s]
                   {
                     vector<int> ret;
                     ret.resize(s.size());
                     transform(s.begin(),
                               s.end(),
                               ret.begin(),
                               [](auto c)->int {
                                 assert(c>='0');
                                 assert(c<='9');
                                 return c-'0';
                               });
                     return ret;
                   }());
      }     
  }
};

int bump(int val, int bumps)
{
  return 1+(val+bumps-1)%9;
}
TEST(bump_, all)
{
  EXPECT_EQ(2, bump(1,1));
  EXPECT_EQ(4, bump(1,3));
  EXPECT_EQ(1, bump(1,9));
}


Cavern five(Cavern const &cav)
{
  assert(cav.Ncols() == cav.Nrows());
  auto n = cav.Ncols();
  Cavern ret(5*cav.Ncols());
  auto const N = 5*n;

  for(auto r =0; r< N; r++)
    for(auto c =0; c< N; c++)
      ret[{r,c}] = bump( cav[{r%n, c%n}], r/n + c/n );
  return ret;
}

Cavern example();
Cavern input(istream& cin);
TEST(Cavern_, all)
{
  {
    auto sut = five(example())[{49,49}];
    EXPECT_EQ(9, sut);
  }
  {
    Cavern sut({
        "1163751742",
        "1381373672",
        "2136511328",
        "3694931569",
        "7463417111",
        "1319128137",
        "1359912421",
        "3125421639",
        "1293138521",
        "2311944581"});

    EXPECT_EQ(10, sut.Nrows());
    EXPECT_EQ(10, sut.Ncols());

    EXPECT_EQ(1, sut[Coord(0,0)]);
    EXPECT_EQ(3, sut[Coord(1,1)]);
    EXPECT_EQ(6, sut[Coord(0,2)]);
    EXPECT_EQ(8, sut[Coord(9,8)]);

    auto ssut = five(sut);

    EXPECT_EQ(2, ssut[Coord(10,0)]);
    EXPECT_EQ(3, ssut[Coord(10,11)]);
    EXPECT_EQ(4, ssut[Coord(10,21)]);

  }

  {
    Cavern sut(4);
    EXPECT_EQ(4, sut.Nrows());
    EXPECT_EQ(4, sut.Ncols());
  }
}
