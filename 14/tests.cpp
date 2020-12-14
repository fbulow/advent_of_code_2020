#include <gtest/gtest.h>
#include "main.cpp"


TEST(type, size)
{
  Value a{0b100000000000000000000000000001001001};
  Mask m ("XXXXXXXXXXXXXXXXXXXXXXXXXXXXX1XXXX0X");
}
TEST(valueIfOneIs, zero)
{
  Mask sut ( "XXXXXXXXXXXXXXXXXXXXXXXXXXXXX1XXXX0X");
  EXPECT_EQ(0b000000000000000000000000000001000000,
	    sut.valueIfOneIs('1'));
}

TEST(mask, first)
{
  Value v=0b000000000000000000000000000000001011;
  Mask m{"XXXXXXXXXXXXXXXXXXXXXXXXXXXXX1XXXX0X"};
  EXPECT_EQ(0b000000000000000000000000000001001001,
	    m.apply(v));
}

TEST(mask, second)
{
  Value v=101;
  Mask m{"XXXXXXXXXXXXXXXXXXXXXXXXXXXXX1XXXX0X"};
  EXPECT_EQ(101, 
	    m.apply(v));
}

TEST(mask, third)
{
  Value v=0;
  Mask m{"XXXXXXXXXXXXXXXXXXXXXXXXXXXXX1XXXX0X"};
  EXPECT_EQ(64, 
	    m.apply(v));
}

TEST(getIndex, first)
{
  EXPECT_EQ(8, getIndex("mem[8] = 11"));
  EXPECT_EQ(88, getIndex("mem[88] = 11"));
}

TEST(getValue, first)
{
  EXPECT_EQ(11, getValue("mem[8] = 11"));
}


TEST(sovle, a)
{
  ASSERT_EQ(165, solveA(EXAMPLE));
  cout<<"Solution a: "<<solveA(INPUT)<<endl;
}
