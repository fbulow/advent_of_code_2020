#include <gtest/gtest.h>
#include "main.cpp"
#include "gmock/gmock.h"

TEST(example, card)
{
  Game sut(EXAMPLE);
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
  auto const ans = solutionA(INPUT);
  EXPECT_EQ(1958, ans);
  cout<<"Solution a: "<<ans<<endl;
}

TEST(Recursive, hash)
{
  EXPECT_NE(
            Recursive(EXAMPLE).hash(),
            Recursive().hash()
            );
  EXPECT_EQ(
            Recursive().hash(),
            Recursive().hash()
            );
}

TEST(Recursive, determine_by_sub_game)
{
// -- Round 9 (Game 1) --
// Player 1's deck: 4, 9, 8, 5, 2
// Player 2's deck: 3, 10, 1, 7, 6
// Player 1 plays: 4
// Player 2 plays: 3
// Playing a sub-game to determine the winner...
//

  
  auto sut = Recursive(list<I>{4, 9, 8, 5, 2},
                       list<I>{3, 10, 1, 7, 6}).recursive();

  EXPECT_TRUE(sut);

// === Game 2 ===
// 
// -- Round 1 (Game 2) --
// Player 1's deck: 9, 8, 5, 2
// Player 2's deck: 10, 1, 7  

  Recursive const ref(list<I>{9, 8, 5, 2},
                      list<I>{10, 1, 7});
  EXPECT_EQ(ref, sut.value());
  
}

TEST(Recursive, do_not_determine_by_sub_game)
{
// -- Round 1 --
// Player 1's deck: 9, 2, 6, 3, 1
// Player 2's deck: 5, 8, 4, 7, 10
// Player 1 plays: 9
// Player 2 plays: 5
// Player 1 wins the round!
  
  EXPECT_FALSE(Recursive(list<I>{9, 2, 6, 3, 1},
                         list<I>{5, 8, 4, 7, 10}).recursive());

}

TEST(Recursive, canPlayRecursive)
{
  EXPECT_FALSE(Recursive::canPlayRecursive({2, 4}));
  EXPECT_TRUE(Recursive::canPlayRecursive({2, 4, 5}));

}


TEST(Recursive, winner)
{
  {
    Recursive sut(list<I>{},
                  list<I>{5, 8, 4, 7, 10});
    EXPECT_EQ(2, sut.winner());
  }
  {
    Recursive sut(list<I>{5, 8, 4, 7, 10},
                  list<I>{});
    EXPECT_EQ(1, sut.winner());
  }
  {
    Recursive sut(list<I>{5, 8},
                  list<I>{4, 7, 10});
    EXPECT_EQ(0, sut.winner()); //No winner yet
  }
  {
    Recursive sut(list<I>{5, 8},
                  list<I>{4, 7, 10});
    EXPECT_EQ(0, sut.winner()); //No winner yet
  }

  {

    // Before either player deals a card, if there was a previous round
    // in this game that had exactly the same cards in the same order
    // in the same players' decks, the game instantly ends in a win for
    // player 1. Previous rounds from other games are not
    // considered. (This prevents infinite games of Recursive Combat,
    // which everyone agrees is a bad idea.)
    
    Recursive sut(list<I>{5, 8},
                  list<I>{4, 7, 10});
    EXPECT_EQ(0, sut.winner()); //No winner yet
    EXPECT_EQ(1, sut.winner()); //No winner yet
  }
}

TEST(solve, b)
{
  ASSERT_EQ(291,
            solutionB(EXAMPLE));
  cout<<"Solution b: "<<solutionB(INPUT)<<endl;
}
