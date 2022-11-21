#include "board.hh"
#include <ranges>
#include <set>
#include <algorithm>
#include <cassert>
#include <iostream>
#include "char_convert.hh"

ostream& operator<<(ostream& out, BoardAsVectors const &b)
{
  for(auto row: b)
    {
      for(auto c : row)
	out<<toVisibleChar(c)<<' ';
      out<<endl;
    }
  return out;
}

ostream& operator<<(ostream& out, Board const &b)
{
  return (out<<b.data);
}
set<int> Board::infiniteRegions()
{
  set<int> ret;
  for(auto const &x: data[0])
    ret.insert(x);
  for(auto const &x: *data.rbegin())
    ret.insert(x);

  for(auto const &x:data)
    {
      ret.insert(x[0]);
      ret.insert(*x.rbegin());
    }
	  
  return ret;
}

int Board::sizeOfLargestFiniteRegion()
{

  auto rs = regionSizes();
  auto ir = infiniteRegions();

  auto finteRegionSizes =
    ranges::iota_view{0, int(rs.size())}
    |ranges::views::filter([ir = set(ir.begin(), ir.end())](auto rowNr ){return not ir.contains(rowNr);})
    |ranges::views::transform([rs](auto rowNr){return rs[rowNr];});

  for(auto x: finteRegionSizes)
    cout<<x<<" ";
  cout<<endl;
  
  
  auto ret = max_element(finteRegionSizes.begin(), finteRegionSizes.end());
  assert (ret!=finteRegionSizes.end());
  auto r = *ret;
  return r;
}




Board::Board(BoardAsVectors &&data)
  :data(move(data))
{}
Board::Board(Data d)
{
  normalize(d);
  data = BoardAsVectors(maxRow(d)+1);
  auto const Ncol = maxCol(d)+1;
  int color=1;
  for(auto &row: data)
      row = vector<int>(Ncol);
  for(auto [row, col] : d)
    data[row][col]=color++;
}



#include<gtest/gtest.h>
#include<gmock/gmock.h>
#include"input.hh"
using namespace testing;

TEST(BoardAsVectors, ctor)
{
  BoardAsVectors sut({
      "a . .",
      ". . .",
      ". . b"
    });  
  ostringstream s;
  s<<sut;
  ASSERT_THAT(s.str(), Eq("a . . \n . . . \n . . b\n "));
  
}

// TEST(Board, fill)
// {
//   // a . .
//   // . . .
//   // . . b  
//   Board sut({pair(0,0), pair(2,2)});
//   auto ans = sut.fill();
//   ASSERT_THAT(ans.get(1,0), Eq(1));
//   ASSERT_THAT(ans.get(0,1), Eq(1));
//   ASSERT_THAT(ans.get(1,1), Eq(0));
// }

TEST(Board, data_ctor)
{
  Board sut(Data({pair(0,0)}));
  ASSERT_THAT(sut.nRows(), Eq(1));
  ASSERT_THAT(sut.nCols(), Eq(1));
  ASSERT_THAT(sut.get(0,0), Eq(1));
}
TEST(Board, data_ctor_four_squares)
{
  Board sut(Data({pair(0,0), pair(1,1)}));
  ASSERT_THAT(sut.get(0,0), Eq(1));
  ASSERT_THAT(sut.get(1,1), Eq(2));
  ASSERT_THAT(sut.get(0,1), Eq(0));
}



TEST(Board, infiniteRegions_are_border_regions)
{
  Board sut(vector<vector<int>>{
      {1,2,3},
      {4,0,5},
      {6,7,8}});
  ASSERT_THAT(sut.infiniteRegions(), AllOf(Contains(1)
					   ,Contains(2)
					   ,Contains(3)
					   ,Contains(4)
					   ,Contains(5)
					   ,Contains(6)
					   ,Contains(7)
					   ,Contains(8)));
}



TEST(Board, ctor_BoardAsVectors)
{
  Board sut(BoardAsVectors({
      {0,0,0},
      {0,1,0},
      {0,2,0}}));
  ASSERT_THAT(sut.get(1,1), Eq(1));
  ASSERT_THAT(sut.get(2,1), Eq(2));
  ASSERT_THAT(sut.get(0,2), Eq(0));
}



TEST(Board, check_infinites_in_example)
{
  auto sut = Board(
      "aaaaa.cccc",
      "aaaaa.cccc",
      "aaaddecccc",
      "aadddecccc",
      "..dddeeccc",
      "bb.deeeecc",
      "bbb.eeee..",
      "bbb.eeefff",
      "bbb.eeffff",
      "bbb.ffffff")
    .infiniteRegions();

   
  ASSERT_THAT(sut,
	      AllOf(Contains(fromVisibleChar('a')),
		    Contains(fromVisibleChar('b')),
		    Contains(fromVisibleChar('c')),
		    Contains(fromVisibleChar('f'))));
}
     
TEST(char, dot_is_zero)
{
  ASSERT_THAT(int('.'), Eq(0));
  ASSERT_THAT(int('a'), Eq(1));
}
