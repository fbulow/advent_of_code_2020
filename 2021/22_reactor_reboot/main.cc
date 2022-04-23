#include <gtest/gtest.h>
#include<algorithm>
#include<fstream>
#include"cube.hh"
#include"instruction.hh"
#include"space.hh"
#include<list>
#include"solution_a.hh"

#include"square_space.hh"
#include"cube.hh"

using namespace std;

auto solutionB(vector<Instruction> const &input)
{
  SquareSpace space;
  for(auto &x: input)
    space.fill(x.cube, x.turnOn());

    return space.countOn();
}
TEST(solution, B)
{
  EXPECT_EQ(39, solutionB({
	{"on x=10..12,y=10..12,z=10..12"},
	{"on x=11..13,y=11..13,z=11..13"},
	{"off x=9..11,y=9..11,z=9..11"},
	{"on x=10..10,y=10..10,z=10..10"}}));

  ifstream in(INPUT);
  vector<Instruction> inp;
  string line;
  getline(in, line);
  while( in.good())
    {
      inp.emplace_back(Instruction(line));
      getline(in, line);
    }
  cout<<inp.size()<<endl;
  auto ans = solutionB(inp);
  ASSERT_LT(538345334, ans);
  cout<<"Ans: "<<ans<<endl;
}

