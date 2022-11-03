#pragma once
#include "time.hh"
#include "notes.hh"
#include <cassert>
#include <functional>
#include "named_types.hh"
using namespace std;




using Callback = function<void(Guard, int)>;
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
    if(n.a==Action::guard)
      {
	if(not awake_)
	  {
	    for(; time_.minute<60 ;time_.minute++)
	      callback_(guard_, time_.minute);
	  }
	guard_=n.guard;
	time_ = n.t;
      }
    else if (awake_)
      {
	assert(n.a==Action::sleep);
	time_ = n.t;
      }
    else
      {
	assert(n.a==Action::wake);

	for(; time_<n.t ;time_.minute++)
	{
	  assert(time_.minute < 60);
	  callback_(guard_, time_.minute);
	}
      }
    awake_= (n.a != Action::sleep);
  }

  Guard guard() const {return guard_;}
  
private:
  Callback callback_;
  Time time_;
  Guard guard_;
  bool awake_{true};
};

