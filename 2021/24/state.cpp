#include <cassert>
#include "state.hpp"
#include "instruction.hpp"

void State::apply(Instruction const&i)
{
  switch(i.cmd)
    {
    case Command::add:
      s[i.a-'w']+=i.b-'0';
      return;
    }
}

int State::value(Storage s)
{
  switch(s)
    {
    case Storage::w :
      return 0;
    case Storage::x :
      return 1;
    case Storage::y :
      return 2;
    case Storage::z :
      return 3;
    }
  assert(false);
}
