#pragma once
#include "range.hh"

struct Cube
{
  Range x;
  Range y;
  Range z;

  long size() const;

};
