#include <gtest/gtest.h>
#include <vector>
#include <functional>
#include <string_view>
#include <fstream>
#include <iostream>
#include <regex>
using namespace std;

TEST(hello, world)
{
  ASSERT_TRUE(true);
}

vector<string> getCredentials(string const &filename)
{
  ifstream in(filename);
  assert(in.is_open());
  vector<string> ret;
  string line;
  ostringstream credentials{};
  while(getline(in, line))
    {
      if(line.empty())
	{
	  ret.push_back(credentials.str());
	  credentials=ostringstream{};
	}
      else
	  credentials<<line<<endl;
    }
  ret.push_back(credentials.str());
  
  return ret;
}

TEST(getCredentials, first)
{
  EXPECT_EQ(
	  getCredentials(example)[0],
	  "ecl:gry pid:860033327 eyr:2020 hcl:#fffffd\n"
	  "byr:1937 iyr:2017 cid:147 hgt:183cm\n");

  EXPECT_EQ(
	  getCredentials(example)[1],
	  "iyr:2013 ecl:amb cid:350 eyr:2023 pid:028048884\n"
	  "hcl:#cfa07d byr:1929\n");

  EXPECT_EQ(4,
	    getCredentials(example).size());
}


bool hasKey(string const &c, string const &key)
{
  return regex_search(c.begin(), c.end(), regex(key+":"));
}

TEST(hasKey, first)
{
  
  auto const second = "iyr:2013 ecl:amb cid:350 eyr:2023 pid:028048884\n"
    "hcl:#cfa07d byr:1929\n";

  
  EXPECT_EQ(second,
	    getCredentials(example)[1]);

  EXPECT_TRUE(hasKey(second, "byr"));//first
  EXPECT_TRUE(hasKey(second, "iyr"));//last
  EXPECT_TRUE(hasKey(second, "eyr"));//not first or last
  EXPECT_FALSE(hasKey(second, "hgt"));//missing
}
