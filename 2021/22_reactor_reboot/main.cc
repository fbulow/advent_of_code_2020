#include <gtest/gtest.h>
#include<algorithm>
#include<fstream>
#include"cube.hh"
#include"instruction.hh"
#include"space.hh"
#include<list>

#include"square_space.hh"
using namespace std;

TEST(Range, split__no_split)
{
  {
    auto sut = Range{1,9}.splitBy(Range(0,10));
    EXPECT_EQ(1, sut.size());
    EXPECT_TRUE(sut.contains(Range{1,9}));
  }
  {
    auto sut = Range{1,9}.splitBy(Range(2,10));
    EXPECT_EQ(2, sut.size());
    EXPECT_TRUE(sut.contains(Range{1,1}));
    EXPECT_TRUE(sut.contains(Range{2,9}));
  }
  {
    auto sut = Range{1,9}.splitBy(Range(0,8));
    EXPECT_EQ(2, sut.size());
    EXPECT_TRUE(sut.contains(Range{1,8}));
    EXPECT_TRUE(sut.contains(Range{9,9}));

  }
  {
    auto sut = Range{1,9}.splitBy(Range(2,8));
    EXPECT_EQ(3, sut.size());
    EXPECT_TRUE(sut.contains(Range{1,1}));
    EXPECT_TRUE(sut.contains(Range{2,8}));
    EXPECT_TRUE(sut.contains(Range{9,9}));
    
  }

}

