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

vector<Pos> theRightPath(string_view a, string_view b, Pos p)
{
  if(a.end()==find(a.begin(), a.end(), p))
    return {b.begin(), b.end()};
  return {a.begin(), a.end()};
}

Paths pathsFrom(Amphipod a)
{
  switch(a)
    {
    case 'A':
      return {"b710", "b723456"};
    case 'B':
      return {"c8210", "c83456"};
    case 'C':
      return {"d93210", "d9456"};
    case 'D':
      return {"ea43210", "ea56"};
    default:
      assert(false);
      return {"",""};
    }
}  

vector<Pos> findPath(Amphipod a, Pos p)
{
  auto paths = pathsFrom(a);
  return theRightPath(paths.left, paths.right, p);
}

Amphipod amphipodHome(Pos p)
{
  switch(p)
    {
    case 'b':
    case '7':
      return 'A';
    case 'c':
    case '8':
      return 'B';
    case '9':
    case 'd':
      return 'C';
    case 'a':
    case 'e':
      return 'D';
    default:
      assert(false);
      return ' ';
    }
}

vector<Move> Board::moves(Pos c) const
{
  auto const amphipod = get(c);
  if(amphipod==' ')
    return {};

  if(hallway(c))
    return movesFromHallway(c);
  else
    {
      if(amphipodHome(c) == amphipod)
	return {}; //case of amphipod starting in top position in the
		   //right room with lower positon taken by other type
		   //is not relevant to input data or example

      auto toHallway = [this](vector<Move> &ret, Pos c, string_view left)
      {
	auto start = next(left.begin(), 2);
	copy(start,
	     find_if(start,
		     left.end(),
		     [this](Pos c)
		     {
		       return ' '!=get(c);
		     }),
	     back_inserter(ret));
      };

      vector<Move> ret;
      ret.reserve(7);
      auto paths = pathsFrom(amphipodHome(c));
      toHallway(ret, c, paths.left);
      toHallway(ret, c, paths.right);
      return ret;
   }
}


vector<Move> Board::movesFromHallway(Pos c)const
{
  auto const amphipod = get(c);
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


bool Board::done() const 
{
  //#############
  //#01 2 3 4 56#
  //###7#8#9#a###
  //  #b#c#d#e#
  //  #########
  return
    ((*this)['7']=='A') 
    and ((*this)['b']=='A') 
    and ((*this)['8']=='B') 
    and ((*this)['c']=='B') 
    and ((*this)['9']=='C') 
    and ((*this)['d']=='C') 
    and ((*this)['a']=='D') 
    and ((*this)['e']=='D')
    ;
}

Board::Board(string_view s)
  {
    //#############
    //#01 2 3 4 56#
    //###7#8#9#a###
    //  #b#c#d#e#
    //  #########
    //
    // b=10, c=11, d=12, e=13

    size_t i{0};
    data[0] = s[14];
    data[1] = s[15];
    data[2] = s[17];
    data[3] = s[19];
    data[4] = s[21];
    data[5] = s[23];
    data[6] = s[24];
    data[7] = s[29];
    data[8] = s[31];
    data[9] = s[33];
    data[10] = s[35]; //a
    data[11] = s[42]; //b
    data[12] = s[44]; //c
    data[13] = s[46]; //d
    data[14] = s[48]; //d

    transform(data.begin(), data.end(),
	      data.begin(), [](auto a){if(a=='.') return ' '; else return a;});
    
  }


#define BODY					\
  {						\
    if((i>='0') and (i<='9'))			\
      return data[i-'0'];			\
    else					\
      return data[10+(i-'a')];			\
  }						\

char& Board::operator[](char i)
BODY
  
char Board::operator[](char i) const
BODY

