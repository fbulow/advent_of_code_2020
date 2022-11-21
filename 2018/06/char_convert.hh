#pragma once

inline
char toVisibleChar(int val)
{
  if(val==0)
    return '.';
  else
    return 'a'+(val-1);
}

inline
int fromVisibleChar(char c)
{
  if(c=='.')
    return 0;
  else
    return c+1-'a';
}


