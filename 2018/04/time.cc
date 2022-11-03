#include "time.hh"
#include <sstream>
#include <vector>

int daysOfMonth(int month)
{
  static  std::vector<int> ret{
    31,
    28,
    31,
    30,
    31,
    30,
    31,
    31,
    30,
    31,
    30,
    31};
  return ret[month-1];
}

void Time::operator++()
{
  minute++;
  if(minute==60)
    {
      minute=0;
      hour++;
      if(hour==24)
	{
	  hour=0;
	  day++;
	}
      if(day==1+daysOfMonth(month))
	{
	  day=1;
	  month++;
	  if(month==13)
	    {
	      month=1;
	      year++;
	    }
	}
    }
}


Time::Time(string const &s)
{
  istringstream in(s);
  in>>*this;
}


bool operator<(Time const &a, Time const &b)
{
  if(a.year<b.year)
    return true;
  else if(a.year>b.year)
    return false;
  if(a.month<b.month)
    return true;
  else if(a.month>b.month)
    return false;
  if(a.day<b.day)
    return true;
  else if(a.day>b.day)
    return false;
  if(a.hour<b.hour)
    return true;
  else if(a.hour>b.hour)
    return false;
  if(a.minute<b.minute)
    return true;
  else
    return false;
}

bool operator==(Time const &a, Time const &b)
{return not ((a<b) or (b<a));}

#include<sstream>
#include<gtest/gtest.h>
#include<gmock/gmock.h>
using namespace testing;

TEST(Time, increase)
{
  Time sut("[1518-07-13 00:13]");
  ++sut;
  EXPECT_THAT(sut, Eq(Time("[1518-07-13 00:14]")));
}

TEST(Time, increase_hour)
{
  Time sut("[1518-07-13 00:59]");
  ++sut;
  EXPECT_THAT(sut, Eq(Time("[1518-07-13 01:00]")));
}

TEST(Time, increase_day)
{
  Time sut("[1518-07-13 23:59]");
  ++sut;
  EXPECT_THAT(sut, Eq(Time("[1518-07-14 00:00]")));
}


TEST(Time, increase_month)
{
  Time sut("[1518-07-31 23:59]");
  ++sut;
  EXPECT_THAT(sut, Eq(Time("[1518-08-01 00:00]")));
}

TEST(Time, increase_year)
{
  Time sut("[1518-12-31 23:59]");
  ++sut;
  EXPECT_THAT(sut, Eq(Time("[1519-01-01 00:00]")));
}
