#pragma once
#include "strong_type.hpp"
#include <set>
#include <sstream>
#include <map>
using namespace std;

using Row = strong::type<int, struct Row_, strong::ordered, strong::incrementable, strong::arithmetic>;
using Col = strong::type<int, struct Col_, strong::ordered, strong::incrementable, strong::arithmetic>;
using Coord = tuple<Row, Col>;

class Board;
class Key;
uint solutionA(Key k, Board b);
struct KeyIndex : strong::type<size_t, struct KeyIndex_, strong::regular, strong::arithmetic>
{
  KeyIndex(size_t v)
    :strong::type<size_t, struct KeyIndex_, strong::regular, strong::arithmetic>(v)
  {}
  KeyIndex(Coord const &coord, Board const &b);
};

class Key: array<bool, 512>
{
  friend istream& operator>>(istream &in, Key &k);
  friend ostream& operator<<(ostream& cout, Key const  & k);
  friend uint solutionA(Key k, Board b);
public:
  Key()=default;
  Key(string v);
  void invert();
  bool operator[](KeyIndex idx) const
  {
    return array<bool, 512>::operator[](value_of(idx));
  }
};

struct Board :  set<Coord>
{
  Board()=default;
  Board(string s);

  string str() const;
};

struct Accumulator : set<Coord>
{
  void poke(Coord q)
  {
    for(Row r{-1}; r<Row(2); r++)
      for(Col c{-1}; c<Col(2); c++)
        insert({
            r+get<Row>(q),
            c+get<Col>(q)
          });
  }
  //  bool contains(Coord c) const;
};


istream& operator>>(istream &in, Key &k);
istream& operator>>(istream& in, Board &b);

ostream& operator<<(ostream& out, Board const &b);
ostream& operator<<(ostream& cout, Key const  & k);

Board iteration(Key const& k, Board const&b);
