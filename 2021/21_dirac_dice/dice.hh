#pragma once

class Dice{
  unsigned int next;
  unsigned int count_;
  static constexpr unsigned int MAX = 100;
public:
  Dice(unsigned int start_at=1, unsigned int count=0)
    :next(start_at)
    ,count_(count)
  {}
  unsigned int roll()
  {
    count_++;
    auto ret =  (next++);
    if(next>MAX)
      next=1;
    return ret;
  }
  unsigned int rollTrice()
  {
    return roll()+roll()+roll();
  }
  unsigned int count() const
  {
    return count_;
  }
};
