#pragma once
#include "coord.hpp"
#include "example_istream.hpp"
#include "scan_space.hpp"
using namespace std;

using Data = vector<ScanSpace>;

bool isSeparatorLine(string const &s)
{
  return
    s.empty() or
    (s[0] == '\n') or
    (s[1]=='-');
}
TEST(isScannerLine, cases)
{
  EXPECT_TRUE (isSeparatorLine("--- scanner 0 ---"));
  EXPECT_TRUE (isSeparatorLine(""));
  EXPECT_TRUE (isSeparatorLine("\n"));
  EXPECT_FALSE(isSeparatorLine("-373,-505,495"));
}
     
Data input(istream& cin)
{
  Data ret;
  vector<Coord> nxt;
  string line;
  getline(cin, line);
  while(not cin.eof())
    {
      while(isSeparatorLine(line))
        getline(cin, line);
      while(not isSeparatorLine(line) and not cin.eof())
        {
          int x,y,z;
          char c;
          istringstream in(line);
          in>>x>>c>>y>>c>>z;
          nxt.emplace_back(Coord{x,y,z});
          getline(cin, line);
        }
      ret.push_back(nxt);
      nxt.clear();
    }
  ret[0].absoluteCoordinates=true;
  return ret;
}

Data input_example()
{
  auto cin = example_istream();
  return input(cin);
}

TEST(input, something)
{
  auto sut = input_example();
  EXPECT_TRUE (sut[0].absoluteCoordinates);
  EXPECT_FALSE(sut[1].absoluteCoordinates);
  EXPECT_EQ(5, sut.size());
  EXPECT_EQ(30,prev(sut[4].beacons.end())->x);
}

