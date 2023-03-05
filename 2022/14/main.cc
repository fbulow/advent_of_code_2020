#include <gtest/gtest.h>
#include <gmock/gmock.h>

using namespace std;
using namespace testing;

void washLine(string &s)
{
  for(char &c:s)
    switch(c)
      {
      case '-':
      case '>':
      case ',':
	c=' ';
      default:
	{}
      }
}
TEST(washLine, example)
{
  string s = "503,4 -> 502,4";
  washLine(s);

  istringstream in(s);
  int a,b,c,d;
  in>>a>>b>>c>>d;

  EXPECT_THAT(a, Eq(503));
  EXPECT_THAT(b, Eq(4));
  EXPECT_THAT(c, Eq(502));
  EXPECT_THAT(d, Eq(4));
}
