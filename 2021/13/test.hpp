#include "solution.hpp"
#include <gtest/gtest.h>

TEST(get_line_dimmension, all)
{
  ASSERT_EQ(Fold::y, get_line_dimmension("fold along y=7\n"));
  ASSERT_EQ(Fold::x, get_line_dimmension("fold along x=5\n"));
  ASSERT_EQ(Fold::y, get_line_dimmension("fold along y=7"));
  ASSERT_EQ(Fold::x, get_line_dimmension("fold along x=5"));

}

auto example()
{
  return istringstream ("6,10\n"
                        "0,14\n"
                        "9,10\n"
                        "0,3\n"
                        "10,4\n"
                        "4,11\n"
                        "6,0\n"
                        "6,12\n"
                        "4,1\n"
                        "0,13\n"
                        "10,12\n"
                        "3,4\n"
                        "3,0\n"
                        "8,4\n"
                        "1,10\n"
                        "2,14\n"
                        "8,10\n"
                        "9,0\n"
                        "\n"
                        "fold along y=7\n"
                        "fold along x=5\n");
}

TEST(Topology, add)
{
  auto e = example();
  auto sut = input(e);
  ASSERT_EQ(18, sut.dots.size());
  ASSERT_EQ(2,  sut.lines.size());

  ASSERT_TRUE(sut.dots.contains({9,0}));
  
  ASSERT_EQ(7, sut.lines[0].value);
  ASSERT_EQ(5, sut.lines[1].value);
}

TEST(fold, once)
{
  auto e = example();
  auto data = input(e).dots;
  auto sut = fold(data,
                  Line(Fold::y, 7));
  ASSERT_EQ(17, sut.size());
}

TEST(fold, twice)
{
  auto e = example();
  auto data = input(e).dots;
                  
  cout<<fold(
             fold(data,
                  Line(Fold::y, 7)),
             Line(Fold::x, 5));
}
