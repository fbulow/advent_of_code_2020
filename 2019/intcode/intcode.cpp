#include "intcode.hpp"

ostream& operator<<(ostream &out, IntCode const &ic)
{
  out<<ic.memory.begin()->second;
  for_each(next(ic.memory.begin()), ic.memory.end(),
           [&out](auto i){
             out<<","<<i.second;
           });
  return out;
}
unsigned int opcode(I command)
{
  return command%100;
}
unsigned int mode(I index, I command)
{
  if(index==1)
    return command/100%10;
  else if(index==2)
    return command/1000%10;
  else if(index==3)
    return command/10000%10;
  return 0;
}

