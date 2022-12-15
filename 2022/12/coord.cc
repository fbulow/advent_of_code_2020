#include "coord.hh"

Coord Coord::up()	const {return {row()-1, col()};}
Coord Coord::down()	const {return {row()+1, col()};}
Coord Coord::left()	const {return {row(), col()-1};}
Coord Coord::right()	const {return {row(), col()+1};}

Row Coord::row()const
{return get<0>(*this);}
Row Coord::col()const
{return get<1>(*this);}

vector<Coord> Coord::adjacent() const
{
  return {up(), down(), left(), right()};
}
