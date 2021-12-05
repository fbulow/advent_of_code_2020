#include <gtest/gtest.h>
#include "solution.cpp"


TEST(input, Point)
{
  istringstream in("527,299");
  Point sut;
  in>>sut;
      
  EXPECT_EQ(527, get<Row>(sut)());
  EXPECT_EQ(299, get<Column>(sut)());
}

TEST(input, Line)
{
  istringstream in("527,299 -> 430,300");
  Line sut;
  in>>sut;
      
  EXPECT_EQ(527, get<Row>(sut.start)());
  EXPECT_EQ(299, get<Column>(sut.start)());

  EXPECT_EQ(430, get<Row>(sut.end)());
  EXPECT_EQ(300, get<Column>(sut.end)());
}


TEST(Line, two_dots)
{
  istringstream in("0,0 -> 1,0");
  Line sut;
  in>>sut;
  set<Point> outp;
  
  sut.draw([&outp](auto &x){
    outp.insert(x);
  });

  ASSERT_EQ(2, outp.size());
}

TEST(Line, three_dots)
{
  istringstream in("0,0 -> 2,0");
  Line sut;
  in>>sut;
  set<Point> outp;
  
  sut.draw([&outp](auto &x){
    outp.insert(x);
  });

  ASSERT_EQ(3, outp.size());
}
