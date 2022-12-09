#include <AoC/getAllLines.hh>
#include <numeric>
#include <algorithm>
#include <ranges>
#include <sstream>

using namespace std;

class Tree{
  char value_;
  bool ticked_{false};
public:
  Tree(char c)
    :value_(c)
  {}
  
  Tree(Tree const & t)
    :value_(t.value_)
    ,ticked_(t.ticked_)
  {}
  
  bool ticked() const {return ticked_;} 
  char value()  const {return value_;} 
  void tick(){ticked_=true;}
};


struct TreeLine:vector<Tree>
{
  TreeLine(){}
  TreeLine(string_view s)
    :vector<Tree>(s.begin(), s.end())
  {}
  using TreeLine::vector<Tree>::resize;
  using TreeLine::vector<Tree>::operator[];
  using TreeLine::vector<Tree>::begin;
  using TreeLine::vector<Tree>::end;

  int countVisible() const
  {
    return count_if(begin(),
		    end(),
		    [](auto const &t)
		    {
		      return t.ticked();
		    });
  }
};

ostream& operator<<(ostream& out, TreeLine const & tl) 
{
  for(auto const &x:tl)
    out<<x.value();
  return out;
}


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
    :Forrest([vs]() //Evaluated immediately!
    {
      vector<TreeLine> ret;
      ret.reserve(vs.size());
      for(auto s:vs)
	if(not s.empty())
	  ret.emplace_back(TreeLine(s));
      return ret;
    }())
  {}

  string toString() const
  {
    ostringstream out;
    for(auto &s:*this)
	out<<s<<endl;
    return out.str();
  }
  
  Forrest(vector<TreeLine> data)
    :vector<TreeLine>(move(data))
  {}
  using vector<TreeLine>::operator[];

  Forrest transpose() const
  {
    vector<TreeLine> ret;
    auto nRowOut = (*this)[0].size();
    ret.resize(nRowOut);

    string typical;
    for(auto &s: ret)
      s.resize(size(), ' ');
    for(auto row = 0; row<size(); ++row)
      for(auto col = 0; col<nRowOut; ++col)
	ret[col][row] = (*this)[row][col];
    return {ret};
  }
  void sweepLines()
  {
      for(auto &treeLine: *this)
	{
	  sweepLine(treeLine.begin(),  treeLine.end());
	  sweepLine(treeLine.rbegin(), treeLine.rend());
	}
  }
  Forrest sweep(){
    {
      sweepLines();
      auto ret = transpose();
      ret.sweepLines();
      return ret;
    }
  }

  int  countVisible() const 
  {
    return accumulate(begin(),
		      end(),
		      0,
		      [](auto ret , auto const &line)
		      {
			return ret+line.countVisible();
		      });
  }
  
};


int solA(vector<string> const &data)
{
  Forrest f(data);
  return f.sweep().countVisible();
}

#include<gtest/gtest.h>
#include<gmock/gmock.h>

using namespace testing;

TEST(a, solA)
{
  EXPECT_THAT(
	      solA(getAllLines()),
	      Eq(1829));

}


TEST(example, solA)
{
  EXPECT_THAT(
	      solA(getAllLines(EXAMPLE)),
	      Eq(21));

}
  

TEST(Forrest, countVisible)
{
  Forrest sut(vector<string>{"00", "11"});
  EXPECT_THAT(sut.countVisible(), Eq(0));
  sut[0][0].tick();
  EXPECT_THAT(sut.countVisible(), Eq(1));
  sut[1][0].tick();
  EXPECT_THAT(sut.countVisible(), Eq(2));
  sut[1][0].tick();
  EXPECT_THAT(sut.countVisible(), Eq(2));
}

TEST(TreeLine, streamOut)
{
  TreeLine tl("012345");
  ostringstream out;
  out<<tl;
  EXPECT_EQ("012345", out.str());
}

TEST(Forrest, transpose)
{
  auto orig = Forrest ({
      TreeLine("30373")
      ,TreeLine("25512")});

  EXPECT_THAT(orig.toString(),
	      Eq(R"""(30373
25512
)"""));
  
  EXPECT_THAT(orig.transpose().toString(),
	      Eq(R"""(32
05
35
71
32
)"""));
  
}

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

  
















