#include "tree_line.hh"
#include <algorithm>

using namespace std;

int TreeLine::countVisible() const
{
  return count_if(begin(),
		  end(),
		  [](auto const &t)
		  {
		    return t.ticked();
		  });
}

ostream& operator<<(ostream& out, TreeLine const & tl) 
{
  for(auto const &x:tl)
    out<<x.value();
  return out;
}
