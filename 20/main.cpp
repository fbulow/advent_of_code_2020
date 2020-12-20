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
  string top;    //left to right 
  string bottom; //left to right 
  string left;   //top to bottom
  string right;  //top to bottom

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
  void flip()  // flip left to right
  {
    reverse(begin(top), end(top));
    reverse(begin(bottom), end(bottom));
    swap(left, right);
  }
  void rotate() //Counter clockwise;
  {
    auto slask = top;
    top = right;

    right = bottom;
    reverse(begin(right), end(right));

    bottom = left;

    left = slask;
    reverse(begin(left), end(left));
    
  }

  
};
