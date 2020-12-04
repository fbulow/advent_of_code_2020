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

bool hasAllFields(string const &credential)
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
  
TEST(hasAllFields, credential)
{
  EXPECT_TRUE (hasAllFields(getBatch(example)[0]));
  EXPECT_FALSE(hasAllFields(getBatch(example)[1]));
}

TEST(hasAllFields, Example)
{
  auto const sut = getBatch(example);
  EXPECT_EQ(2, count_if(sut.begin(), sut.end(), [](auto const &c){return hasAllFields(c);}));

}

TEST(hasAllFields, Input)
{
  auto const sut = getBatch(input);
  EXPECT_EQ(190, count_if(sut.begin(), sut.end(), [](auto const &c){return hasAllFields(c);}));

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


optional<int> getUnit(string hgt, string const &unit)
{
  string out;
  if(not regex_match(hgt.begin(),
		     hgt.end(),
		     regex("[0-9]*"+unit+"$")))
    return {};
  
  if(out.begin() == regex_replace(out.begin(),
				  hgt.begin(),
				  hgt.end(),
				  regex(unit+"$"),
				  ""))
    return {};
  else
      return stoi(out);
}


TEST(getUnit, no_unit)
{
  EXPECT_FALSE(getUnit("190","in"));
}

optional<int> getInch(string hgt)
{
  return getUnit(hgt, "in");
}

TEST(getInch, first)
{
  EXPECT_FALSE(bool(getInch("")));
  EXPECT_FALSE(bool(getInch("50cm")));
  EXPECT_EQ(5, getInch("5in").value());
  EXPECT_EQ(60, getInch("60in").value());
}

optional<int> getCm(string hgt)
{
  return getUnit(hgt, "cm");
}

TEST(getCm, first)
{
  EXPECT_FALSE(bool(getCm("")));
  EXPECT_EQ(5, getCm("5cm").value());
}

bool validateFields(string const & c)
{
  if(hasKey(c, byr))
    {
      auto y = stoi(get(c,byr));
      return (y>=1920)and(y<=2002);
    }
  if(hasKey(c, hgt))
    {
      auto h = getCm(get(c,hgt));
      if(h)
	return (h.value()>=150) and (h.value()<=193);
      h = getInch(get(c,hgt));
      if(h)
	return (h.value()>=59) and (h.value()<=76);
      return false;
    }
  if(hasKey(c, hcl))
    {
      auto x = get(c, hcl);
      return regex_match(x.begin(),
			 x.end(),
			 regex("^#[0-9a-f]{6}$"));
    }
  if(hasKey(c, ecl))
    {
      auto x = get(c, ecl);
      return regex_match(x.begin(),
			 x.end(),
			 regex("(amb)|(blu)|(brn)|(gry)|(grn)|(hzl)|(oth)"));
    }
  if(hasKey(c, pid)) 
    {
      auto x = get(c, pid);
      return regex_match(x.begin(),
			 x.end(),
			 regex("[0-9]{9}"));

    }
    
  return false;
}

TEST(validateFields, case_byr)
{
  EXPECT_TRUE (validateFields("byr:2002"));
  EXPECT_FALSE(validateFields("byr:2003"));
}

TEST(validateFields, case_hgt) // Intermitent faults????
{
  EXPECT_TRUE (validateFields("hgt:60in"));
  EXPECT_TRUE (validateFields("hgt:190cm"));
  EXPECT_FALSE(validateFields("hgt:190in"));
  EXPECT_FALSE(validateFields("hgt:190"));
}

TEST(validateFields, case_hcl)
{
  EXPECT_TRUE (validateFields("hcl:#123abc"));
  EXPECT_FALSE(validateFields("hcl:#123abz"));
  EXPECT_FALSE(validateFields("hcl:123abc"));
}

TEST(validateFields, case_ecl)
{
  EXPECT_TRUE (validateFields("ecl:brn"));
  EXPECT_FALSE(validateFields("ecl:wat"));
}

TEST(validateFields, case_pid)
{
  EXPECT_TRUE (validateFields("pid:000000001"));
  EXPECT_FALSE(validateFields("pid:0123456789"));
}

