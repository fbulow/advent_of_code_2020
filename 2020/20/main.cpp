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

void transpose(auto &data)
{
  for(size_t row=0;row<(data.size()-1);row++)
    for(size_t column=row+1;column<data[row].size();column++)
      swap(data[row][column], data[column][row]);
}

class Tile 
{
  
public:
  I nr;
  vector<string> data;
  Tile(vector<string> const & inputData)
    :data(next(inputData.begin()), inputData.end())
  {
    {
      istringstream cin(inputData[0]);
      string slask;
      cin>>slask>>nr;
      assert(slask=="Tile");
    }
  }

  vector<string> sides() const
  {return {top(), bottom(), left(), right()};}
  
  string top()    const {return data[0];}
  string bottom() const {return *data.rbegin();}
  string left()   const
  {
    string left;
    left.resize(data.size());
    transform(data.begin(),
	      data.end(),
	      left.begin(),
	      [](string const &s){return *s.begin();});
    return left;    
  }
    
  string right()  const
  {
    string right;
    right.resize(data.size());
    transform(data.begin(),
	      data.end(),
	      right.begin(),
	      [](string const &s){return *s.rbegin();});
    return right;
  }
  
  Tile& flip()  // Top to bottom
  {
    reverse(data.begin(), data.end());
    return *this;
  }

  Tile& transpose()
  {
    ::transpose(data);
    return *this;
  }
  
  void rotate() //Counter clockwise;
  {
    transpose();
    flip();
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

  auto findTile(I nr)
  {
    return find_if(data.begin(),
		    data.end(),
		    [nr](auto &t){return t.nr==nr;});
  }

  optional<Tile> getTile(I nr)
  {
    auto x = findTile(nr);
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
  int row;
  int column;

  Coord up()    const { return{row-1, column};}
  Coord down()  const { return{row+1, column};}
  Coord left()  const { return{row, column-1};}
  Coord right() const { return{row, column+1};}
  
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
  auto a = encodeBinary(s);
  auto b = encodeBinary(r);
  assert(a!=b); //No palindrome.
  return max(a,b);
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

struct Requirement:Sides<string>
{
  bool match(Tile const &t) const
  {
    if (not top.empty() and top!=t.top())
      return false;
    if (not bottom.empty() and bottom!=t.bottom())
      return false;
    if (not left.empty() and left!=t.left())
      return false;
    if (not right.empty() and right!=t.right())
      return false;


    return true;
  }
};
  
#include"puzzle.cpp"
