#pragma once
#include <cassert>

class Tile
{
    char c;
public:
  Tile(char c)
    :c(c)
  {
    switch(c)
      {
      default:
	assert(false);
      case '0':
      case '1':
      case '2':
      case '3':
      case '4':
      case '5':
      case '6':
      case '7':
      case '8':
      case '9':
      case 'a':
      case 'b':
      case 'c':
      case 'd':
      case 'e':
	{}
      }
  }
  char get()const
  {return c;}
};
