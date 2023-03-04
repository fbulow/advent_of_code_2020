#include "read_input.hh"

using namespace std;


void readInputRec_(vector<string> &ret, istream &in)
{
  string row;
  in>>row;
  if(not in.eof())
    {
      ret.emplace_back(move(row));
      readInputRec_(ret, in);
    }
}

Input readInput(istream &in)
{
  vector<string> ret;
  readInputRec_(ret, in);
  return ret;
}
