#include "input.hh"
#include <sstream>
Data Input::example()
{
  return
    {{1, 1},
     {1, 6},
     {8, 3},
     {3, 4},
     {5, 5},
     {8, 9}};
}

int minRow(Data const &d){
  return min_element(d.begin(),
		     d.end(),
		     [](auto const &a, auto const &b){
		       return a.first < b.first;})->first;}

int minCol(Data const &d){
  return min_element(d.begin(),
		     d.end(),
		     [](auto const &a, auto const &b){
		       return a.second < b.second;})->second;}

int maxRow(Data const &d){
  return max_element(d.begin(),
		     d.end(),
		     [](auto const &a, auto const &b){
		       return a.first < b.first;})->first;}

int maxCol(Data const &d){
  return max_element(d.begin(),
		     d.end(),
		     [](auto const &a, auto const &b){
		       return a.second < b.second;})->second;}

void normalize(Data &d)
{
  auto rowMin = minRow(d);
  auto colMin = minRow(d);
  for(auto& x: d)
    {
      x.first  -= rowMin;
      x.second -= colMin;
    }
}


#include<gtest/gtest.h>
#include<gmock/gmock.h>
using namespace testing;

TEST(normalize, data)
{
  Data d{{1,1}, {2,2}};
  normalize(d);
  
  EXPECT_THAT(d[0], Eq(Coord(0,0)));
  EXPECT_THAT(d[1], Eq(Coord(1,1)));
}


TEST(minRow, data)
{
  Data d{{1,1}, {2,2}};
  
  EXPECT_THAT(minRow(d), Eq(1));
}

TEST(minRow, data_negative)
{
  Data d{{-5,1}, {-7,2}};
  
  EXPECT_THAT(minRow(d), Eq(-7));
}

TEST(minCol, data)
{
  Data d{{1,1}, {2,2}};
  
  EXPECT_THAT(minCol(d), Eq(1));
}

TEST(example, values)
{
  EXPECT_THAT(*Input::example().begin(),
	      Eq(Coord{1,1}));
  EXPECT_THAT(*Input::example().rbegin(),
	      Eq(Coord{8,9}));
}
