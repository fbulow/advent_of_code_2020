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

ostream& operator<<(ostream &cout, Command &c)
{
  cout	<< c.cmd
	<< " "
	<< c.arg;
  return cout;
}


using Code = vector<Command>;

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
  set<size_t> positions{};
  while(b.pos<b.code.size())
    {
      if( positions.contains(b.pos) )
	return {positions.size(), move(b)};
      else
	{
	  positions.insert(b.pos);
	  b.step();
	}
    }
  assert(false);
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
  EXPECT_EQ(5, get<GameBoy>(sut).accumulator);
}

