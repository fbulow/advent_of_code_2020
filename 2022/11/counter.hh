#pragma once

#include <map>
#include <set>
#include <algorithm>

class Counter{
  std::map<size_t, long int> data;
public:
  void tick(size_t v);
  long long int monkeyBusines() const;
  long int operator[](size_t i) const
  {
    return data.find(i)->second;
  }
};
