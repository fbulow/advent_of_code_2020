#include <AoC/getAllLines.hh>

using namespace std;

enum class Hand{Rock, Paper, Scissors};


Hand hand(char h)
{
  switch(h)
    {
    case 'A':return Hand::Rock;	   
    case 'B':return Hand::Paper;   
    case 'C':return Hand::Scissors;
    case 'X':return Hand::Rock;	   
    case 'Y':return Hand::Paper;   
    case 'Z':return Hand::Scissors;
    }
  assert(false);
}

int iWon(Hand opponent, Hand me)
{
  if(me==opponent) return 3;

  if(me==Hand::Rock      and opponent==Hand::Scissors) return 6;
  if(me==Hand::Paper     and opponent==Hand::Rock    ) return 6;
  if(me==Hand::Scissors  and opponent==Hand::Paper   ) return 6;

  return 0;
}

int iWon(string s)
{
  return iWon(hand(s[0]), hand(s[2]));
}

#include<gtest/gtest.h>
#include<gmock/gmock.h>

using namespace testing;


TEST(iWon, examples)
{

  // In the first round, your opponent will choose Rock (A), and you
  // should choose Paper (Y). This ends in a win for you with a score of
  // 8 (2 because you chose Paper + 6 because you won).
  ASSERT_EQ(6, iWon("A Y"));
    
  // In the second round, your opponent will choose Paper (B), and you
  // should choose Rock (X). This ends in a loss for you with a score of
  // 1 (1 + 0).
  ASSERT_EQ(0, iWon("B X"));

  // The third round is a draw with both players choosing Scissors, giving you a score of 3 + 3 = 6.
  ASSERT_EQ(3, iWon("C Z"));
}

TEST(input, input_data_is_not_empty)
{
  ASSERT_THAT(getAllLines().size(), Gt(0));
}
