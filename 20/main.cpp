#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include <iostream>
#include <sstream>
#include <numeric>
#include<list>
#include<ranges>
using namespace std;

using I = unsigned int;

template<class T>
struct Sides{
  T top;    //left to right 
  T bottom; //left to right 
  T left;   //top to bottom
  T right;  //top to bottom

  vector<T> sides() const
  {
    return {top, bottom, left, right};
  }
};

class Tile : public Sides<string>
{
public:
  I nr;
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
  void flip()  // Top to bottom
  {
    reverse(begin(left), end(left));
    reverse(begin(right), end(right));
    swap(top, bottom);
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

struct Pile
{
  vector<Tile> data;
  Pile(string filename)
  {
    vector<string> data;
    ifstream in(filename);
    assert(in.is_open());
    string line;
    while(getline(in, line))
      data.push_back(line);

    auto a = data.begin();
    auto b = find(a, data.end(), "");
    while(b!=data.end())
      {
	this->data.emplace_back(Tile(vector<string>{a,b}));
	a=next(b);
	b=find(a,data.end(), "");
      }
  }
  size_t size() const
  {return data.size();}

  optional<Tile> getTile(I nr)
  {
    auto x= find_if(data.begin(),
		    data.end(),
		    [nr](auto &t){return t.nr==nr;});
    if(x==data.end())
      return {};
    else
      return {*x};
  }

  
  Tile const& operator[](size_t i) const
  {
    return data[i];
  }

  auto begin() const
  {
    return data.begin();
  }
  auto end() const
  {
    return data.end();
  }

  auto erase(auto iterator)
  {
    return data.erase(iterator);
  }
  
};

struct Coord{
  int column;
  int row;
  bool operator==(auto const &other) const
  {return (row==other.row) and (column == other.column);}
  
  bool operator<(auto const &other) const
  {
    if(column<other.column) return true;
    else if(column == other.column) return row < other.row;
    else return false;
  }
};

Coord up   (Coord c){ c.row-=1;	   return c;}
Coord down (Coord c){ c.row+=1;	   return c;}
Coord left (Coord c){ c.column-=1; return c;}
Coord right(Coord c){ c.column+=1; return c;}

void insertNear(set<Coord> &near, Coord const &c)
{
  near.emplace(up   (c));
  near.emplace(down (c));
  near.emplace(left (c));
  near.emplace(right(c));
}

int encodeBinary(string const &s)
{
  int sum=0;
  for(auto x:s)
    sum=2*sum+(('#'==x)?1:0);
  return sum;
}
  

using Key = unsigned int;

Key bigKey(string s)
{
  string r(s.rbegin(), s.rend());
  return max(encodeBinary(s), encodeBinary(r));
}

bool isCorner(Tile const &t, set<unsigned int> const& edges)
{
  auto s = t.sides();
  
  return 2==count_if(s.begin(),
		     s.end(),
		     [&edges](auto x){
		       return edges.contains(bigKey(x));
		     });;
}

set<Key> getEdges(Pile const &p)
{
  map<Key, int>    edgeCount;// edge, count;  
  for(Tile t: p)
    for(auto ts:t.sides())
	edgeCount[bigKey(ts)]++;
  
  auto x =edgeCount
    |views::filter([](auto &x){return x.second==1;})
    |views::transform([](auto &x){return x.first;});

  return set<Key>(x.begin(), x.end());
}



auto solveA(string filename)
{

  Pile p(filename);
  auto edges = getEdges(p);

  auto corners = p.data
    |views::filter([edges](auto tile){return isCorner(tile, edges);});

  
  return accumulate(corners.begin(),
		    corners.end(),
		    (unsigned long long int) 1,
		    [](unsigned long long int product, auto tile)
		    {
		      product*=tile.nr;
		      return product;
		    });
}    
