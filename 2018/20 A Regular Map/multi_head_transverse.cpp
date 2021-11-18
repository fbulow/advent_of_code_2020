#include "multi_head_transverse.hpp"
#include <iterator>
#include "position.hpp"
#include <queue>
#include <set>
#include <iostream>
#include "fast_forward.hpp"
using namespace std;


void step(auto it, auto end, Position const & p, auto &log)
{
  auto stp = [end, log](auto it, Position const & p)
  {
    return step(it, end, p, log);
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

Doors multi_head_transverse(string const &s)
{
  Doors ret;
  auto act = [&ret](Position a, Position b)
       {
         ret.push(a,b);
       };
  step(s.begin(), s.end(), {0,0},
       act);
  return ret;
}
