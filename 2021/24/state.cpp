#include <cassert>
#include "state.hpp"
#include "instruction.hpp"
#include <functional>



namespace
{
  int index(Arg a)
  {
    assert(a>='w');
    assert(a<='z');
    return a-'w';
  }
};

void State::apply(Instruction const&i)
{
  if(i.cmd==Command::inp)
    {
      inputTarget = i.a;
      return;
    }

  auto &dest = s[index(i.a)];
  auto a = value(i.a);
  Int b;
  if(std::holds_alternative<Arg>(i.b))
    b = value(std::get<Arg>(i.b));
  else
    b = get<Int>(i.b);
  switch(i.cmd)
    {
    case Command::add:
      dest = a + b;
      return;
    case Command::mul:
      dest = a * b;
      return;
    case Command::div:
      dest = a / b;
      return;
    case Command::mod:
      dest = a % b;
      return;
    case Command::eql:
      dest = (a == b)?1:0;
      return;
    }
}


void State::input(int v)
{
  assert(inputRequired());
  s[index(inputTarget)] = v;
  inputTarget='\0';
}

Int State::value(Arg a) const
{
  if((a>='1') and (a<='9'))
    return a-'0';
  else
    return s[index(a)];
}

Int State::value(Int a) const
{
  return a;
}
