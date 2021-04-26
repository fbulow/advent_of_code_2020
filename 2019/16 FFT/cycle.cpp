#include "cycle.hpp"

int cycle(unsigned int count)
{
  switch( count % 4 )
    {
    case 1:
      return 1;
    case 3:
      return -1;
    default:
      return 0;
    }
}
