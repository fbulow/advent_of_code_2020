#pragma once
#include <vector>
#include "types.hh"

struct Event{
  Minutes timePassed;
  Valve open;
};

using Path = std::vector<Event>;
