#include<gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <fstream>
using namespace testing;
using namespace std;


struct Rep
{
  string asString;
  int asInt;

  static vector<Rep> intsOnly()
  {
    return {
      Rep{"0", 0},
      Rep{"1", 1},
      Rep{"2", 2},
      Rep{"3", 3},
      Rep{"4", 4},
      Rep{"5", 5},
      Rep{"6", 6},
      Rep{"7", 7},
      Rep{"8", 8},
      Rep{"9", 9}};

  }
  static vector<Rep> all()
  {
    auto ret = intsOnly();
    ret.emplace_back("zero",	  0);
    ret.emplace_back("one",	  1);
    ret.emplace_back("two",	  2);
    ret.emplace_back("three",	  3);
    ret.emplace_back("four",	  4);
    ret.emplace_back("five",	  5);
    ret.emplace_back("six",	  6);
    ret.emplace_back("seven",	  7);
    ret.emplace_back("eight",	  8);
    ret.emplace_back("nine",	  9);
  return ret;
  }
};

using Reps = vector<Rep>;

int firstValue(auto begin, auto end, Reps const &reps)
{
  string s(begin, end);
  for(auto const &r:reps)
    {
      if(s.starts_with(r.asString))
	return r.asInt;
    }
  return firstValue(next(begin), end, reps);
}

int firstValue(string s, Reps const &reps)
{
  return firstValue(s.begin(),
		    s.end(),
		    reps);
}

int lastValue(auto const &s, Reps reps)
{
  for(auto &r: reps)
    r.asString = string{r.asString.rbegin(), r.asString.rend()};
  
  return firstValue(s.rbegin(), s.rend(), reps);
}


int callibrationValue(std::string s, Reps const &r)
{
  return
    10*firstValue(s, r) +
    lastValue(s, r);
}


auto sol(istream &in, Reps const & r)
{
  string nxt;
  int ans{0};
  while((in>>nxt, !nxt.empty()))
    {
      ans+=callibrationValue(nxt, r);
      nxt.clear();
    }
  return ans;
}

auto solA(istream &in)
{
  return sol(in, Rep::intsOnly());
}

auto solB(istream &in)
{
  return sol(in, Rep::all());
}


TEST(solution, A)
{
  ASSERT_THAT(callibrationValue("1abc2", Rep::intsOnly()), Eq(12));

  ASSERT_THAT(callibrationValue("pqr3stu8vwx", Rep::intsOnly()), Eq(38));
  ASSERT_THAT(callibrationValue("a1b2c3d4e5f", Rep::intsOnly()), Eq(15));
  ASSERT_THAT(callibrationValue("treb7uchet" , Rep::intsOnly()), Eq(77));

  {
    ifstream in(EXAMPLE);
    ASSERT_THAT(solA(in), Eq(142));
  }
  {
    ifstream in(INPUT);
    ASSERT_THAT(solA(in), Eq(55447));
  }
}

TEST(b, firstAsNumber)
{
  ASSERT_THAT(firstValue("4nineeightseven2", Rep::intsOnly()),
	      Eq(4));
}

TEST(SolB, input)
{
  istringstream exampleB(
		   "two1nine\n"
		   "eightwothree\n"
		   "abcone2threexyz\n"
		   "xtwone3four\n"
		   "4nineeightseven2\n"
		   "zoneight234\n"
		   "7pqrstsixteen\n");

  {
    ASSERT_THAT(solB(exampleB), Eq(281));
  }
  {
    ifstream in(INPUT);
    ASSERT_THAT(solB(in), Eq(281));
  }
}
