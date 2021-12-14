#include<iostream>
#include<fstream>
#include<functional>
#include<numeric>
#include<algorithm>
#include<optional>
#include<cassert>
#include<memory>
#include"strong_type.hpp"
#include<set>
#include<map>

using namespace std;

using Data = vector<string>;
Data input(istream& cin)
{
  Data ret;
  string s;
  cin>>s;
  while(not cin.eof())
    {
      ret.push_back(s);
      cin>>s;
    }
  return ret;
}


class Topology{
  map<string, set<string>> d;
public:
  void operator<<(string s)
  {
    string a(s.begin(), find(s.begin(), s.end(), '-'));
    string b(next(find(s.begin(), s.end(), '-')), s.end());
    d[a].insert(b);
    d[b].insert(a);
  }
  set<string> operator[](string s) const
  {
    return d.find(s)->second;
  }
};

bool isSmall(string const &s)
{
  char c = *s.begin();
  return (c>='a') and (c<='z');
}

class Path{
  vector<string> d;
public:
  bool empty() const
  {
    return d.empty();
  }
  Path operator+(string const &s) const
  {
    Path ret(*this);
    ret.d.push_back(s);
    return ret;
  }
  string location() const
  {
    return *prev(d.end());
  }
  bool contains(string const &s) const
  {
    if (isSmall(s))
      return find(d.cbegin(),
                  d.cend(),
                  s) != d.cend();
    else
      return false;
  }
};

unsigned int travel(Topology const &t,
                    Path p,
                    string const &next,
                    bool goldenTicket = false)
{
  if(next == "start" and not p.empty())
    return 0;
  
  if(p.contains(next))
    {
      if(goldenTicket)
        goldenTicket=false;
      else
        return 0;
    }

  if(next=="end")
    return 1;
  else
    {
      auto new_path = p+next;
      auto nxt = t[next];
      return accumulate(nxt.begin(),
                        nxt.end(),
                        0,
                        [t, new_path, goldenTicket]
                        (unsigned int summa, string s) -> unsigned int
                        {
                          return summa+travel(t, new_path, s, goldenTicket);
                        });
    }
}


auto solution_a(Data const &in)
{
  Topology topology;
  for(auto s:in)
    topology<<s;
  return travel(topology, Path(), "start");
}

auto solution_b(Data in)
{
  Topology topology;
  for(auto s:in)
    topology<<s;
  return travel(topology, Path(), "start", true);
}
