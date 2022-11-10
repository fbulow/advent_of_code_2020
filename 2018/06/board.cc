#include "board.hh"

Box::Box(vector<Coord> const & v)
{
  auto rows = v|views::transform([](auto const &x)->int {return x.row();});
  row.max = *max_element(rows.begin(),rows.end());
  row.min = *min_element(rows.begin(),rows.end());

  auto cols = v|views::transform([](auto const &x)->int {return x.col();});
  col.max = *max_element(cols.begin(),cols.end());
  col.min = *min_element(cols.begin(),cols.end());
}

bool Board::thereAreUnknowns() const
{
  auto rowDoesNotContainFree =
    [](vector<int> const &row) -> bool
    {
      return ranges::any_of(row, [](int x){return x==free;});
    };
  return ranges::any_of(data_, rowDoesNotContainFree);
}  

Board::Board(Box const & box, Coords const &points)
{
  data_.reserve(box.height());
  for(int i=box.row.min; i<=box.row.max; i++)
    data_.emplace_back(vector<int>(box.width(), free));
  for(int i=0;i<points.size(); i++)
    {
      auto p = points[i];
      set(p.row()-box.row.min,
	  p.col()-box.col.min, i);
    }
}

Board::Board(Coords const &points)
  :Board(Box(points), points)
{}

void Board::set(int row, int col, int value)
{data_[row][col] = value;}

int Board::get(int row, int col) const
{return data_[row][col];}


#include<gtest/gtest.h>
#include<gmock/gmock.h>
using namespace testing;

//TEST(Board, get_outside_board_is_always_free)
//TEST(newValue, border)
//TEST(newValue, already_known)
//TEST(newValue, assign_value)



TEST(Board, thereAreUnknowns_true)
{
  Board sut(Coords({Coord{1,0},Coord{0,1}}));
  EXPECT_TRUE(sut.thereAreUnknowns());
}

TEST(Board, thereAreUnknowns_false)
{
  Board sut(Coords({Coord{1,0},Coord{0,0}}));
  EXPECT_FALSE(sut.thereAreUnknowns());
}


TEST(Box, ctor)
{
  vector<Coord> data{{0,0}};
  auto sut = Box(data);
  EXPECT_THAT(sut.row.min, Eq(0));
  EXPECT_THAT(sut.row.max, Eq(0));
  EXPECT_THAT(sut.col.min, Eq(0));
  EXPECT_THAT(sut.col.max, Eq(0));
}

TEST(Box, ctor_two_points)
{
  vector<Coord> data{{1,5}, {3,2}};
  auto sut = Box(data);
  EXPECT_THAT(sut.row.min, Eq(1));
  EXPECT_THAT(sut.row.max, Eq(3));
  EXPECT_THAT(sut.col.min, Eq(2));
  EXPECT_THAT(sut.col.max, Eq(5));
}

TEST(Box, height)
{
  vector<Coord> data{{0,0}, {1,0}};
  auto sut = Box(data);
  EXPECT_THAT(sut.height(), Eq(2));
}

TEST(Board, ctor)
{
  vector<Coord> points{{1,5}, {3,2}};
  auto sut = Board(Box(points), points);

  EXPECT_THAT(sut.get(0,0), Eq(Board::free));
  EXPECT_THAT(sut.get(0,3), Eq(0));
  EXPECT_THAT(sut.get(2,0), Eq(1));
}

