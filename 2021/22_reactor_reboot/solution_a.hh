#pragma once

inline unsigned int solutionA(vector<Instruction> const &input)
{
  Space space;    

  for(auto &x: input)
    space.fill(x.cube, x.turnOn());
  return space.countOn();
}
