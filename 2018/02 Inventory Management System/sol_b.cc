#include<gtest/gtest.h>
#include<gmock/gmock.h>
#include<fstream>
#include<vector>
#include<string_view>
using namespace std;

string consolidate(string_view left, string_view right)
{
  string ret;
  ret.reserve(left.size());
  auto a = left.begin();
  auto b = right.begin();
  while(a!=left.end())
    {
      if(*a==*b)
	ret.push_back(*a);
      a++;
      b++;
    }
  return ret;
}

string consolidate(pair<string_view, string_view> data)
{
  return consolidate(data.first, data.second);
}

bool isPair(pair<string_view, string_view> p )
{
  return p.first.size() == (1+consolidate(p).size());
}


string solb(vector<string> const & data)
{
  for(auto const & a: data)
    for(auto const & b: data)
      {
	pair<string_view, string_view> p(a,b);
	if(isPair(p))
	  return consolidate(p);
      }
  
  return "NOT FOUND";
}

using namespace testing;

TEST(b, isPair)
{
  EXPECT_TRUE(
	      isPair({"fghij", "fguij"}));
  
}

TEST(b, consolidate)
{
  EXPECT_THAT(
	      consolidate("fghij", "fguij"),
	      Eq("fgij")
	      );
  EXPECT_THAT(
	      consolidate({"fghij", "fguij"}),
	      Eq("fgij")
	      );
}

TEST(b, example)
{
  EXPECT_THAT(
	      solb({
		  "abcde",
		  "fghij",
		  "klmno",
		  "pqrst",
		  "fguij",
		  "axcye",
		  "wvxyz",
		}),
	      Eq("fgij")
	      );
}

TEST(b, solution)
{
  ifstream in(INPUT);
  string s;
  vector<string> v;

  in>>s;
  while(not in.eof())
    {
      v.push_back(s);
      in>>s;
    }
  
  
  EXPECT_THAT(
	      solb(v),
	      Eq("")
	      );
}
