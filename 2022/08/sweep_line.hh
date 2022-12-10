#pragma once

void sweepLine(auto begin, auto end, char max='0'-1)
{
  if (begin==end)
    return;
  else if(begin->value()>max)
    {
      begin->tick();
      return sweepLine(next(begin), end, begin->value());
    }
  else
    return sweepLine(next(begin), end, max);
}
