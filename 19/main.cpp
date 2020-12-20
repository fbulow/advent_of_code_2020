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
	auto end = find(str.begin(), str.end(), '|');
	string s(next(find(str.begin(), str.end(), ':')),
		 end);
	cout<<s<<endl;
	istringstream cin(s);
	I n;
	while(cin>>n)
	    left.push_back(n);
	
      }
  }
  
  bool known() const
  {
    return not str.empty();
  }
};
