#include <AoC/getAllLines.hh>
#include <numeric>

using namespace std;


using Hand = char;

constexpr char Rock	= 'A';
constexpr char Paper	= 'B';
constexpr char Scissors	= 'C';


Hand hand(char h)
{
  switch(h)
    {
    case 'A':return Rock;	   
    case 'B':return Paper;   
    case 'C':return Scissors;
    case 'X':return Rock;	   
    case 'Y':return Paper;   
    case 'Z':return Scissors;
    }
  assert(false);
}

int intrisicValue(Hand h)
{
  //...for the shape you selected (1 for Rock, 2 for Paper, and 3 for Scissors)
  switch(h)
    {
    case Rock:	 return 1;
    case Paper:	 return 2;
    case Scissors: return 3;
    }
  assert(false);
}

int intrisicValue(string const &s)
{
  return intrisicValue(hand(s[2]));
}


int iWon(Hand opponent, Hand me)
{
  auto val = (opponent-me+3)%3;
  switch(val)
    {
    case 2: return 6;
    case 0: return 3;
    case 1: return 0;
    }
  assert(false);
}

int iWon(string s)
{
  return iWon(hand(s[0]), hand(s[2]));
}

struct Score{
  int value;
  Score(string s)
    :value(s.empty()?0:iWon(s) + intrisicValue(s))
  {}
};


int solA(vector<Score> const && scores)
{
  return accumulate(scores.begin(),
		    scores.end(),
		    0,
		    [](int a,Score s){return s.value+a;});
}


#include<gtest/gtest.h>
#include<gmock/gmock.h>

using namespace testing;


TEST(solA, real)
{
  ASSERT_EQ(9651, solA(getAllLines<Score>()));
}

TEST(Score, empty_string_value_zero)
{
  ASSERT_EQ(0, Score("").value);
}

TEST(solA, example)
{
  istringstream in(R""(A Y
B X
C Z
)"");

  ASSERT_EQ(15, solA(getAllLines<Score>(in)));
}

TEST(intrisicValue, example)
{
  // In the first round, your opponent will choose Rock (A), and you
  // should choose Paper (Y). This ends in a win for you with a score of
  // 8 (2 because you chose Paper + 6 because you won).
  ASSERT_EQ(2, intrisicValue("A Y"));
}



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
