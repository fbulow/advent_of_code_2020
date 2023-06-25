#include "row.hh"
#include <sstream>

Row Row::fromString(std::string row)
{
  Row ret;
  istringstream in(row);
  in>>ret.from>>ret.from;

  std::string slask;
  in>>slask>>slask>>slask;
  for(int i=0;i<5;i++)
    slask[i]=' ';
  (*slask.rbegin())=' ';
  istringstream inInt(slask);
  inInt>>ret.rate;
  in>>slask>>slask>>slask>>slask;

  in>>slask;
  while(*slask.rbegin() == ',')
    {
      ret.to.emplace_back(std::string(slask.begin(), prev(slask.end())));
      in>>slask;
    }
  ret.to.emplace_back(std::move(slask));
  return ret;
}

vector<string> Row::allValves() const
{
  vector<string> ret{to};
  ret.push_back(from);
  return ret;
}
