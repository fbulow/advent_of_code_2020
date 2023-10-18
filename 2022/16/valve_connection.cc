#include "valve_connection.hh"

ValveConnection::ValveConnection(Valve f, Valve t, Steps s)
  :data_(std::move(f), std::move(t), s)
{
  if(from()>to())
    std::swap(from_(), to_());
}


bool operator<(ValveConnection const & lhs, ValveConnection const & rhs)
{
  
  return lhs.data_ < rhs.data_;
}

Valve const & ValveConnection::from()  const {return std::get<0>(data_);}
Valve const & ValveConnection::to  ()  const {return std::get<1>(data_);}
Steps         ValveConnection::steps() const {return std::get<2>(data_);}

Valve & ValveConnection::from_() {return std::get<0>(data_);}
Valve & ValveConnection::to_  () {return std::get<1>(data_);}
