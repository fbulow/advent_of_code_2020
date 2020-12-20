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

class Tile{
public:
  I nr;
  string top;
  string bottom;
  string left;
  string right;

  Tile(vector<string> const & data)
  {
    {
      istringstream cin(data[0]);
      string slask;
      cin>>slask>>nr;
      assert(slask=="Tile");
    }
    top = data[1];
    bottom = *data.rbegin();
    left.resize(10);
    transform(next(data.begin()),
	      data.end(),
	      left.begin(),
	      [](string const &s){return *s.begin();});
    right.resize(10);
    transform(next(data.begin()),
	      data.end(),
	      right.begin(),
	      [](string const &s){return *s.rbegin();});
    
  }


  
};
