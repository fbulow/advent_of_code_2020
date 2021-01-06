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

using I = long long int;



struct Machine{
  I memory{0};
  char op{'b'};

  void push(string str)
  {
    if(op=='b')//beginning
      {
	assert(0==memory);
	memory = stoll(str);
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
	memory+=stoll(str);
	op=' ';
      }
    else if('*' == op)
      {
	memory*=stoll(str);
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


bool expandedParenthesis(string &str, auto evaluator)
{
  static regex const re("\\([^)(]*\\)");
  smatch m;
  bool ret{false};
  while(regex_search(str, m, re))
    {
      ret=true;
      string s = m[0];
      s = {next(s.begin()), prev(s.end())};
      str.replace(m.position(0),
		  m.length(0),
		  to_string(evaluator(s)));
    }
  return ret;
}

I eval(string str)
{
  while(expandedParenthesis(str, evalSimple))
    {}
  return evalSimple(str);
}

I solve(string filename, auto evaluator)
{
  ifstream in(filename);
  list<string> data;
  string line;
  assert(in.is_open());
  while(getline(in, line))
    data.push_back(line);
  return accumulate(data.begin(),
		    data.end(),
		    I{0},
		    [evaluator](auto sum, string const &s)
		    {
		      try{
			return sum+evaluator(s);
		      }
		      catch(exception const &ex){
			cout<<"Error "<<s<<endl;
			throw ex;
		      }
		    });
}

I solveA(string filename)
{
  return solve(filename, eval);
}

bool performAdditions(string &str)
{
  static regex const re("[0-9]+ \\+ [0-9]+");
  smatch m;
  bool ret{false};
  while(regex_search(str, m, re))
    {
      ret=true;
      string s = m[0];
      //      cout<<endl<<str<<endl;
      str.replace(m.position(0),
		  m.length(0),
		  to_string(evalSimple(s)));
      //      cout<<str<<endl<<endl;

    }
  return ret;
}


I evalB(string str)
{
  cout<<str<<endl;
  while(expandedParenthesis(str, evalB))
    {}//cout<<str<<endl;
  while(performAdditions(str))
    {}//cout<<str<<endl;

  return evalSimple(str);
}

I solveB(string filename)
{
  return solve(filename, evalB);
}
