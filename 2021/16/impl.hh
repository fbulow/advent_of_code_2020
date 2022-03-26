#pragma once

#include<gtest/gtest.h>
#include<string>
#include<cassert>
#include<array>
#include<string_view>
#include<iterator>
#include<numeric>
#include<vector>

using namespace std;
using Uint = unsigned long long int;
struct Hex:string{
};

struct Bin:string{
  Bin(Hex const &h);
  Bin(string const &h);
  operator Uint () const;
  // {
  //   return accumulate(cbegin(), cend(), uint(0),
  //                     [](uint sum, uint nxt) ->uint
  //                     {
  //                       return 2*sum+( (nxt=='0')?0:1 );
  //                     });
  // }
};

string expand(string const & in);

struct Packet{
  Bin data;
  Bin version() const;
  Bin typeId() const;
};

struct Litteral: Packet
{
  Bin value() const;
};

struct Operator: Packet
{
  char lengtType() const
  {
    return data[6];
  }
  Bin bitLength() const
  {
    assert('0'==lengtType());
    return string{
      next(data.cbegin(),7),
      next(data.cbegin(),7+15)};
  }
  Bin subPackages() const
  {
    return string{
      next(data.cbegin(),7+16-1),
      next(data.cbegin(),7+16+bitLength()-1)};
  }
};

using Iterator = string::const_iterator;

Iterator nextPacket(Iterator pos, Iterator begin, Iterator end);

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
