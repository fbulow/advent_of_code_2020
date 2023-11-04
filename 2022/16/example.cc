#include "example.hh"

Input example()
{
  Input ret;
  ret["AA"] =  {0,  {"DD", "II", "BB"}};
  ret["BB"] =  {13, {"CC", "AA"}};
  ret["CC"] =  {2,  {"DD", "BB"}};
  ret["DD"] =  {20, {"CC", "AA", "EE"}};
  ret["EE"] =  {3,  {"FF", "DD"}};
  ret["FF"] =  {0,  {"EE", "GG"}};
  ret["GG"] =  {0,  {"FF", "HH"}};
  ret["HH"] =  {22, {"GG"}};
  ret["II"] =  {0,  {"AA", "JJ"}};
  ret["JJ"] =  {21, {"II"}};

  return ret;
}

Score::Score(Time t, Flow f, int sum)
  :t(t)
  ,f(f)
  ,sum(sum)
{}

int Score::total() const
{
  return log(30,0).sum;     
}

Score Score::log(Time time, Flow flow) const
{
  return Score(
	       time,
	       f+flow,
	       sum+f*(time-t)
	       );
}

Flow Input::flow(Valve v) const
{
  return at(v).first;
}

Path examplePath()
{
  Path p({
    {2,  "DD"},
    {5,  "BB"},
    {9,  "JJ"},
    {17, "HH"},
    {21, "EE"},
    {24, "CC"}});

  return p;
}
