#pragma once

using namespace std;

#include "row.hh"
#include <map>

class DistanceList
{
  map<pair<string, string>, int> data_;
  
public:
  DistanceList(vector<Row> const &rows)
  {
    for(auto const &r : rows)
      for(auto const &t : r.to)
	{
	  data_[{r.from, t}]=1;
	  data_[{t, r.from}]=1;
	}
  }

  int steps(string const & from, string const & to) const
  {
    if(from==to)
      return 0;
    else
      return data_.at({from, to});
  }

};
