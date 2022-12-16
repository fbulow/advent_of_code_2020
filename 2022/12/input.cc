#include "input.hh"

Input::Input(vector<string> data)
  :data(move(data))
{}

bool Input::canMoveFromTo(Coord from, Coord to) const
{

  auto heightIncrease =
    data[to.row()  ][to.col()  ]
    -
    data[from.row()][from.col()]
    ;

  return heightIncrease <=1;
}

vector<Coord> Input::adjacent(Coord c)
{
  vector<Coord> ret;
  for(Coord cc : c.adjacent())
    if(onBoard(cc))
      if(canMoveFromTo(c, cc))
	ret.push_back(cc);
  return ret;
}

bool Input::onBoard(Coord const & c)
{
  if(c.row() < data.size()) //Also false if row() is negative due to signed/unsigned arithmetics!
    if (c.col() < data[c.row()].size())
      return true;
  return false;
}

Coord Input::find(char c) const
{
  for(int row=0; row<data.size(); row++)
    {
      int col = data[row].find(c);
      if (col!=std::string::npos)
	return {row, col};
    }
  assert(("letter not found", false));
}
