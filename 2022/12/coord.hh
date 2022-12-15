#pragma once

#include <tuple>
#include <vector>

#include "int_types.hh"
#include <cassert>

using namespace std;

class Input;

struct Coord : pair<Row, Column>
{
  Coord(Row r, Column c)
    :pair<Row, Column>(r,c)
  {}
  Row row()const;
  Row col()const;
  
  Coord up()	const;
  Coord down()	const;
  Coord left()	const;
  Coord right() const;

  vector<Coord> adjacent() const;
};
