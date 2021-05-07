#pragma once

#include<vector> 
#include <string>
#include <cassert>
#include <iostream>
#include <set>
//#include "distance_table.hpp" 
using namespace std;

struct Destination
{
  char name;
  unsigned int steps;
};

inline bool isKey(char c, char start_at='@')
{
  if(start_at==c)
    return false;
  else
    return (c>='a') and (c<='z');
}

inline bool isLock(char c)
{
  return (c>='A') and (c<='Z');
}

class Vault;
set<Destination> destinations(Vault v, char start_at='@');

class Vault{
  vector<string> map;
  friend ostream& operator<<(ostream& out, Vault const &v);
public:
  Vault(vector<string> map);
  Vault(Vault const &other, char c);

  
  set<Destination> destinations(char start_at='@') const
  {return ::destinations(*this, start_at);}

  bool no_snabela(char start_at='@')
  {
    return none_of(map.begin(),
                  map.end(),
                  [start_at](auto const & x)
                  {
                    return x.find(start_at)!=std::string::npos;
                  });
  }

  char& get(int row, int col)
  {
    static char border = '#';
    
    if ((row<0)
        or (row>=map.size())
        or (col<0)
        or (col>=map[0].size()))
      return border;
    else
      return map[row][col];
  }

  bool operator==(Vault const & other)
  {
    if (map.size()!=other.map.size())
      return false;
    for(int i=0;i<map.size();i++)
      {
        if(map[i]!=other.map[i])
          return false;
      }
    return true;
  }
  
  set<char> step(char start_at='@')
  {
    set<char> ret;
    auto act =
      [&ret, start_at](char &c)
      {
        if(c=='.')
          c='+';
        else if(isKey(c))
          {
            ret.insert(c);
            c='#';
          }
      };
    
    for(int i=0;i<map.size();i++)
      for(int j=0;j<map[i].size();j++)
        if(get(i,j)==start_at)
          {
            get(i,j)='#';
            act(get(i-1,j));
            act(get(i+1,j));
            act(get(i,  j-1));
            act(get(i,  j+1));
          }

    for(int i=0;i<map.size();i++)
      for(int j=0;j<map[i].size();j++)
        if(get(i,j)=='+')
          get(i,j)=start_at;
    return ret;
  }

};



ostream& operator<<(ostream& out, Vault const &v);
bool operator<(Destination const & lhs, Destination const &rhs);

bool operator==(Destination const & lhs, Destination const &rhs);

unsigned int minimal_steps(Vault const&v, int steps =0);
