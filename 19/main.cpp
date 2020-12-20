#include <fstream>
#include <string>
#include <vector>
#include <regex>
// #include <cmath>
#include <iostream>
#include <sstream>
// #include <limits>
#include <numeric>
// #include <cassert>
#include<list>
using namespace std;

using I = long long int;

void getBranchValues(vector<int> &target, auto begin, auto end)
{
  if(begin==end) return;
  string s(next(begin),
	   end);
  istringstream cin(s);
  I n;
  while(cin>>n)
    target.push_back(n);
}

I getIndex(string const &s)
{
  istringstream cin(s.substr(0, s.find(":")));
  I ret;
  cin>>ret;
  return ret;
}

class Rule
{
public:
  string str;
  vector<int> left;
  vector<int> right;
  Rule(string str)
  {
    auto i = find(str.begin(), str.end(), '"');
    if(i!=str.end())
      this->str = {next(i), find(next(i), str.end(), '"')};
    else
      {
	auto pipeOrEnd = find(str.begin(), str.end(), '|');
	getBranchValues(left,
			find(str.begin(), str.end(), ':'),
			pipeOrEnd);

	getBranchValues(right,
			pipeOrEnd,
			str.end());
      }
  }
  
  bool known() const
  {
    return not str.empty();
  }
};

class RegexBuilder{
  map<I, Rule> data;
public:
  RegexBuilder(vector<string> vs)
  {
    for(string &s: vs)
      data.emplace(getIndex(s), Rule(s));
  }
  string get(I index)
  {
    Rule &r = find_if(data.begin(),
		      data.end(),
		      [index](auto &x)
		      {
			return x.first == index;
		      })->second;

    if(r.known())
      return r.str;
    else
      {
	string ret;
	if(0 == r.right.size())
	    for(auto i:r.left)
	      ret+=get(i);
	else
	  {
	    ret+='(';
	    for(auto i:r.left)
	      ret+=get(i);
	    ret+="|";
	    for(auto i:r.right)
	      ret+=get(i);
	    ret+=')';
	  }
	r.str = ret;//cache
	return r.str;
      }
  }
};

regex getRegexpA(string filename)
{
  vector<string> data;
  string line = "slask";
  ifstream cin(filename);
  while((not line.empty()) and getline(cin, line))
    data.push_back(line);
  
  RegexBuilder sut(data);
  return regex(sut.get(0));
}

I solveA(string filename)
{
  auto re = getRegexpA(filename);
  ifstream cin(filename);

  string line;
  I count = 0;
  while(getline(cin, line))
    if (regex_match(line, re))
      count++;

  return count;
  
}
