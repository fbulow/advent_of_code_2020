#include"headers.hh"

char getStack(int stackNr, string const &s);
bool isNumbersRow(string const & row);
string numbersRow(vector<string>(input));

int vectorSize(vector<string> const &input);
int vectorSize(string const &numbersRow);


class State{
  vector<stack<char>> stacks; // Stack zero is never used to match index
  
public:
  State(vector<string> const &input)
  {
    numbersRow(input);
    stacks.resize(vectorSize(numbersRow(input)));
    
    
    // for(auto const & row: input)
      
    
  }
  operator string ()
  {
    return "CMZ"; //TODO
  }
};

string solA(vector<string> const &input)
{
  State state(input);
  
  return state;
}

#include<gtest/gtest.h>
#include<gmock/gmock.h>

using namespace testing;

TEST(getStack, example)
{
  EXPECT_EQ('Z',getStack(1 ,"[Z] [M] [P]"));
  EXPECT_EQ('M',getStack(2 ,"[Z] [M] [P]"));
  EXPECT_EQ('P',getStack(3 ,"[Z] [M] [P]"));
}

TEST(vectorSize, example)
{
  vector<string> rows = getAllLines(EXAMPLE);
  ASSERT_THAT(vectorSize(rows) , Eq(4));
}

TEST(vectorSize, just_one_row)
{
  vector<string> rows ({" 1 2 "});
  ASSERT_THAT(vectorSize(rows) , Eq(3));
}

TEST(solA, example)
{
  EXPECT_THAT(solA(getAllLines(EXAMPLE)), Eq("CMZ"));
}
