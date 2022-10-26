#include "time.hh"
#include <sstream>
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

