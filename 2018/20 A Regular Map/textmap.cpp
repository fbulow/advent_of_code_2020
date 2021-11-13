#include "textmap.hpp"
#include <sstream>
Textmap::Textmap(string in)
{
  istringstream x(in);
  init(x);
}

Textmap::Textmap(istream &in)
{
  init(in);
}

void Textmap::init(istream &in)
{
  char c = in.get();
  vector<char> row;
  while(not in.eof())
    {
      if(c=='\n')
        {
          data.push_back(row);
          row.clear();
        }
      else
          row.push_back(c);
      c = in.get();
    }
}

ostream& operator<<(ostream& out, Textmap const &x)
{
  for(auto const & q: x.data)
    {
      for(char c: q)
        out<<c;
      out<<endl;
    }
  return out;
}
