#include <gtest/gtest.h>
#include "dice.hh"
#include "player.hh"
#include <algorithm>

using namespace std;


unsigned int solutionA(Player a,
                       Player b)
{
  Dice d;
  while(true)
    {
      if(0 == (d.count()%2))
        {
          a.move(d.rollTrice());
          if(a.score() >=1000)
            return b.score()*d.count();
        }
      else
        {
          b.move(d.rollTrice());
          if(b.score() >=1000)
            return a.score()*d.count();
        }
    }  

}

TEST(solution, a)
{
  EXPECT_EQ(739785,
            solutionA(4,8));
  EXPECT_EQ(605070,
            solutionA(8,10));
  
}



// class Game{
//   Dice &d;
//   int PosA;
//   int PosB;
// public:
//   //  Game(Dice &d, int PosA, int PosB) = default();

//   long int evaluate() const;
// };


// TEST(Game, evaluate_example)
// {
//   Dice d(94, 993);
//   EXPECT_EQ(Game(d, 10, 3)
// }
