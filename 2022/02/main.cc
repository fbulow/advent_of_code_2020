#include <AoC/getAllLines.hh>
#include <numeric>
#include <algorithm>

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
    :value()
  {}
};


int solA(vector<string> scores)
{
  return accumulate(scores.begin(),
		    scores.end(),
		    0,
		    [](int a,string s){
		      return a+(s.empty()?0:iWon(s) + intrisicValue(s));
		    });
}

string decrypt(string s)
{
  switch(s[2])
    {
    case 'X':
      switch(s[0])
	{
	case 'A':
	  s[2] = 'C';
	  return s;
	case 'B':
	  s[2] = 'A';
	  return s;
	case 'C':
	  s[2] = 'B';
	  return s;
	}
    case 'Y':
      s[2]=s[0];
      return s;
    case 'Z':
      switch(s[0])
	{
	case 'A':
	  s[2] = 'B';
	  return s;
	case 'B':
	  s[2] = 'C';
	  return s;
	case 'C':
	  s[2] = 'A';
	  return s;
	}
      
    }
  return s;
}
int solB(vector<string> s)
{
  transform(s.begin(),
	    s.end(),
	    s.begin(),
	    decrypt);
  return solA(s);
}


#include<gtest/gtest.h>
#include<gmock/gmock.h>

using namespace testing;

TEST(solB, real)
{
  ASSERT_EQ(10560, solB(getAllLines<>()));
}


TEST(solB, example)
{
  istringstream in(R""(A Y
B X
C Z
)"");

  ASSERT_EQ(12, solB(getAllLines<string>(in)));
}

TEST(decrypt, losses)
{
  ASSERT_EQ(0, iWon(decrypt("A X")));
  ASSERT_EQ(0, iWon(decrypt("B X")));
  ASSERT_EQ(0, iWon(decrypt("C X")));
}
TEST(decrypt, draws)
{
  ASSERT_EQ(3, iWon(decrypt("A Y")));
  ASSERT_EQ(3, iWon(decrypt("B Y")));
  ASSERT_EQ(3, iWon(decrypt("C Y")));
}
TEST(decrypt, wins)
{
  ASSERT_EQ(6, iWon(decrypt("A Z")));
  ASSERT_EQ(6, iWon(decrypt("B Z")));
  ASSERT_EQ(6, iWon(decrypt("C Z")));
}


TEST(solA, real)
{
  ASSERT_EQ(9651, solA(getAllLines()));
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

  ASSERT_EQ(15, solA(getAllLines<string>(in)));
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
