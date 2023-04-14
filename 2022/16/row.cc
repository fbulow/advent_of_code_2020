#include "row.hh"
#include <sstream>

Row::Row(std::string row)
{
  istringstream in(row);
  in>>from>>from;

  std::string slask;
  in>>slask>>slask>>slask;
  for(int i=0;i<5;i++)
    slask[i]=' ';
  (*slask.rbegin())=' ';
  istringstream inInt(slask);
  inInt>>rate;
  in>>slask>>slask>>slask>>slask;

  in>>slask;
  while(*slask.rbegin() == ',')
    {
      to.emplace_back(std::string(slask.begin(), prev(slask.end())));
      in>>slask;
    }
  to.emplace_back(std::move(slask));
}
