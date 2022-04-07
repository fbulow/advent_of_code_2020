#include "solution_a.hh"
#include "dice.hh"
unsigned int solutionA(Player a,
                       Player b)
{
  Dice d;
  while(true)
    {
      if(0 == (d.count()%2))
        {
          a.move(d.rollTrice());
          if(a.score() >=1000)
            return b.score()*d.count();
        }
      else
        {
          b.move(d.rollTrice());
          if(b.score() >=1000)
            return a.score()*d.count();
        }
    }  
}
