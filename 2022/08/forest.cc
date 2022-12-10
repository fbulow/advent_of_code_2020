#include "forest.hh"
#include <ostream>
#include <sstream>
#include <numeric>


#include "sweep_line.hh"

using namespace std;

Forrest::Forrest(vector<string>const &vs)
  :Forrest([vs]() //Evaluated immediately!
  {
    vector<TreeLine> ret;
    ret.reserve(vs.size());
    for(auto s:vs)
      if(not s.empty())
	ret.emplace_back(TreeLine(s));
    return ret;
  }())
{}

string Forrest::toString() const
{
  ostringstream out;
  for(auto &s:*this)
    out<<s<<endl;
  return out.str();
}
  
Forrest::Forrest(vector<TreeLine> data)
  :vector<TreeLine>(move(data))
{}

Forrest Forrest::transpose() const
{
  vector<TreeLine> ret;
  auto nRowOut = (*this)[0].size();
  ret.resize(nRowOut);

  string typical;
  for(auto &s: ret)
    s.resize(size(), ' ');
  for(auto row = 0; row<size(); ++row)
    for(auto col = 0; col<nRowOut; ++col)
      ret[col][row] = (*this)[row][col];
  return {ret};
}

void Forrest::sweepLines()
{
  for(auto &treeLine: *this)
    {
      sweepLine(treeLine.begin(),  treeLine.end());
      sweepLine(treeLine.rbegin(), treeLine.rend());
    }
}

Forrest Forrest::sweep(){
  {
    sweepLines();
    auto ret = transpose();
    ret.sweepLines();
    return ret;
  }
}

int Forrest::countVisible() const 
{
  return accumulate(begin(),
		    end(),
		    0,
		    [](auto ret , auto const &line)
		    {
		      return ret+line.countVisible();
		    });
}


