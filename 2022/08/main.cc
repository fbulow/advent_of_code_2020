#include <AoC/getAllLines.hh>
#include <numeric>
#include <algorithm>
#include <ranges>

using namespace std;

class Tree{
  char value_;
  bool ticked_{false};
public:
  Tree(char c)
    :value_(c)
  {
  }
  bool ticked() const {return ticked_;} 
  char value()  const {return value_;} 
  void tick(){ticked_=true;}
};

struct TreeLine:vector<Tree>
{
  TreeLine(string_view s)
    :vector<Tree>(s.begin(), s.end())
  {}
};

void sweepLine(auto begin, auto end, char max='0'-1)
{
  if (begin==end)
    return;
  else if(begin->value()>max)
    {
      begin->tick();
      return sweepLine(ranges::next(begin), end, begin->value());
    }
  else
    return sweepLine(ranges::next(begin), end, max);
}

class Forrest : vector<TreeLine>
{
  
public:
  Forrest(vector<string>const &vs)
    :Forrest([vs]()
    {
      vector<TreeLine> ret;
      ret.reserve(vs.size());
      for(auto s:vs)
	if(not s.empty())
	  ret.emplace_back(TreeLine(s));
      return ret;
    }())
  {}
  
  Forrest(vector<TreeLine> data)
    :vector<TreeLine>(move(data))
  {}
  using vector<TreeLine>::operator[];
  void transpose(){}//TODO
  void sweepLines()
  {
      for(auto &treeLine: *this)
	{
	  sweepLine(treeLine.begin(),  treeLine.end());
	  sweepLine(treeLine.rbegin(), treeLine.rend());
	}
  }
  void sweep(){
    {
      sweepLines();
      transpose();
      sweepLines();
    }
  }

  int  countVisible(){}//TODO
};


int solA(vector<string> const &data)
{
  Forrest f(data);
  f.sweep();
  return f.countVisible();
}

#include<gtest/gtest.h>
#include<gmock/gmock.h>

using namespace testing;


TEST(Forrest, sweepLines)
{
  Forrest sut({
      TreeLine("30373")
      ,TreeLine("25512")});
  sut.sweepLines();
  EXPECT_TRUE	(sut[0][0].ticked());
  EXPECT_FALSE	(sut[0][1].ticked());
  EXPECT_FALSE	(sut[0][2].ticked());
  EXPECT_TRUE	(sut[0][3].ticked());
  EXPECT_TRUE	(sut[0][4].ticked());
    
  EXPECT_TRUE	(sut[1][0].ticked());
  EXPECT_TRUE	(sut[1][1].ticked());
  EXPECT_TRUE	(sut[1][2].ticked());
  EXPECT_FALSE	(sut[1][3].ticked());
  EXPECT_TRUE	(sut[1][4].ticked());
  
}

TEST(sweepLine, examples)
{
  {  
    TreeLine sut("5184");
    sweepLine(sut.begin(), sut.end());
    EXPECT_TRUE	(sut[0].ticked());
    EXPECT_FALSE	(sut[1].ticked());
    EXPECT_TRUE	(sut[2].ticked());
    EXPECT_FALSE	(sut[3].ticked());
  }
  {  
    TreeLine sut("5184");
    sweepLine(sut.rbegin(), sut.rend());
    EXPECT_FALSE (sut[0].ticked());
    EXPECT_FALSE (sut[1].ticked());
    EXPECT_TRUE	 (sut[2].ticked());
    EXPECT_TRUE  (sut[3].ticked());
  }
}


TEST(Tree, all)
{
  Tree sut('8');
  EXPECT_EQ('8', sut.value());

  ASSERT_FALSE(sut.ticked());
  sut.tick();
  ASSERT_TRUE(sut.ticked());

}

  
















