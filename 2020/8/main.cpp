#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <fstream>
//#include <regex>
//#include <iostream>
//#include <sstream>
//#include <numeric>

TEST(hello, world)
{
  EXPECT_TRUE(true);
}
using namespace std;

struct Command{
  string cmd; //command
  int arg; //argument
};

istream& operator>>(istream &cin, Command &c)
{
  cin>>c.cmd;
  cin>>c.arg;
  return cin;
}

ostream& operator<<(ostream &cout, Command const &c)
{
  cout	<< c.cmd
	<< " "
	<< c.arg;
  return cout;
}


using Code = vector<Command>;

ostream& operator<<(ostream& cout, Code const & c)
{
  for(auto const &x:c)
    cout<<x<<endl;
  return cout;
}

Code getCommands(string const &filename)
{
  Code ret;
  ifstream in(filename);
  assert(in.is_open());
  Command line;
  while( not (in>>line).eof() )
      ret.push_back(line);
  return ret;
}

struct GameBoy
{
  Code code;
  size_t pos{0};
  int accumulator{0};

  template<class CODE>
  GameBoy(CODE &&c)
    :code(forward<CODE>(c))
  {}
  
  void step()
  {
    if (code[pos].cmd == "acc")
      {
	accumulator+=code[pos].arg;
	pos++;
      }
    else if (code[pos].cmd == "jmp")
	pos+=code[pos].arg;
    else if (code[pos].cmd == "nop")
      pos++;
  }
  bool success() const
  {
    return pos>=code.size();
  }
  unsigned int run();
};

TEST(GameBoy, read_data)
{
  GameBoy sut(getCommands(EXAMPLE));
  
  EXPECT_EQ(9, sut.code.size());
  EXPECT_EQ("acc", sut.code[8].cmd);
  EXPECT_EQ(6, sut.code[8].arg);
}
  

TEST(GameBoy, step)
{
  GameBoy sut(getCommands(EXAMPLE));

  for(int i=0;i<7;i++)
    sut.step();
  EXPECT_EQ(5, sut.accumulator);
}

pair<unsigned int, GameBoy> infiniteLoopSteps(GameBoy b)
{
  auto steps = b.run();
  assert(not b.success());//i.e. infinite loop
  return {steps, move(b)};
}

TEST(GameBoy, infiniteLoopSteps)
{
  auto const sut = infiniteLoopSteps(GameBoy(getCommands(EXAMPLE)));
  EXPECT_EQ(7, get<unsigned int>(sut));
  EXPECT_EQ(5, get<GameBoy>(sut).accumulator);
}

TEST(solution, a)
{
  auto const sut = infiniteLoopSteps(GameBoy(getCommands(INPUT)));
  EXPECT_EQ(1487, get<GameBoy>(sut).accumulator);
}

unsigned int GameBoy::run()
{
  set<size_t> positions{};
  while(pos<code.size())
    {
      if( positions.contains(pos) )
	return positions.size();
      else
	{
	  positions.insert(pos);
	  step();
	}
    }
  return positions.size();
}

Command toggle(Command c)
{
  string &cmd = c.cmd;
  if(cmd=="jmp")
    cmd="nop";
  else if (cmd=="nop")
    cmd="jmp";
  return c;
}

Code toggle(Code c, size_t index)
{
  c[index] = toggle(c[index]);
  return c;
}


TEST(toggle, Command)
{
  EXPECT_EQ("jmp", toggle(Command{"nop",0}).cmd);
  EXPECT_EQ("nop", toggle(Command{"jmp",0}).cmd);
  EXPECT_EQ("acc", toggle(Command{"acc",0}).cmd);
}

optional<int> evaluate(Code const &c)
{
  GameBoy g(c);
  g.run();
  if(g.success())
    return g.accumulator;
  else
    return {};
}


TEST(toggle, example)
{
  auto sut = getCommands(EXAMPLE);
  sut[7] = toggle(sut[7]);
  
  EXPECT_EQ(8, evaluate(sut).value());

  EXPECT_EQ(8, evaluate(toggle(getCommands(EXAMPLE), 7)).value());
}

int solveB(Code const &c, size_t index=0)
{
  assert(index<c.size());
  auto x = evaluate(toggle(c, index));
  if(not x)
    return solveB(c, 1+index);
  else
    return x.value();
}

TEST(solve_b, example)
{
  EXPECT_EQ(8, solveB(getCommands(EXAMPLE)));
}

TEST(solve_b, input)
{
  EXPECT_EQ(1607, solveB(getCommands(INPUT)));
}
