#include <gtest/gtest.h>
#include "space.hh"


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

TEST(Range, size)
{
  {
    auto sut = Range{0,0};
    EXPECT_EQ(1, sut.size());
  }
  {
    auto sut = Range{0,1};
    EXPECT_EQ(2, sut.size());
  }
}

TEST(Cube, size)
{
  {
    auto sut = Cube{{0,0}, {0,0},{0,0}};
    EXPECT_EQ(1, sut.size());
  }
  {
    auto sut = Cube{{0,1}, {0,0},{0,0}};
    EXPECT_EQ(2, sut.size());
  }
}


TEST(SquareSpace, countOn)
{
  {
    SquareSpace sut;
  
    Range one{0,0};
    sut.fill(Cube{one,one,one}, true);

    EXPECT_EQ(1, sut.countOn());
  }
  {
    SquareSpace sut;
  
    Range one{0,0};
    sut.fill(Cube{{0,1},one,one}, true);

    EXPECT_EQ(2, sut.countOn());
  }

}
  
TEST(Range, split__no_split)
{
  {
    auto sut = Range{1,9}.splitBy(Range(0,10));
    EXPECT_EQ(1, sut.size());
    EXPECT_TRUE(sut.contains(Range{1,9}));
  }
  {
    auto sut = Range{1,9}.splitBy(Range(2,10));
    EXPECT_EQ(2, sut.size());
    EXPECT_TRUE(sut.contains(Range{1,1}));
    EXPECT_TRUE(sut.contains(Range{2,9}));
  }
  {
    auto sut = Range{1,9}.splitBy(Range(0,8));
    EXPECT_EQ(2, sut.size());
    EXPECT_TRUE(sut.contains(Range{1,8}));
    EXPECT_TRUE(sut.contains(Range{9,9}));

  }
  {
    auto sut = Range{1,9}.splitBy(Range(2,8));
    EXPECT_EQ(3, sut.size());
    EXPECT_TRUE(sut.contains(Range{1,1}));
    EXPECT_TRUE(sut.contains(Range{2,8}));
    EXPECT_TRUE(sut.contains(Range{9,9}));
    
  }

}

