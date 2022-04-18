#pragma once
#include"cube.hh"
#include<string>
#include<sstream>
#include<cassert>

using namespace std;

class Instruction
{
  bool turnOn_;
public:
  Cube cube;
  Instruction(string s) 
  {
    istringstream in(s);
    string word;
    in>>word;
    if(word=="on")
      turnOn_=true;
    else
      {
	turnOn_=false;
	assert(word=="off");
      }
    char c;
    in>>
      c>>c>>
      cube.x.min>>
      c>>c>>
      cube.x.max>>
    
      c>>c>>c>>
      cube.y.min>>
      c>>c>>
      cube.y.max>>

      c>>c>>c>>
      cube.z.min>>
      c>>c>>
      cube.z.max
      ;
  }
      
  bool turnOn() const;
};
