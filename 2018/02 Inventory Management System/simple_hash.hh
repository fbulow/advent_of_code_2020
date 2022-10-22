#pragma once
#include <array>
#include <string_view>
#include <map>
using namespace std;

struct SimpleHash{

  SimpleHash(string_view s)
  {
    map<char, unsigned int> count;
    for(auto c:s)
      count[c]++;
    doublet = 
      find_if(count.begin(),
	      count.end(),
	      [](auto const & v){return v.second==2;})!=count.end();
    triplet = 
      find_if(count.begin(),
	      count.end(),
	      [](auto const &v){return v.second==3;})!=count.end();
    
  }
  bool doublet;
  bool triplet;
};
