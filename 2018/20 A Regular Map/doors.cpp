#include "doors.hpp"
#include "strong_type.hpp"
#include "transverse.hpp"
#include <algorithm>

Door::Door(Position const & a, Position const &b)
  :a(min(a,b))
  ,b(max(a,b))
{
  assert(a!=b);
}

bool Door::has(Position const &p) const
{
  return (a==p) or (b==p);
}


Position Door::other(Position const &p) const 
{
  if(a==p)
    return b;
  else
    {
      assert (b==p);
      return a;
    }
}


ostream& operator<<(ostream& out, Doors const &d)
{
  /*
0   4 
#####
# | #
#####
   */

   int row_min = 1;
   int row_max = 2;
   int col_min = -1;
   int col_max = 2;
  
  
   int width = 2*(col_max-col_min)+1;
   int height = 2*(row_max-row_min)+1;

  auto origin = [=](auto row, auto col)
  {
    return
      row == 1-2*row_min
    and
      col == 1-2*col_min;
  };
    
  auto door_right = [](auto row, auto col)
  {
    return false;//row==2;
  };
  auto door_down = [](auto row, auto col)
  {
    return col==3;
  };

  for(int row=0;row < height; row++)
    {
      for(int col=0;col < width; col++)
      {
        if (row==0 or row == (height-1))
          cout<<"#";
        else if (col==0 or col == (width-1))
          cout<<"#";                  
        else if(row%2==0 and col%2==0)
          cout<<"#";
        else if(row%2==0)
          {
            if(door_down(row/2, col/2))
              cout<<"-";
            else
              cout<<"#";
          }

        else if(col%2==0)
          {
            if(door_right(row/2, col/2))
              cout<<"|";
            else
              cout<<"#";
          }
        else if (origin(row,col))
          cout<<"X";
        else
          cout<<" ";
      }
      cout<<endl;
    }
  return out;
}

Doors::Doors(string s)
{
  istringstream in(s);
  transverse_ignore_branching(in,
                              Trail(*this));
}

Position Doors::start_at() const
{
    return position;
}
