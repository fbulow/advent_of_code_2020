#include "solution.hpp"
#include <gtest/gtest.h>

TEST(Row, read)
{
  istringstream in("acedgfb cdfbe gcdfa fbcad dab cefabd cdfgeb eafb cagedb ab | cdfeb fcadb cdfeb cdbaf");
  Row sut(in);

  EXPECT_EQ(Signal("acedgfb"), Signal("abcdefg")), 
  
  cout<<sut.all[0]<<endl;
  EXPECT_EQ(Signal("acedgfb"), sut.all[0]);
  EXPECT_EQ(Signal("ab"), sut.all[9]);
  EXPECT_EQ(Signal("cdfeb"), sut.rhs[0]);
  EXPECT_EQ(Signal("cdbaf"), sut.rhs[3]);
}

TEST(Row, read_input)
{
  //  ifstream in(INPUT);
  
  //  auto d = input(cin);
  //  ASSERT_EQ(Signal("abecgd"), prev(d.end())->rhs[3]);
}

TEST(Led, sorted)
{
  Led sut("acb");
  ASSERT_EQ("abc", sut.data());
}

TEST(Led, equal)
{
  ASSERT_EQ(Led("abc"), Led("cba"));
  ASSERT_NE(Led("ab"), Led("cba"));
}

TEST(Led, transform)
{
  Led x("abc") ;
  ASSERT_EQ(Led("abc"), Wiring("abcdefg")[Signal("abc")]);
  ASSERT_EQ(Led("efg"), Wiring("gfedcab")[Signal("abc")]);

}

TEST(Led, value)
{
  EXPECT_EQ(5, Led("abdfg").visual()) ;
  EXPECT_EQ(nullopt, Led("a").visual()) ;
}
