#pragma once

#include <map>
#include <set>
#include <algorithm>

class Counter{
  std::map<size_t, int> data;
public:
  void tick(size_t v);
  int monkeyBusines() const;
};
