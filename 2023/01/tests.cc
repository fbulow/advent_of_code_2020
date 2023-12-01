#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <fstream>
#include <algorithm>

#include "rep.hh"

using namespace testing;
using namespace std;

int firstValue(auto begin, auto end, Reps const &reps)
{
  string_view s(&*begin, distance(begin, end));
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

int lastValue(auto s, Reps reps)
{
  for(auto &r: reps)
    reverse(r.asString.begin(), r.asString.end());
  reverse(s.begin(), s.end());
  return firstValue(s, reps);
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
    ASSERT_THAT(solB(in), Eq(54706));
  }
}
