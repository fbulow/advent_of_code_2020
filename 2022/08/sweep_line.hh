#pragma once

int sweepLine(auto begin, auto end, char max='0'-1)
{
  if (begin==end)
    return 0;
  else if(begin->value()>max)
    {
      begin->tick();
      return 1+sweepLine(next(begin), end, begin->value());
    }
  else
    return sweepLine(next(begin), end, max);
}
