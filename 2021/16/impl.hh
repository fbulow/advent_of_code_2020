#pragma once

#include<gtest/gtest.h>
#include<string>
#include<cassert>
#include<array>
#include<string_view>
#include<iterator>
#include<numeric>
#include<vector>

#include"infint.hh"

using namespace std;
using Uint = InfInt;
struct Hex:string{
};

struct Bin:string{
  Bin(Hex const &h);
  Bin(string const &h);
  operator Uint () const;
};

string expand(string const & in);

using Iterator = string::const_iterator;

Iterator nextPacket(Iterator pos);

Uint evalN(size_t n, Iterator begin);

Uint solutionA(Bin data);

Uint eval(Iterator pos, Iterator end);

template<class T>
Uint eval(T const &x)
{
  return eval(x.cbegin(), x.cend());
}

Uint readNumberN(size_t N, Iterator &pos);
Uint evalNext(Iterator& pos);

class Parser
{
  Bin data;
  Iterator pos;
public:
  Parser(Bin &&b)
    :data(move(b))
    ,pos{data.cbegin()}
  {}
  Uint get(unsigned int N);

  Iterator getPos() const;
};
Uint aggregate(Uint typeId, vector<Uint> const &arg);
Uint evalNextPacketB(Parser &p);
Uint solutionB(Bin data);

inline auto next(Iterator it, InfInt const & i)
{
  return next(it, i.toInt());
}
