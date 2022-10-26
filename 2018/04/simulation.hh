#pragma once
#include "time.hh"
#include "notes.hh"
#include <cassert>
#include <functional>

using namespace std;

using Callback = function<void(int, bool)>;
class Simulation{
public:
  Simulation(Note const &n,
	     Callback callback=[](auto...){})
    :callback_(callback)
    ,time_(n.t)
    ,guard_(n.guard)
     
  {
    assert(n.a==Action::guard);
  }
  
  Time time() const{return time_;}
  bool awake() const{ return awake_;}
  void execute(Note const &n)
  {
    if(n.t.day>time_.day)
      {
	time_ = n.t;
	time_.hour=0;
	time_.minute=0;
      }
    for(; time_<n.t ;time_.minute++)
      callback_(guard_, awake());
    awake_= (n.a != Action::sleep);
  }
  
private:
  Callback callback_;
  Time time_;
  int guard_;
  bool awake_;
};


#include<sstream>
#include<gtest/gtest.h>
#include<gmock/gmock.h>
using namespace testing;

TEST(Simulation, callback_second_guard_shows_up)
{
  int a=0;
  Simulation sut(Note("[1518-11-01 00:00] Guard #10 begins shift"),
		 [&a](auto...){
		   a++;
		 });
  sut.execute(Note("[1518-11-02 00:00] Guard #11 begins shift"));
  EXPECT_THAT(a, Eq(60));
}
