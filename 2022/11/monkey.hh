#pragma once

#include <queue>
#include <tuple>
#include <functional>
#include "types.hh"
#include "counter.hh"

class Monkey{
  std::queue<int> fifo_;
  std::function<int(int)> oper_;
  int divisor_;
  size_t destTrue_;
  size_t destFalse_;
public:
  template<typename ... T>
  Monkey(std::function<int(int)> oper, int divisor, size_t destTrue, size_t destFalse, T...arg)
    :oper_(oper)
    ,divisor_(divisor)
    ,destTrue_(destTrue)
    ,destFalse_(destFalse)
  {
    (fifo_.push(arg),...);
  }

  static std::vector<Monkey> example();
  static std::vector<Monkey> input();
  
  bool empty() const
  {
    return fifo_.empty();
  }
  
  void push(WorryValue v)
  {
    fifo_.push(v);
  }

  struct Pop{
    size_t destination;
    WorryValue value;
  };
  
  Pop pop( WorryManager worryManager = [](WorryValue old){return old/3;})
  {
    auto ret = worryManager(oper_(fifo_.front()));
    fifo_.pop();
    return {ret%divisor_==0?destTrue_:destFalse_,
	    ret};
  }
  
};

void round(std::vector<Monkey> & data, Counter &c, WorryManager worryManager = [](WorryValue old){return old/3;});

