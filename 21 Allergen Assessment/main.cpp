#include <fstream>
#include <string>
#include <vector>
// #include <cmath>
// #include <iostream>
// #include <limits>
#include <numeric>
// #include <cassert>
#include<list>
#include<deque>
#include <initializer_list>
#include <functional>
#include <boost/algorithm/string.hpp> 

using namespace std;

using I = unsigned long int;

struct Allergens :set<string>
{
  Allergens(initializer_list<string> &&x)
    :set<string>(move(x))
  {}
  
  Allergens(string const &s)
  {
    string commaSeparated = [&s](){//evaluated immediately
      string x=s.substr(s.find("(contains")+"(contains"s.size()+1);
      return x.substr(0,x.size()-1);
    }();

    deque<string> untrimmed;
    boost::split(untrimmed, commaSeparated, [](auto x){return x==',';});
    for(auto x:untrimmed)
      {
        boost::trim(x);
        insert(x);
      }
    
  }
};
using Ingredients = set<string>;



class Food{
  Allergens a;

public:
  Food(string const &s)
    :a(s)
  {}

  Allergens allergens() const
  {
    return a;
  }
};


bool operator==(set<string> const &a, set<string> const &b)
{
  for(auto &x:a)
    if(not b.contains(x))
      return false;
  for(auto &x:b)
    if(not a.contains(x))
      return false;
  return true;
}
