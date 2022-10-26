#include "notes.hh"
#include<structured_input.hh>

istream& operator>>(istream& in, Notes &n)
{
  Note slask;
  in>>slask;
  while(not in.eof())
    {
      n.insert(slask);
      in>>slask;
    }
  return in;
}

#include<sstream>
#include<gtest/gtest.h>
#include<gmock/gmock.h>
using namespace testing;

TEST(Notes, initialize)
{
  Notes sut;
  istringstream in(
		   "[1518-11-01 00:05] falls asleep\n"
		   "[1518-11-01 00:00] Guard #10 begins shift\n"
		   );
  in>>sut;
  EXPECT_THAT(sut.cbegin()->t.minute, Eq(0));
  EXPECT_THAT(next(sut.cbegin())->t.minute, Eq(5));
}

