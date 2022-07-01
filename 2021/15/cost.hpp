#pragma once
#include<optional>
struct Cost : Board<optional<int>>
{
  Cost(int rows, int cols)
  {
    d.reserve(rows);
    for(int i =0;i<rows;i++)
      d.emplace_back(vector<optional<int>>(cols, nullopt));
  }
  Cost(auto const &b)
    :Cost(b.Nrows(), b.Ncols())
  {
  }
  optional<int> bottomRight() const
  {
    return d.back().back();
  }
  optional<int>& bottomRight() 
  {
    auto &a = d.back();
    return a.back();
  }
  unsigned int hash() const
  {
    unsigned int ret{0};
    for(auto &x : d)
      ret+=accumulate(x.cbegin(), x.cend(), 0, [](auto a, auto &x){return a+x.value_or(10000);});
    return ret;
  }
};

TEST(Cost_, all)
{
  {
    Cost sut(2,3);
    EXPECT_EQ(60000, sut.hash());
    sut[{1,2}]=5;
    EXPECT_EQ(50005, sut.hash());
  }
  
  {
    Cost sut(2,3);
    Coord c{1,2};
    sut[c] = 5;
    EXPECT_EQ(5, sut[c]);
    EXPECT_EQ(5, sut.bottomRight());
  }
  {
    Cost sut(2,3);
    EXPECT_EQ(2, sut.Nrows());
    EXPECT_EQ(3, sut.Ncols());
    EXPECT_EQ(nullopt, sut[Coord(1,1)]);
  }

  {
    Cost sut(3,3);
    EXPECT_EQ(4, sut.adjacent(Coord(1,1)).size());
    EXPECT_EQ(2, sut.adjacent(Coord(0,0)).size());
    EXPECT_EQ(2, sut.adjacent(Coord(2,0)).size());
    EXPECT_EQ(2, sut.adjacent(Coord(0,2)).size());
    EXPECT_EQ(2, sut.adjacent(Coord(2,2)).size());

    EXPECT_EQ(3, sut.adjacent(Coord(0,1)).size());
    EXPECT_EQ(3, sut.adjacent(Coord(1,0)).size());
    EXPECT_EQ(3, sut.adjacent(Coord(2,1)).size());
    EXPECT_EQ(3, sut.adjacent(Coord(1,2)).size());
  }
}
