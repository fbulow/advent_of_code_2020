#pragma once

inline
int height(char c)
{
  switch(c)
    {
    case 'S':
      return 'a';
    case 'E':
      return 'z';
    default:
      return c;
    }
}
