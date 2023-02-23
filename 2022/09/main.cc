#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <fstream>

#include "rope.hh"
using namespace testing;

TEST(Rope, move_right)
{
  Rope sut;
  EXPECT_THAT(sut.step('R'), Eq(Coord{0,0}));
  EXPECT_THAT(sut.step('R'), Eq(Coord{0,1}));
}

TEST(Rope, move_left)
{
  Rope sut;
  EXPECT_THAT(sut.step('L'), Eq(Coord{0,0}));
  EXPECT_THAT(sut.step('L'), Eq(Coord{0,-1}));
}

TEST(Rope, move_up)
{
  Rope sut;
  EXPECT_THAT(sut.step('U'), Eq(Coord{0,0}));
  EXPECT_THAT(sut.step('U'), Eq(Coord{-1,0}));
}
TEST(Rope, move_down)
{
  Rope sut;
  EXPECT_THAT(sut.step('D'), Eq(Coord{0,0}));
  EXPECT_THAT(sut.step('D'), Eq(Coord{1,0}));
}
TEST(Rope, move_diagonal)
{
  Rope sut;
  EXPECT_THAT(sut.step('R'), Eq(Coord{0,0}));
  EXPECT_THAT(sut.step('D'), Eq(Coord{0,0}));
  EXPECT_THAT(sut.step('D'), Eq(Coord{1,1}));
}



TEST(Coord, motion)
{
  Coord sut;
  EXPECT_THAT(sut, Eq(Coord(0,0)));
  EXPECT_THAT(sut.step('R'), Eq(Coord(0 ,1 )));
  EXPECT_THAT(sut.step('L'), Eq(Coord(0 ,-1)));
  EXPECT_THAT(sut.step('D'), Eq(Coord(1 ,0 )));
  EXPECT_THAT(sut.step('U'), Eq(Coord(-1,0 )));
}

#include<set>
#include<sstream>
struct Solution
{
  Rope r;
  std::set<Coord> visited;
  
  int ans()
  {
    return visited.size();
  }

  Solution& operator<<(std::string const &s)
  {
    if(s.empty()) return *this;
      
    int repeat;
    char dir;
    std::istringstream in(s);
    in>>dir>>repeat;
    while(repeat-- > 0)
      visited.insert(r.step(dir));
    return *this;
  }
    
};




TEST(Solution, example)
{
  Solution sut;
  
  sut
    << "R 4";
  EXPECT_THAT(sut.ans(), Eq(4));

  sut    
    << "U 4";
  EXPECT_THAT(sut.ans(), Eq(7));
  
  sut    
    << "L 3"
    << "D 1"
    << "R 4"
    << "D 1"
    << "L 5"
    << "R 2";

  EXPECT_THAT(sut.ans(), Eq(13));

}

TEST(Solution, a)
{
  Solution sut;
  std::ifstream in(INPUT);
  std::string row;
  std::getline(in,row);
  while(not row.empty())
    {
      sut<< row;
      std::getline(in,row);
    }
  
  //  std::cout << "Answer a: "<<sut.ans()<< std::endl;
  EXPECT_THAT(sut.ans(), Eq(6311));
}

