#pragma once
#include "types.hh"
#include <tuple>


class ValveConnection
{
public:
  ValveConnection(Valve f, Valve t, Steps s)
    :data_(std::move(f), std::move(t), s)
  {
    if(from()>to())
      std::swap(from_(), to_());
  }

  
  Valve const & from() const {return std::get<0>(data_);}
  Valve const & to  () const {return std::get<1>(data_);}
  Steps steps() const {return std::get<2>(data_);}

  friend bool operator<(ValveConnection const & lhs, ValveConnection const & rhs);
private:
  Valve & from_() {return std::get<0>(data_);}
  Valve & to_  () {return std::get<1>(data_);}
  std::tuple<Valve, Valve, Steps> data_;
};

inline
bool operator<(ValveConnection const & lhs, ValveConnection const & rhs)
{
  
  return lhs.data_ < rhs.data_;
}

