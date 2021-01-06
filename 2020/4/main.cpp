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
				  regex(unit),
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


bool inIntervall(optional<int> value, int min, int max)
{
  return value     and
    (value >= min) and
    (value <= max);
}

bool inIntervall(string value, int min, int max)
{
  return inIntervall(stoi(value), min, max);
}

bool matches(string const &value, string const & sxpr)
{
  return regex_match(value.begin(),
		     value.end(),
		     regex(sxpr));
}

bool validateField(string const & c, string const & key)
{
  if (key==byr)
      return inIntervall(get(c, byr), 1920, 2002);
  else if (key==iyr)
      return inIntervall(get(c, iyr), 2010, 2020);
  else if (key==eyr)
      return inIntervall(get(c, eyr), 2010, 2030);
  else if (key==hgt)
	return
	  inIntervall(getCm(get(c,hgt)), 150, 193) or
	  inIntervall(getInch(get(c,hgt)), 59, 76);
  else if (key== hcl)
      return matches(get(c, hcl), "^#[0-9a-f]{6}$");
  else if (key==ecl)
      return matches(get(c, ecl), "(amb)|(blu)|(brn)|(gry)|(grn)|(hzl)|(oth)");
  else if (key == pid)
      return matches(get(c, pid), "[0-9]{9}");
  else
    assert(false);
}

bool validateFields(string const & c)
{

  vector<string> keys{
    byr,     
    iyr,     
    eyr,     
    hgt,     
    hcl,     
    ecl,     
    pid};
  return all_of(keys.begin(),
		keys.end(),
		[c](auto const &key){
		  return validateField(c, key);
		});

}

TEST(validateFields, case_iyr)
{
  EXPECT_TRUE (validateField("iyr:2010",iyr));
  EXPECT_TRUE (validateField("iyr:2020",iyr));
  EXPECT_FALSE(validateField("iyr:2003",iyr));
}

TEST(validateFields, case_eyr)
{
  EXPECT_TRUE (validateField("eyr:2020",eyr));
  EXPECT_TRUE (validateField("eyr:2030",eyr));
  EXPECT_FALSE(validateField("eyr:2003",eyr));
  EXPECT_FALSE(validateField("eyr:1972",eyr));
}


TEST(validateFields, case_byr)
{
  EXPECT_TRUE (validateField("byr:2002", byr));
  EXPECT_FALSE(validateField("byr:2003", byr));
}

TEST(validateFields, case_hgt)
{
  EXPECT_TRUE (validateField("hgt:190cm", hgt));
  EXPECT_TRUE (validateField("hgt:60in", hgt));
  EXPECT_FALSE(validateField("hgt:190in", hgt));
  EXPECT_FALSE(validateField("hgt:190", hgt));
}

TEST(validateFields, case_hcl)
{
  EXPECT_TRUE (validateField("hcl:#123abc", hcl));
  EXPECT_FALSE(validateField("hcl:#123abz", hcl));
  EXPECT_FALSE(validateField("hcl:123abc", hcl));
}

TEST(validateFields, case_ecl)
{
  EXPECT_TRUE (validateField("ecl:brn", ecl));
  EXPECT_FALSE(validateField("ecl:wat", ecl));
}

TEST(validateFields, case_pid)
{
  EXPECT_TRUE (validateField("pid:000000001", pid));
  EXPECT_FALSE(validateField("pid:0123456789", pid));
}

bool isValidPassport(string const & p)
{
  return hasAllFields(p) and validateFields(p);
}


TEST(isValidPassport, invalid_ones)
{
  auto const sut = getBatch(invalid_passports);
  EXPECT_FALSE(isValidPassport(sut[0]));
  EXPECT_FALSE(isValidPassport(sut[1]));
  EXPECT_FALSE(isValidPassport(sut[2]));
  EXPECT_FALSE(isValidPassport(sut[3]));

  EXPECT_EQ(0, count_if(sut.begin(), sut.end(), isValidPassport));
}

TEST(isValidPassport, valid_ones)
{
  auto const sut = getBatch(valid_passports);
  EXPECT_TRUE(isValidPassport(sut[0]));
  EXPECT_TRUE(isValidPassport(sut[1]));
  EXPECT_TRUE(isValidPassport(sut[2]));
  EXPECT_TRUE(isValidPassport(sut[3]));

  EXPECT_EQ(4, count_if(sut.begin(), sut.end(), isValidPassport));

}

TEST(solution, b)
{
  auto const sut = getBatch(input);
  EXPECT_EQ(121, count_if(sut.begin(), sut.end(), isValidPassport));
}
