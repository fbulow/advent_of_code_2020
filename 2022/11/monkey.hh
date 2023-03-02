#pragma once

#include <queue>
#include <tuple>
#include <functional>
#include "types.hh"
#include "counter.hh"

class Monkey{
  std::queue<WorryValue> fifo_;
  int divisor_;
  size_t destTrue_;
  size_t destFalse_;
public:
  template<typename ... T>
  Monkey(std::function<WorryValue(WorryValue)> oper, int divisor, size_t destTrue, size_t destFalse, T...arg)
    :oper(oper)
    ,divisor_(divisor)
    ,destTrue_(destTrue)
    ,destFalse_(destFalse)
  {
    (fifo_.push(arg),...);
  }

  std::function<WorryValue(WorryValue)> oper;

  static std::vector<Monkey> example();
  static std::vector<Monkey> input();

  int getDivisor() const
  {
    return divisor_;
  }
  
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
    auto a = fifo_.front();
    auto b = oper(a);
    auto ret = worryManager(b);
    fifo_.pop();
    return {ret%divisor_==0?destTrue_:destFalse_,
	    ret};
  }
  
};

void round(std::vector<Monkey> & data, Counter &c, WorryManager worryManager = [](WorryValue old){return old/3;});

long int productOfDivisors(std::vector<Monkey> const & m);



			   
