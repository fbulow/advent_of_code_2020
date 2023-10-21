#pragma once

#include<functional>
#include "path.hh"

class PathGenerator{
public:
  using Callback = std::function<void(Path const &)>;
  virtual
  void callWithEach(Callback&) = 0;
};

