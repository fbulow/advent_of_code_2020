#pragma once
#include<string>
#include<vector>
#include"enums.hh"

using namespace std;

using Arg = char;

class Instruction{

public:
  Command cmd;
  Arg a{'\0'};
  Arg b{'\0'};
  
  
  static unsigned int nArg(Command c);
};


istream& operator>>(istream& in, Instruction &i);
istream& operator>>(istream& in, vector<Instruction> &v);
