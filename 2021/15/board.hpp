#pragma once
#include<vector>

using namespace std;

struct Coord{
  int row;
  int col;
};

bool operator==(Coord const &lhs, Coord const &rhs)
{
  return
    (lhs.row==rhs.row) and
    (lhs.col==rhs.col) ;
}
bool operator!=(Coord const &lhs, Coord const &rhs)
{
  return not (lhs==rhs);
}

ostream& operator<<(ostream& cout, Coord const &c)
{
  cout<<"("<<c.row<<", "<<c.col<<")";
  return cout;
}


template<class T>
class Board{
protected:
  vector<vector<T>> d;
  bool onBoard(Coord c) const
  {
    return  (c.row>=0)
      and   (c.col>=0)
      and   (c.row<Nrows())
      and   (c.col<Ncols());
  }
  
public:
  T& operator[](Coord c)
  {
    return d[c.row][c.col];
  }
  T operator[](Coord c) const
  {
    return d[c.row][c.col];
  }
  size_t Nrows() const
  {return d.size();}

  size_t Ncols() const
  {
    return d[0].size();
  }

  vector<Coord> adjacent(Coord c) const
  {
    vector<Coord> ret;
    ret.reserve(4);

    for (Coord const & c : {Coord(c.row-1, c.col),
                            Coord(c.row+1, c.col),
                            Coord(c.row,   c.col-1),
                            Coord(c.row,   c.col+1)})
      if(onBoard(c))
        ret.push_back(c);
    return ret;
  }
  
};

