#pragma once

template<class I = int>
struct Coord
{
  I row;
  I column;

  Coord<I> clockwise() const
  {
    return { column, -row };
  }
  Coord<I> antiClockwise()
  {
    return { -column, row };
  }

  void operator+=(Coord const & other)
  {
    row+=other.row;
    column+=other.column;
    
  }

  bool operator==(Coord const & other) const
  {
    return (row == other.row) and (column == other.column);
  }
  
  bool operator<(Coord const & other) const
  {
    if (row < other.row)
      return true;
    else if (row > other.row)
      return false;
    else
      return column<other.column;
  }
};

template<class I>
ostream& operator<<(ostream& out, Coord<I> const &c)
{
  out<<"{"<<c.row<<", ", c.column<<"}";
  return out;
}
