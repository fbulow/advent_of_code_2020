#pragma once
#include <cassert>
#include "tile.hh"

class Amphipod : public Tile
{
public:
  Amphipod(char c)
    :Tile(c)
  {
    assert(c>='A');
    assert(c<='D');
  }
};


