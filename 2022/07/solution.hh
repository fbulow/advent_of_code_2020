#pragma once
#include <string>
#include "nav.hh"
#include "tree.hh"

class Solution{
  Nav n;
  Tree t;
public:
  Solution & operator<<(std::string const &);
  
  long long int ans() const;
  size_t requiredSpace() const;
  size_t smallest() const;
  
};
