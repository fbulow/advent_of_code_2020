#pragma once
#include <string>

class PositiveIntOrEmpty{
  int value_;
public:
  PositiveIntOrEmpty(std::string const & s);

  int value() const;
  bool empty() const {return value_<0;}
};
