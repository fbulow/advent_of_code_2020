#pragma once

#include<vector> 
#include <string>
#include <cassert>
#include <iostream>
#include <set>

using namespace std;

struct Destination
{
  char name;
};

inline bool isKey(char c)
{
  return (c>='a') and (c<='z');
}

inline bool isLock(char c)
{
  return (c>='A') and (c<='Z');
}



class Vault{
  vector<string> map;
  friend ostream& operator<<(ostream& out, Vault const &v);
public:
  Vault(vector<string> map)
    :map{move(map)}
  {
    assert(all_of(next(this->map.begin()),
                  this->map.end(),
                  [N = this->map[0].size()](auto &x){return x.size()==N;}));

  }
  vector<Destination> destinations() const
  {return {Destination{'a'}};}

  bool no_snabela()
  {
    return none_of(map.begin(),
                  map.end(),
                  [](auto const & x)
                  {
                    return x.find("@")!=std::string::npos;
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
  
  set<char> step()
  {
    set<char> ret;
    auto act =
      [&ret](char &c)
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
        if(get(i,j)=='@')
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
          get(i,j)='@';
    return ret;
  }

};

set<Destination> options(Vault v);


ostream& operator<<(ostream& out, Vault const &v);
bool operator<(Destination const & lhs, Destination const &rhs);

bool operator==(Destination const & lhs, Destination const &rhs);
