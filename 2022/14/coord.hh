#pragma once

#include<array>

using namespace std;

class Coord : public array<int,2>
{
public:
  Coord(int a, int b)
    :array<int,2>{a,b}
  {}
  int x() const {return (*this)[0];}
  int y() const {return (*this)[1];}
};
