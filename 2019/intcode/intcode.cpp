#include "intcode.hpp"
#include <cassert>

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

I& IntCode::ref(I index, I command)
{
  switch(mode(index,command))
    {
    case 0://position mode
      return memory[memory[instructionPointer+index]];
    case 1:
      return memory[instructionPointer+index];
    case 2:
      return memory[relativeBase+memory[instructionPointer+index]];
    default:
      assert(false);
    }
}

IntCode::IntCode(istream &&in, I pos)
  :instructionPointer(pos)
{
  I address=0;
  I i;
  in>>i;
  memory.insert({address++, i});
  char c;
  in>>c>>i;
  while(not in.eof())
    {
      memory.insert({address++, i});
      assert(c==',');
      in>>c>>i;
    }
  memory.insert({address++, i});
}

I& IntCode::operator[](I i)
{
  return memory[i];
}
  

bool IntCode::operator==(IntCode const &other)const
{
  return (memory==other.memory) and (instructionPointer==other.instructionPointer);
}
  

void IntCode::run()
{
  while(step())
    {};
}

bool IntCode::step()
{
  auto inst = memory[instructionPointer];
  auto code = opcode(inst);
  I increase = 1;
  auto x = [this, inst, &increase](I index) -> I&
  {
    increase = max(increase, index+1);
    return ref(index, inst);
  };
      
  if(code==99)
    return false;
  else if(code==1)
    x(3) = x(1) + x(2);
  else if(code==2)
    x(3) = x(1) * x(2);
  else if(code==3)
    {
      x(1)=input.front();
      input.pop();
    }
  else if(code==4)
    output.push(x(1));
  else if(code==5) //Opcode 5 is jump-if-true: if the first
    //parameter is non-zero, it sets the instruction
    //pointer to the value from the second
    //parameter. Otherwise, it does nothing.
    {
      if(x(1)!=0)
        {
          instructionPointer=x(2);
          return true;
        }
      x(2);
    }
  else if(code==6) //Opcode 6 is jump-if-false: if the first
    //parameter is zero, it sets the instruction
    //pointer to the value from the second
    //parameter. Otherwise, it does nothing.
    {
      if(x(1)==0)
        {
          instructionPointer=x(2);
          return true;
        }
      x(2);
    }
  else if(code==7) //Opcode 7 is less than: if the first parameter
    //is less than the second parameter, it stores 1
    //in the position given by the third
    //parameter. Otherwise, it stores 0.
    x(3) = ( x(1) < x(2) ) ? 1 : 0;
  else if(code==8) //Opcode 8 is equals: if the first parameter is
    //equal to the second parameter, it stores 1 in
    //the position given by the third
    //parameter. Otherwise, it stores 0.
    x(3) = ( x(1) == x(2) ) ? 1 : 0;
  else if (code==9) //Opcode 9 adjusts the relative base by the
    //value of its only parameter. The relative base
    //increases (or decreases, if the value is
    //negative) by the value of the parameter.
    relativeBase += x(1);
  else
    assert(false);

  instructionPointer += increase;
  return true;
}

