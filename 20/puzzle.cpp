struct Puzzle
{
  Pile pile;
  map<Key, set<Tile>> edgeMatch;
  map<Coord, Tile> table;

  Puzzle(string filename)
    :pile(filename)
  {}
  
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
                      [c](auto x){return x.first==c;});
    if(it == table.end()) return {};
    
    return it->second;
  }

      
  void put(Tile const &t, Coord c)
  {
    table.insert({c,t});
  }

  void place(I i, Coord c)
  {
    auto it = pile.findTile(i);
    assert(it!=pile.end());
    Tile t=*it;
    auto req=getRequirements(c);
    auto positionCounter=0;
    while(not req.match(t))
      {
        if(positionCounter==10)
          throw exception{};
        else if(positionCounter%2==0)
          t.flip();
        else
          t.transpose();
        positionCounter++;
      }
    table.insert({c,*it});
    pile.erase(it);
  }

  
  optional<Tile> whatFitsHere(Coord c)
  {
    return {};
  }
  
};
