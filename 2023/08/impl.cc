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

using Int = long long;

constexpr size_t Left  = 0;
constexpr size_t Right = 1;

struct Navigation
{
  string s;
  Int pos{0};

  Int nxt()
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
    Int ret{0};
    string pos = "AAA";
    while(pos!="ZZZ")
      {
	pos = loc[pos][n.nxt()];
	ret++;
      }
    return ret;
  }

  auto solBnaive() 
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


struct Seq
{
  Int offset;
  Int period; //Add this to get to the next time when it is "true" ;-)

  static Seq alwaysTrue()
  {return {0, 1};}

  Seq(Int firstTime, Int secondTime)
    :offset(firstTime)
    ,period(secondTime - firstTime) 
  {}
  
  Seq merge(Seq other) const
  {
     
    
    other.period*=period;

    k*x + m = i*y + n

      0 + m%k = (i*y)%k + n%k

      (m-n)%k = (i*y)%k
      
      
    auto p = other.offset 
    return other;
  }
};



/*
Int solveB(vector<string> starts,
       Navigation const &n,
       map<string, vector<string>> const &loc)
{
  vector<Sequence> s{Sequence::alwaysTrue()};
  
  for(auto const &start:starts)
    {
      vector<Sequence> tmp;
      for(auto const &newSeq : Sequences(start,n,loc))
	{
	  for(auto const &oldSeq :s)
	    tmp.emplace_back(newSeq.merege(oldSeq));
	}
      s = tmp;
    }

  return min_element(s.begin(),
		     s.end(),
		     [](Sequence const &s)
		     {
		       return s.offset;
		     })
}


struct SolB:Input
{
  SolB(Input&& inp)
    :Input(move(inp))
  {
    
  }

  vector<string> startPositions() const
  {
    //TODO
  }

  auto operator()()
  {
    return solveB(startPositions(), n, loc);
  }
}

/**/
