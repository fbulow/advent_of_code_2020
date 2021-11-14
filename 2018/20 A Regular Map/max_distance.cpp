#include "max_distance.hpp"
#include <set>
#include "position.hpp"

class Visited: set<Position>
{
  using Parent= set<Position>;
public:
  Visited(Parent&& p)
    :Parent(move(p))
  {}
  
  void insert(Position p)
  {Parent::insert(p);}
  bool contains(Position p)
  {return Parent::contains(p);}
};

class CurrentPos:public set<Position>
{
};

Distance max_distance(Visited v,
                          CurrentPos cp,
                          Doors d,
                          Distance dist
                          )
{
  CurrentPos next_current_pos; 
  for( auto x: cp )
    {
      v.insert(x);
      for(auto otherPos : d.pop(x))
        if(not v.contains(otherPos))
          next_current_pos.insert(otherPos);
    }
  if(next_current_pos.empty())
    return dist;
  else
    return max_distance(v,
                        next_current_pos,
                        d,
                        dist+Distance(1));
}

Distance max_distance(Doors const &d)
{
  return max_distance(Visited({}),
                      CurrentPos{{d.start_at()}},
                      Doors(d),
                      Distance(0));
}
