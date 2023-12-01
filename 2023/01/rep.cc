#include "rep.hh"

using namespace std;

vector<Rep> Rep::intsOnly()
{
  return {
    Rep{"0", 0},
    Rep{"1", 1},
    Rep{"2", 2},
    Rep{"3", 3},
    Rep{"4", 4},
    Rep{"5", 5},
    Rep{"6", 6},
    Rep{"7", 7},
    Rep{"8", 8},
    Rep{"9", 9}};
}

vector<Rep> Rep::all()
{
  auto ret = intsOnly();
  ret.emplace_back("zero",	  0);
  ret.emplace_back("none",	  0);
  ret.emplace_back("naught",      0);
  ret.emplace_back("one",	  1);
  ret.emplace_back("two",	  2);
  ret.emplace_back("three",	  3);
  ret.emplace_back("four",	  4);
  ret.emplace_back("five",	  5);
  ret.emplace_back("six",	  6);
  ret.emplace_back("seven",	  7);
  ret.emplace_back("eight",	  8);
  ret.emplace_back("nine",	  9);
  return ret;
}



