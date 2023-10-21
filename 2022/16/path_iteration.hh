#pragma once
#include "path.hh"
#include "types.hh"
#include "regions.hh"
#include <algorithm>
#include <cassert>

#include<functional>

struct FromAndTo{
  Valve from;
  Valve to;
  Minutes distance;
};  

using Callback = std::function<void(Path)>;
using Distance = std::function<Minutes(Valve, Valve)>;

void pathIteration(Callback  ret,
		   Minutes remaining,
		   Distance distance,
		   Regions r,
		   Path p
		   );


void pathIteration(Callback  ret,
		   Minutes remaining,
		   Distance distance,
		   Regions r,
		   Valve const &v = "AA"
		   );
