#include "state.hpp"
#include "instruction.hpp"

void State::apply(Instruction const&i)
{
  switch(i.cmd)
    {
    case Instruction::Command::add:
      s[0]+=i.b-'0';
      return;
    }
}
