#include<cmath>
#include<limits>
bool noMoreThanTwoTilesLinked(map<Key, set<I>> const &edgeMatch)
{
  return all_of(edgeMatch.begin(), edgeMatch.end(),
                [](auto &x){return x.second.size()<3;});
}

struct PuzzleSize{
  int rowMax = numeric_limits<int>::min();
  int rowMin = numeric_limits<int>::max();
  int colMax = numeric_limits<int>::min();
  int colMin = numeric_limits<int>::max();
  void add(Coord c)
  {
    if(rowMin > c.row    ) rowMin = c.row;
    if(colMin > c.column ) colMin = c.column;
    if(rowMax < c.row    ) rowMax = c.row;
    if(colMax < c.column ) colMax = c.column;
  }
  
  bool valid() const
  {
    return  (rowMin < rowMax) and (colMin < colMax);
  }
};

struct Table 
{
  PuzzleSize puzzleSize;
  int rowMax() const
  {assert(puzzleSize.valid()); return puzzleSize.rowMax;}
  int rowMin() const
  {assert(puzzleSize.valid()); return puzzleSize.rowMin;}
  int colMax() const
  {assert(puzzleSize.valid()); return puzzleSize.colMax;}
  int colMin() const
  {assert(puzzleSize.valid()); return puzzleSize.colMin;}
  
  map<Coord, Tile> data;
  auto begin() const {return data.begin();}
  auto end() const {return data.end();}
  auto find(Coord c) const {return data.find(c);}
  auto insert(pair<Coord, Tile> d)
  {
    puzzleSize.add(d.first);
    return data.emplace(move(d));}
  auto size() const {return data.size();}
  
};
using Collage = vector<string>;

string getRow(Table const &table, int row)
{
  string ret;
  auto r=table|views::transform([](auto x){return x.first.row;});
  set<int> all_rows{r.begin(), r.end()};
  
  auto firstRow = *next(all_rows.begin(), row/8);
  auto cols=table|views::transform([](auto x){return x.first.column;});
  
  for(auto column = *min_element(cols.begin(), cols.end());
      column <=  *max_element(cols.begin(), cols.end());
      column++)
    {
      auto s = table.find(Coord{firstRow, column})->second.data[row%8+1];
      ret += s.substr(1,s.size()-2);
    }
  return ret;
}




struct Puzzle
{
  Pile pile;
  map<Key, set<I>> edgeMatch;
  Table table;

  Puzzle(string filename)
    :pile(filename)
  {
    for(auto t:pile)
      for(auto s:t.sides())
        edgeMatch[bigKey(s)].insert(t.nr);
    
    for(auto it = edgeMatch.begin(); it != edgeMatch.end(); ) {
      if(it->second.size() != 2)
        it = edgeMatch.erase(it);
      else
        ++it;
    }
  }
  
  Requirement getRequirements(Coord c)
  {
    Requirement ret;
    {
      auto x=get(c.up());
      if(x) ret.top = x.value().bottom();
    }
    {
      auto x=get(c.down());
      if(x) ret.bottom = x.value().top();
    }
    {
      auto x=get(c.left());
      if(x) ret.left = x.value().right();
    }
    {
      auto x=get(c.right());
      if(x) ret.right = x.value().left();
    }
      
    return ret;

  }

  optional<Tile> get(Coord c)
  {
    auto it = find_if(table.begin(),
                      table.end(),
                      [c](auto const &x){return x.first==c;});
    if(it == table.end()) return {};
    
    return it->second;
  }

      
  void put(Tile const &t, Coord c)
  {
    table.insert({c,t});
  }

  void removeFromPile(auto findPileIterator)
  {
    auto nr = findPileIterator->nr;
    pile.erase(findPileIterator);

    for(auto &x:edgeMatch)
      x.second.erase(nr);
  }
  

  void place(vector<Tile>::iterator tile, Coord const &c)
  {
    if(tile==pile.end())
      return;
    auto req=getRequirements(c);
    auto positionCounter=0;
    while(not req.match(*tile))
      {
        if(positionCounter==10)
          throw exception{};
        else if(positionCounter%2==0)
          tile->flip();
        else
          tile->transpose();
        positionCounter++;
      }
    table.insert({c, *tile});
    removeFromPile(tile);
  }
  void place(I i, Coord const &c)
  {
    return place(pile.findTile(i), c);

  }
  
  optional<I> whatFitsHere(Coord c)
  {
    assert(noMoreThanTwoTilesLinked(edgeMatch));

    auto sides = getRequirements(c).sides();
    for(auto x:sides)
      if(not x.empty())
        {
          auto mapElement = edgeMatch.find(bigKey(x));
          if(mapElement==edgeMatch.end())
            return {};
          auto candidates  = mapElement->second;
          if(candidates.size()==0)
            return {};
          else if(candidates.size()>=3)
            {
              cout<<x<<endl<<"size "<<candidates.size()<<endl;
              for(auto x:candidates)
                cout<< x<<endl;
              assert(false);
            }              
          else if(candidates.size()!=1)
            assert(false);
          return *candidates.begin();
        }
    return {};
  }

  void solve(Coord c)
  {
    if(pile.size()==0)
      return; //done
    auto optNr = whatFitsHere(c);
    if(not optNr) return;
    auto nr = optNr.value();
    place(nr, c);
    solve(c.up());
    solve(c.down());
    solve(c.left());
    solve(c.right());
  }

  void solve()
  {
    Coord c={0,0};
    place(pile.begin()->nr, c);
    solve(c.up());
    solve(c.down());
    solve(c.left());
    solve(c.right());
  }

  int sideSize() const
  {
    return 8 * sqrt(table.size());
  }

  vector<string> collage() const
  {
    vector<string> ret;
    ret.reserve(sideSize());
    for(int row=0; row<sideSize(); row++)
      ret.push_back(getRow(table, row));
    return ret;
  }

    
};

ostream& operator<<(ostream &cout, Coord const &c)
{
  cout<<"{"<<c.row<<", "<<c.column<<"}";
  return cout;
}
ostream& operator<<(ostream &cout, Puzzle const &p)
{
  for(auto row = p.table.rowMin(); row<=p.table.rowMax(); row++)
    {
      for(auto column = p.table.colMin(); column<=p.table.colMax(); column++)
        {
          auto it = p.table.find({row, column});
          if(it==p.table.end())
            cout<<"    ";
          else
            cout<<it->second.nr;
          cout<<"  ";
        }
      cout<<endl;
    }
  return cout;
}

string getRow(Puzzle const &puzzle, int row)
{
  return getRow(puzzle.table, row);
}
