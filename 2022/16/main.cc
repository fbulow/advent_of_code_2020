#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <vector>
#include <fstream>

using namespace testing;
using namespace std;

vector<string> readInput(istream &in)
{
  vector<string> ret;
  try
    {
      while(true)
	{
	  ret.emplace_back(
			   [&ret, &in]()
			   {
			     string row;
			     getline(in, row);
			     if(row.empty())
			       throw exception();
			     return row;
			   }());
	}
    }
  catch(...)
    {
    }
  return ret;
}

auto readInput(string const &filename)
{
  ifstream in(filename);
  return readInput(in);
}

struct Row{
  std::string from;
  int rate{1};
  vector<std::string> to;
  Row(std::string row)
  {
    istringstream in(row);
    in>>from>>from;

    std::string slask;
    in>>slask>>slask>>slask;
    for(int i=0;i<5;i++)
      slask[i]=' ';
    (*slask.rbegin())=' ';
    istringstream inInt(slask);
    inInt>>rate;
    in>>slask>>slask>>slask>>slask;

    in>>slask;
    while(*slask.rbegin() == ',')
      {
	to.emplace_back(std::string(slask.begin(), prev(slask.end())));
	in>>slask;
      }
    to.emplace_back(std::move(slask));
  }
};


TEST(scrubbed, example)
{
  {
    Row sut("Valve AA has flow rate=0; tunnels lead to valves DD, II, BB");
    EXPECT_THAT(sut.from, Eq("AA"));
    EXPECT_THAT(sut.rate, Eq(0));
    EXPECT_THAT(sut.to, Contains("DD"));
    EXPECT_THAT(sut.to, Contains("II"));
    EXPECT_THAT(sut.to, Contains("BB"));
    EXPECT_THAT(sut.to.size(), Eq(3));
  }
  {
    Row sut("Valve HH has flow rate=22; tunnel leads to valve GG");
    EXPECT_THAT(sut.from, Eq("HH"));
    EXPECT_THAT(sut.rate, Eq(22));
    EXPECT_THAT(sut.to, Contains("GG"));
    EXPECT_THAT(sut.to.size(), Eq(1));
  }
}


TEST(readInput, example)
{
  auto sut = readInput(EXAMPLE);
  EXPECT_THAT(sut.size(), Eq(10));
}

