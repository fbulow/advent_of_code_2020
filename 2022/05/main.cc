#include"headers.hh"

size_t vectorSize(size_t v)
{
  return v+1;
}
  

class State{
  vector<stack<char>> stacks; // Stack zero is never used to match index
  
public:
  State(vector<string> const &input)
  {
    size_t endCrates = numbersRow(input);    
    stacks.resize(vectorSize(endCrates));

    for(auto row=stacks.size()-1; row>=0; row--)
      {
	string const & s = input[row];
	if(not s.empty())
	  for(int column=1; column < stacks.size(); column++)
	    {
	      char c =getStack(column , s);
	      if(c!=' ')
		stacks[column].push(c);
	    }
      }
    applyCommands(input);
	  
	  

  }

  void applyCommands(vector<string> input) //TODO
  {}
  void applyCommand(Command i)
  {
    while(i.count-->0)
      {
	stacks[i.to].push(stacks[i.from].top());
	stacks[i.from].pop();
      }
  }
  
  operator string ()
  {
    string ret;
    auto N = stacks.size();
    for(auto i = 1; i<N; i++)
      {
	auto const & s = stacks[i];
	if(s.empty())
	  ret.push_back('@');
	else
	  ret.push_back(s.top());
      }
    return ret;  //"CMZ"; //TODO
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

TEST(command, ctor)
{
  Command sut("move 1 from 2 to 3");
  EXPECT_THAT(sut.count	, Eq(1));
  EXPECT_THAT(sut.from	, Eq(2));
  EXPECT_THAT(sut.to	, Eq(3));
}


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


TEST(stack, test)
{
  stack<char> sut;
  
  sut.push('a');
  sut.push('b');
  
  EXPECT_THAT(sut.top(), Eq('b'));
  sut.pop();

  EXPECT_THAT(sut.top(), Eq('a'));
  EXPECT_FALSE(sut.empty());
  EXPECT_THAT(sut.top(), Eq('a'));
  sut.pop();
  EXPECT_TRUE(sut.empty());;
}
