#pragma once
#include<cassert>

struct Move
{
  unsigned int from;
  unsigned int to;
  Move(unsigned int from, unsigned int  to)
    :from(from)
    ,to(to)
  {
    assert(from<to);
    assert(to<11);
  }
};

inline bool operator==(Move const &a, Move const &b)
{
  return (a.from==b.from) and (a.to==b.to);
}

namespace A{

  struct Move{
    unsigned int from{0};
    unsigned int to{1};

    ::Move get() const
    {
      return {from, to};
    }
    operator ::Move() const
    {
      return get();
    }
  };
};

