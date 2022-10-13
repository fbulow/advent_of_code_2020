#pragma once
#include<cassert>
#include<ostream>

using namespace std;

struct Move
{
  unsigned int from;
  unsigned int to;
  Move(unsigned int from, unsigned int  to)
    :from(from)
    ,to(to)
  {
    assert(from<11);
    assert(to<11);
  }

  unsigned int distance() const;
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

inline
ostream& operator<<(ostream& out, Move const &m)
{
  out<<"Move{"<<m.from<<", "<<m.to<<"}";
  return out;
}
