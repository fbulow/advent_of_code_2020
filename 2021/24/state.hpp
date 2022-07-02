#pragma once
#include<array>

using Int = long long int;

class Instruction;

class State
{
  std::array<Int, 4> s{0,0,0,0};
public:
  Int w() const {return s[0];}
  Int x() const {return 0;}
  Int y() const {return 0;}
  Int z() const {return 0;}  

  void apply(Instruction const&);
};
