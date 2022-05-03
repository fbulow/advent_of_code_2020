#include "incl.hh"

bool hallway(Pos p)
{
  return p<'7';
}

array<char, 2> sideRooms(Amphipod a)
{
  switch(a)
    {
    case 'A':
      return {'7','b'};
    case 'B':
      return {'8','c'};
    case 'C':
      return {'9','d'};
    case 'D':
      return {'a','e'};
    }
  assert(false);
}

vector<Pos> findPath(Amphipod a, Pos p)
{
  string_view s;
  if(a == 'A')
    s="b710";
  else if (a=='C')
    s="d93210";
  return {s.begin(), s.end()};
}


vector<Move> Board::moves(Pos c) const
{
  auto const amphipod = get(c);
  if(amphipod==' ')
    return {};

  if(hallway(c))
    {
      auto p = [=]{
	auto p = findPath(amphipod, c);
	reverse(p.begin(), p.end());
	return p;}();
      auto start = find(p.begin(), p.end(),
			c);
      auto lastRoom = prev(p.end());

      if(not clearWay(*start, *prev(lastRoom)))
	return {};
      
      if ( any_of(next(start), lastRoom,
		  [this](auto it){
		    if( get(it)!=' ' )
		      return true;
		    else
		      return false;
		  }) )
	return {}; // path blocked
      else
	{
	  vector<Pos> ret;
	  if(' '==get(*lastRoom))
	    ret={*lastRoom};
	  else if(amphipod!=get(*lastRoom))
	    ret={};
	  else
	    ret={*prev(lastRoom)};
	  return ret;
	}
    }
}
