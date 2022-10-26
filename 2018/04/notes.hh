#pragma once
#include"note.hh"

class Notes{
  set<Note> data;
  friend istream& operator>>(istream& in, Notes &);
  public:
  void insert(Note const &n){data.insert(n);}
  auto cbegin() const
  {return data.cbegin();}
  auto cend() const
  {return data.cend();}
};

istream& operator>>(istream& in, Notes &n);
