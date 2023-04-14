#include "read_input.hh"

vector<string> readInput(istream &in)
{
  vector<string> ret;
  try
    {
      while(true)
	{
	  ret.emplace_back(
			   [&ret, &in]()
			   {
			     string row;
			     getline(in, row);
			     if(row.empty())
			       throw exception();
			     return row;
			   }());
	}
    }
  catch(...)
    {
    }
  return ret;
}

