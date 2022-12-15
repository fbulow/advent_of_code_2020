#include "input.hh"

bool Input::canMoveFromTo(Coord from, Coord to) const
{

  auto heightIncrease =
    data[to.row()  ][to.col()  ]
    -
    data[from.row()][from.col()]
    ;

  return heightIncrease <=1;
}
