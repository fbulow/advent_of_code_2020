#pragma once
#include"types.hh"
#include<map>
#include "input.hh"
#include <tuple>

class Distance{
public:
  Distance(Input const &inp,
	   Valve start,
	   Steps maxSteps)
  {
    
  }
  std::set<std::pair<Valve, Steps>> from(Valve, Steps) const
  {
    
    
    return {{"II", 1}};
  }
};
	       
