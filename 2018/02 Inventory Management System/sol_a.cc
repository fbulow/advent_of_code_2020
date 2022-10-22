#include<gtest/gtest.h>
#include<gmock/gmock.h>
#include<fstream>
#include"simple_hash.hh"
using namespace testing;

TEST(a, example)
{
  {
    SimpleHash sut("abcdef");
    ASSERT_FALSE(sut.doublet);
    ASSERT_FALSE(sut.triplet);
  }

  {
    SimpleHash sut("bababc");
    ASSERT_TRUE(sut.doublet);
    ASSERT_TRUE(sut.triplet);
  }

  {
    SimpleHash sut("abbcde");
    ASSERT_TRUE(sut.doublet);
    ASSERT_FALSE(sut.triplet);
  }

}

TEST(a, solution)
{
  ifstream in(INPUT);
  string s;

  int doublets{0};
  int triplets{0};
  
  in>>s;
  while(not in.eof())
    {
      SimpleHash x(s);
      if(x.doublet)
	doublets++;
      if(x.triplet)
	triplets++;
      in>>s;
    }

  EXPECT_THAT( doublets*triplets, Eq(6225));
}
