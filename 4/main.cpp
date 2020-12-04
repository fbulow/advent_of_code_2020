#include <gtest/gtest.h>
#include <vector>
#include <functional>
#include <string_view>
#include <fstream>
#include <iostream>
#include <regex>
#include <algorithm>
using namespace std;

TEST(hello, world)
{
  ASSERT_TRUE(true);
}

using Batch = vector<string>;

Batch getBatch(string const &filename)
{
  Batch ret;
  ifstream in(filename);
  assert(in.is_open());
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

TEST(getBatch, first)
{
  EXPECT_EQ(
	  getBatch(example)[0],
	  "ecl:gry pid:860033327 eyr:2020 hcl:#fffffd\n"
	  "byr:1937 iyr:2017 cid:147 hgt:183cm\n");

  EXPECT_EQ(
	  getBatch(example)[1],
	  "iyr:2013 ecl:amb cid:350 eyr:2023 pid:028048884\n"
	  "hcl:#cfa07d byr:1929\n");

  EXPECT_EQ(4,
	    getBatch(example).size());
}


bool hasKey(string const &c, string const &key)
{
  return regex_search(c.begin(), c.end(), regex(key+":"));
}


auto constexpr byr = "byr";     
auto constexpr iyr = "iyr";     
auto constexpr eyr = "eyr";     
auto constexpr hgt = "hgt";     
auto constexpr hcl = "hcl";     
auto constexpr ecl = "ecl";     
auto constexpr pid = "pid";     
auto constexpr cid = "cid";     

TEST(hasKey, first)
{
  
  auto const second = "iyr:2013 ecl:amb cid:350 eyr:2023 pid:028048884\n"
    "hcl:#cfa07d byr:1929\n";

  
  EXPECT_EQ(second,
	    getBatch(example)[1]);

  EXPECT_TRUE(hasKey(second, byr));//first
  EXPECT_TRUE(hasKey(second, iyr));//last
  EXPECT_TRUE(hasKey(second, eyr));//not first or last
  EXPECT_TRUE(hasKey(second, hcl));//after newline
  EXPECT_FALSE(hasKey(second, hgt));//missing
}

bool isValid(string const &credential)
{
  for( auto key: {byr,     
		  iyr,     
		  eyr,     
		  hgt,     
		  hcl,     
		  ecl,     
		  pid})
    if(not hasKey(credential, key))
      return false;
  return true;
}
  
TEST(isValid, credential)
{
  EXPECT_TRUE (isValid(getBatch(example)[0]));
  EXPECT_FALSE(isValid(getBatch(example)[1]));
}

TEST(isValid, Example)
{
  auto const sut = getBatch(example);
  EXPECT_EQ(2, count_if(sut.begin(), sut.end(), [](auto const &c){return isValid(c);}));

}

TEST(isValid, Input)
{
  auto const sut = getBatch(input);
  EXPECT_EQ(190, count_if(sut.begin(), sut.end(), [](auto const &c){return isValid(c);}));

}

string removeKey(string const &s)
{
  return {s, s.find(":")+1};
}

TEST(removeKey, test)
{
  EXPECT_EQ("gry", removeKey("ecl:gry"));
  EXPECT_EQ("grygg", removeKey("ecl:grygg"));
}

string get(string const & c, string const & key)
{
  smatch m;
  regex_search(c, m, regex(key+":[^ \n]*"));
  return removeKey(m[0]);
}

TEST(get, first)
{
  EXPECT_EQ("gry",
	    get("ecl:gry pid:860033327 eyr:2020 hcl:#fffffd\n"
		"byr:1937 iyr:2017 cid:147 hgt:183cm\n", ecl));

}
