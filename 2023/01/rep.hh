#pragma once
#include<vector>
#include<string>

struct Rep;
using Reps = std::vector<Rep>;

struct Rep
{
  std::string asString;
  int asInt;

  [[nodiscard]]
  static Reps intsOnly();
    

  [[nodiscard]]
  static Reps all();
    
};


