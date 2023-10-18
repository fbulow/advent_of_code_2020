#pragma once

#include<optional>
#include "path.hh"

class PathGenerator{
public:
  virtual std::optional<Path> next() = 0;
};
