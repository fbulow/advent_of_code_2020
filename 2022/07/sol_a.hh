#pragma once
#include <string>
#include "nav.hh"
#include "tree.hh"

class SolA{
  Nav n;
  Tree t;
public:
  SolA & operator<<(std::string const &);
  
  long long int ans() const;
  size_t requiredSpace() const;
  size_t smallest() const;
  
};
