#include <algorithm>
#include <fstream>
#include <numeric>
#include <sstream>
#include <string>
#include <set>
#include <map>
#include <cassert>
#include <vector>
using namespace std;


constexpr size_t Left  = 0;
constexpr size_t Right = 1;


struct Navigation
{
  string s;
  int pos{0};

  int nxt()
  {
    pos%=s.size();
    switch(s[pos++])
      {
      case 'L':	return Left;
      case 'R':	return Right;
      }
    assert(false);
  }
};

string getPos(string const &s, size_t i)
{
  switch(i)
    {
    case 0:
      return s.substr(0,3);
    case 1:
      return s.substr(7,3);
    case 2:
      return s.substr(12,3);
    }
  assert(false);
}

struct Input
{
  Navigation n;
  map<string, vector<string>> loc;

  Input(istream && in)
  {
    string s;
    
    getline(in, s);
    n = Navigation{s};

    getline(in, s);
    assert(s.empty());


    while(getline(in, s))
      loc[getPos(s,0)] = {getPos(s,1), getPos(s,2)};
  }
  auto solA() 
  {
    int ret{0};
    string pos = "AAA";
    while(pos!="ZZZ")
      {
	pos = loc[pos][n.nxt()];
	ret++;
      }
    return ret;
  }

  auto solB() 
  {
    long long unsigned ret{0};
    set<string> pos;
    for(auto const &x: loc)
      if(x.first[2] == 'A')
	pos.insert(x.first);
    
    while(any_of(pos.begin(),
		 pos.end(),
		 [](string const &p)
		 {
		   return p[2] != 'Z';
		 }))
      {
	set<string> tmp;
	auto dir = n.nxt();
	for(auto const&p: pos)
	  tmp.insert(loc[p][dir]);
	pos = move(tmp);
	ret++;
      }
    return ret;
  }
};
