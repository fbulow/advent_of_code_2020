#pragma once
#include "types.hh"
#include <tuple>


class ValveConnection
{
public:
  ValveConnection(Valve f, Valve t, Steps s);

  
  Valve const & from() const;
  Valve const & to  () const;
  Steps steps() const;

  friend bool operator<(ValveConnection const & lhs, ValveConnection const & rhs);
private:
  Valve & from_();
  Valve & to_  ();
  std::tuple<Valve, Valve, Steps> data_;
};

bool operator<(ValveConnection const & lhs, ValveConnection const & rhs);

