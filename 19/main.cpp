#define _GLIBCXX_REGEX_STATE_LIMIT 10000000


#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include <iostream>
#include <sstream>
#include <numeric>
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
  virtual string get(I index)
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


template<class REGBUILD>
regex getRegexp(string filename)
{
  vector<string> data;
  string line = "slask";
  ifstream cin(filename);
  while((not line.empty()) and getline(cin, line))
    data.push_back(line);
  
  REGBUILD sut(data);
  return regex(sut.get(0));
}

regex getRegexpA(string filename)
{
  return getRegexp<RegexBuilder>(filename); 
}

template<class REGBUILD>
I solve(string filename)
{
  auto re = getRegexp<REGBUILD>(filename);
  ifstream cin(filename);

  string line;
  I count = 0;
  while(getline(cin, line))
    if (regex_match(line, re))
      count++;

  return count;  
}

I solveA(string filename)
{
  return solve<RegexBuilder>(filename);
}

string parseRuleEight(string fortyTwo)
{
  return "("+fortyTwo+")+";
}

string parseRuleEleven(string fortyTwo, string thirtyOne, int n)
{
  string ret = "(";
  string body = fortyTwo+thirtyOne;
  ret+=body;
  while(n-->0)
    {
      body = fortyTwo+body+thirtyOne;
      ret+="|"+body;
    }
  ret+=")";
  return ret;
}

class RegexBuilderB : public RegexBuilder
{
public:
  RegexBuilderB(vector<string> vs)
    :RegexBuilder(vs)
  {}
  string get(I index) override
  {
    switch(index)
      {
      case 8:
	return parseRuleEight(get(42));
      case 11:
	return parseRuleEleven(get(42), get(31),
			       40 // Max line length is 80 so 40 should be enough...
			       );
      default:
	return RegexBuilder::get(index);
      }
  }
};

I solveB(string filename)
{
  return solve<RegexBuilderB>(filename);
}
