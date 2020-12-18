#include <fstream>
#include <string>
#include <vector>
// #include <cmath>
// #include <iostream>
// #include <limits>
#include <numeric>
// #include <cassert>
#include<list>
using namespace std;

using I = int;

struct Machine{
  I memory{0};
  char op{'b'};

  void push(string str)
  {
    if(op=='b')//beginning
      {
	assert(0==memory);
	memory = stoi(str);
	op=' ';
	return;
      }
    else if(op==' ')
      {
	assert( (str=="+") or (str=="*") );
	op = str[0];
      }
    else if('+' == op)
      {
	memory+=stoi(str);
	op=' ';
      }
    else if('*' == op)
      {
	memory*=stoi(str);
	op=' ';
      }
  }
};



I eval(string const & str)
{
  Machine m;
  istringstream cin(str);
  string cmd;
  cin>>cmd;
  while(not cin.eof())
    {
      m.push(cmd);
      cin>>cmd;
    }
  if(not cmd.empty())
    m.push(cmd);
  return m.memory;
}
