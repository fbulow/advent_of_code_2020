#pragma once

#include "types.hh"
#include <functional>

using Distance = std::function<Minutes(Valve, Valve)>;


class DistanceImpl
{
public:
  Minutes operator()(Valve, Valve) const
  {
    return 0;
  }
  
};
