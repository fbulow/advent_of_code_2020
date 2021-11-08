#pragma once
#include<functional>
#include<iostream>
enum class S{N, S, E, W, BEGIN, END};

template<class T>
char transverse_ignore_branching(istream &note,
                                 T process)
{
  char c;
  note>>c;
  while(c!='$')
    {
      switch(c)
        {
        case ')':
        case '$':
        case '|':
          return c;
        case '(':
          {
            auto d = transverse_ignore_branching(note, T(process));
            while(d =='|')
                d = transverse_ignore_branching(note, T(process));
            return d;
          }
        case 'S':
        case 'E':
        case 'W':
        case 'N':
          process(c);
        }
      note>>c;
    }
  return c;
};

