#include "note.hh"
#include<structured_input.hh>

Note::Note(string const &s)
{
  istringstream in(s);
  in>>*this;
}


istream& operator>>(istream& in, Note&n)
{
  in>>n.t>>" ";
  string s;
  getline(in, s);
  if(s=="falls asleep")
    n.a = ::Action::sleep;
  else if(s=="wakes up")
    n.a = ::Action::wake;
  else
    {
      n.a = ::Action::guard;
      istringstream in(s);
      in>>"Guard #">>n.guard.get()>>" begins shift";
    }
  

  return in;
}

bool operator<(Note const &a, Note const &b)
{
return a.t<b.t;
}

#include<sstream>
#include<gtest/gtest.h>
#include<gmock/gmock.h>
using namespace testing;


TEST(Note, Action)
{
istringstream in(
"[1518-11-01 00:00] Guard #10 begins shift\n"
"[1518-11-01 00:05] falls asleep\n");

Note a,b;

in>>a>>b;
EXPECT_TRUE(a<b);
EXPECT_FALSE(b<a);
}

TEST(Note, sort)
{
istringstream in(
"[1518-11-01 00:00] Guard #10 begins shift\n"
"[1518-11-01 00:05] falls asleep\n");

Note a,b;

in>>a>>b;
EXPECT_TRUE(a<b);
EXPECT_FALSE(b<a);
}

TEST(Note, read)
{
  istringstream in("[1518-11-01 00:25] wakes up");
  Note sut;
  in >> sut;
  
  EXPECT_THAT(sut.t.year,	Eq(1518));
  EXPECT_THAT(sut.t.month,	Eq(11));
  EXPECT_THAT(sut.t.day,	Eq(01));
  EXPECT_THAT(sut.t.hour,	Eq(0));
  EXPECT_THAT(sut.t.minute,	Eq(25));
EXPECT_THAT(sut.a,		Eq(::Action::wake));
}

TEST(Time, compare)
{
  EXPECT_FALSE(Time(1, 0, 0, 0, 0) < Time(0, 1, 0, 0, 0));
  EXPECT_TRUE (Time(1, 0, 0, 0, 0) < Time(1, 1, 0, 0, 0));
  EXPECT_FALSE(Time(1, 1, 0, 0, 0) < Time(1, 1, 0, 0, 0));
}
