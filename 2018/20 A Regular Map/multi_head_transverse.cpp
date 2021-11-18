#include "multi_head_transverse.hpp"
#include <iterator>
#include "position.hpp"
#include <queue>
#include <set>
#include <iostream>
#include "fast_forward.hpp"
using namespace std;

void step(auto it, auto end, Position const & p, auto &log, auto &already_visited)
{
  if(already_visited({distance(it, end), p}))
    return;
  
  auto stp = [end, log, &already_visited](auto it, Position const & p)
  {
    return step(it, end, p, log, already_visited);
  };
  
  switch(*it)
    {
    case 'N':
    case 'S':
    case 'W':
    case 'E':
      {
        auto p_plus = p.step(*it);
        log(p, p_plus);
        return stp(next(it), p_plus);
      }
    case ')':
    case '^':
      return stp(next(it), p);
    case '$':
      return;
    case '|':
      return stp(to_closing(it, end),  p);
    case '(':
      auto nxt = to_closing_or_branch(it, end);
      stp(next(it),  p);
      while('|'==*nxt)
        {
          stp(next(nxt),  p);
          nxt = to_closing_or_branch(nxt, end);
        }
      assert(')'==*nxt);
      return stp(next(nxt), p);
    }
}


using PointAndMap = tuple<long int, Position>;

Doors multi_head_transverse(string const &s)
{
  Doors ret;
  auto act = [&ret](Position a, Position b)
       {
         ret.push(a,b);
       };
  set<PointAndMap> v;
  auto already_visited = [&v](PointAndMap const & pam)
  {
    if (v.contains(pam))
      return true;
    else
      {
        v.insert(pam);
        return false;
      }
  };
  
  step(s.begin(), s.end(), {0,0},
       act, already_visited);
  return ret;
}
