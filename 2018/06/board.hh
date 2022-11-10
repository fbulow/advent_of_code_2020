#pragma once
#include<vector>
#include<tuple>
#include<algorithm>
#include"coord.hh"
#include<ranges>
using namespace std;


struct Range{
  int min;
  int max;
  int length()const {return 1+max-min;}
};

#include<ranges>
struct Box{
  Box(vector<Coord> const & v);
  Range row;
  Range col;  

  int height() const{ return row.length();}
  int width()  const{ return col.length();}
};

class Board{
  vector<vector<int>> data_;
public:
  Board(Coords const &points);
  Board(Box const & box, Coords const &points);

  bool thereAreUnknowns() const;
  
  static constexpr int free={-1};
  static constexpr int border={-2}; // between regions

  int& get(int row, int col);
  int get(int row, int col) const;
};
