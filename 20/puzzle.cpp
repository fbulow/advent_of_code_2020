struct Puzzle
{
  Pile pile;
  map<Key, set<I>> edgeMatch;
  map<Coord, Tile> table;

  Puzzle(string filename)
    :pile(filename)
  {
    for(auto t:pile)
      for(auto s:t.sides())
        edgeMatch[bigKey(s)].insert(t.nr);
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
                      [c](auto x){return x.first==c;});
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

    auto it = find_if(edgeMatch.begin(),
                      edgeMatch.end(),
                      [nr](pair<Key, set<I>> const &x){return x.second.contains(nr);});
    assert(it!=edgeMatch.end());
    it->second.erase(nr);
    if(it->second.size()==0)
      edgeMatch.erase(it);
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
    removeFromPile(it);
  }
      
  
  optional<I> whatFitsHere(Coord c)
  {
    for(auto x:getRequirements(c).sides())
      if(not x.empty())
        {
          auto candidates = edgeMatch[bigKey(x)];
          assert(candidates.size()==1);
          return *candidates.begin();
        }
    return {};
  }
  
};
