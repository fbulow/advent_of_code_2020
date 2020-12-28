#include <gtest/gtest.h>
#include "main.cpp"


TEST(Cups, ctor)
{
  Cups sut("12345");
  EXPECT_EQ("12345", sut.toString());
  sut.shiftRight();
  EXPECT_EQ("51234", sut.toString());
  sut.shiftRight(2);
  EXPECT_EQ("34512", sut.toString());

}

TEST(Cups, placePickupLast)
{
  Cups sut("389125467");
  sut.placePickupLast();
  EXPECT_EQ("254673891", sut.toString());
}

TEST(nextDown, cases)
{
  EXPECT_EQ('8', nextDown('9'));
  EXPECT_EQ('7', nextDown('8'));
  EXPECT_EQ('9', nextDown('1'));
}

TEST(destination, cases)
{
  Cups sut("123456789");
  EXPECT_EQ("789", string(sut.stashBeginConst(),
                          sut.stashEndConst()));

  EXPECT_EQ('5', sut.destination());
  EXPECT_EQ('6', sut.beforeStash());
}

TEST(smallShiftRight, cases)
{
  Cups sut("123456789");
  sut.smallShiftLeft();
  EXPECT_EQ("234561789", sut.toString());
}

TEST(smallShiftUntilLastIs, example)
{
  Cups sut("123456789");
  sut.smallShiftUntilLastIs('2');
  EXPECT_EQ("345612789", sut.toString());
}

TEST(makeMove, example)
{
  Cups sut("389125467");
  sut.makeMove();
  EXPECT_EQ("289154673", sut.toString());
}

TEST(solve, a)
{
  auto ans = sovleA("389125467");
  ASSERT_EQ("67384529", ans);
  cout<<"Solution a: " <<ans<<endl;
}

TEST(numeric, size)
{
  ASSERT_LT(10000000, numeric_limits<I>::max());
}

TEST(QuickCup, ctor)
{
  QuickCups sut("12345", 7);
  ostringstream s;
  for(auto x:sut)
    s<<x;
  EXPECT_EQ("1234567", s.str());
  EXPECT_EQ("1 2 3 4 5 6 7", sut.toString());
}

TEST(QuickCup, toString)
{
  QuickCups sut("389125467", 9);
  EXPECT_EQ("3 8 9 1 2 5 4 6 7", sut.toString());
}

TEST(QuickCup, move)
{
  QuickCups sut("389125467", 9);
  sut.move();
  EXPECT_EQ("2 8 9 1 5 4 6 7 3", sut.toString());
}

TEST(QuickCup, shift_until_first_one_is)
{
  QuickCups sut("123456789", 9);
  sut.shiftUntilFirstOneIs(7);

  EXPECT_EQ("7 8 9 1 2 3 4 5 6", sut.toString());
}

