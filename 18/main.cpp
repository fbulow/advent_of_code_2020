#include <fstream>
#include <string>
#include <vector>
#include <regex>
// #include <cmath>
// #include <iostream>
// #include <limits>
#include <numeric>
// #include <cassert>
#include<list>
using namespace std;

using I = long int;

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


I evalSimple(string const & str)
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



I eval(string str)
{
  regex re("\\([^)(]*\\)");
  smatch m;
  while(regex_search(str, m, re))
    {
      string s = m[0];
      s = {next(s.begin()), prev(s.end())};
      str.replace(m.position(0),
		  m.length(0),
		  to_string(evalSimple(s)));
    }
  return evalSimple(str);
}

I solveA(string filename)
{
  ifstream in(INPUT);
  list<string> data;
  string line;
  assert(in.is_open());
  while(getline(in, line))
    //    if(not line.empty())
      data.push_back(line);
  cout<<"Size   "<< data.size()<<endl;
  cout<<"begin  "<< *data.begin()<<endl;
  cout<<"rbegin "<< *data.rbegin()<<endl;
  return accumulate(data.begin(),
		    data.end(),
		    I{0},
		    [](auto sum, string const &s)
		    {
		      return sum+eval(s);
		    });
}
