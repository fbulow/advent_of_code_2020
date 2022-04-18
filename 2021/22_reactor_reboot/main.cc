#include <gtest/gtest.h>
#include<algorithm>
#include<fstream>
#include"cube.hh"
#include"instruction.hh"
using namespace std;

struct Space: vector<bool>
{
  Space()
    :vector<bool>(101*101*101, false)
  {}

  unsigned int countOn() const
  {
    return count_if(cbegin(),
		    cend(),
		    [](auto x)->bool{return x;});
  }

  void fill(Cube c, bool val)
  {
    c.x.min = max(c.x.min, -50);
    c.y.min = max(c.y.min, -50);
    c.z.min = max(c.z.min, -50);

    c.x.max = min(c.x.max,  50);
    c.y.max = min(c.y.max,  50);
    c.z.max = min(c.z.max,  50);
    
    for(int x = c.x.min; x<=c.x.max ; x++)
      for(int y =c.y.min; y<=c.y.max ; y++)
	for(int z =c.z.min; z<=c.z.max ; z++)
	  (*this)(x,y,z) = val;
  }
  
  vector<bool>::reference operator()(int x, int y, int z)
  {
    return (*this)[(x+50)+101*((y+50)+101*(z+50))];
  }
}; 


TEST(Space, full_change)
{
  Space sut;
  EXPECT_TRUE(none_of(sut.begin(),sut.end(), [](auto x)->bool{return x;}));
  EXPECT_EQ(0, sut.countOn());

  sut.fill(Cube{{-50,50},{-50,50},{-50,50}}, true);
  
  EXPECT_TRUE(all_of(sut.begin(),sut.end(), [](auto x)->bool{return x;}));
  EXPECT_EQ(101*101*101, sut.countOn());

  sut.fill(Cube{{-50,50},{-50,50},{-50,50}}, false);
  EXPECT_EQ(0, sut.countOn());

  sut.fill(Cube{{-50,50},{1,1},{1,2}}, true);  
  EXPECT_EQ(202, sut.countOn());
}

unsigned int solutionA(vector<Instruction> const &input)
{
  Space space;    

  for(auto &x: input)
    space.fill(x.cube, x.turnOn());
  return space.countOn();
      
  return 39;
}

TEST(solution, A)
{
  EXPECT_EQ(39, solutionA({
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
  cout<<"Ans: "<<solutionA(inp)<<endl;
  
}
TEST(Instruction, ctor)
{
  EXPECT_TRUE ( Instruction("on x=10..12,y=10..12,z=10..12" ).turnOn() );
  EXPECT_FALSE( Instruction("off x=10..12,y=10..12,z=10..12").turnOn() );

  Cube sut = Instruction("on x=10..12,y=13..14,z=15..16\n").cube;
  EXPECT_EQ(10, sut.x.min);
  EXPECT_EQ(12, sut.x.max);
  EXPECT_EQ(13, sut.y.min);
  EXPECT_EQ(14, sut.y.max);
  EXPECT_EQ(15, sut.z.min);
  EXPECT_EQ(16, sut.z.max);
}

