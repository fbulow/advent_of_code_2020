#pragma once
#include<string>
#include<vector>
#include"enums.hh"
#include<variant>
#include"int.hh"

using namespace std;

using Arg = char;

class Instruction{

public:
  Command cmd;
  Arg a{'\0'};
  std::variant<std::monostate,char,Int> b;
  
  
  static unsigned int nArg(Command c);
};


istream& operator>>(istream& in, Instruction &i);
istream& operator>>(istream& in, vector<Instruction> &v);
