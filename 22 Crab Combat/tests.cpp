#include <gtest/gtest.h>
#include "main.cpp"


TEST(example, card)
{
  Game sut("example");
  {
    list<I> refOne{9, 2, 6, 3, 1};
    list<I> refTwo{5, 8, 4, 7, 10};
    
    EXPECT_EQ(refOne,
              sut.one);
    EXPECT_EQ(refTwo,
              sut.two);
  }
            
  sut.playRound();
  
  {
    list<I> refOne{2, 6, 3, 1, 9, 5};
    list<I> refTwo{8, 4, 7, 10};
    
    EXPECT_EQ(refOne,
              sut.one);
    EXPECT_EQ(refTwo,
              sut.two);
  }

  sut.finnish();
  {
    list<I> refOne{};
    list<I> refTwo{3, 2, 10, 6, 8, 5, 9, 4, 7, 1};
    
    EXPECT_EQ(refOne,
              sut.one);
    EXPECT_EQ(refTwo,
              sut.two);
  }

  EXPECT_EQ(306,
            sut.score());
  
}

TEST(solve, a)
{
  ASSERT_EQ(306,
            solutionA(EXAMPLE));
  cout<<"Solution a: "<<solutionA(INPUT)<<endl;
}

TEST(Game, hash)
{
  EXPECT_NE(
            Game(EXAMPLE).hash(),
            Game().hash()
            );
  EXPECT_EQ(
            Game().hash(),
            Game().hash()
            );
}
