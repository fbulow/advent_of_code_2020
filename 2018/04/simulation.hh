#pragma once
#include "time.hh"
#include "notes.hh"
#include <cassert>
#include <functional>
#include "named_types.hh"
using namespace std;




using Callback = function<void(Guard, Time const &)>;
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
    while(time_ < n.t)
      {
	if((not awake_) and (time_.hour==0))
	  callback_(guard_, time_);
	++time_;
      }
    if(time_.hour>0) 
      awake_ = true;

    switch(n.a)
      {
      case Action::guard:
	awake_=true;
	guard_=n.guard;
	return;
      case Action::sleep:
	assert(awake_);
	awake_= false;
	return;
      case Action::wake:
	assert(not awake_);
	awake_= true;
      }
  }

  Guard guard() const {return guard_;}
  
private:
  Callback callback_;
  Time time_;
  Guard guard_;
  bool awake_{true};
};

