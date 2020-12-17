#include <fstream>
#include <string>
#include <vector>
// #include <cmath>
// #include <iostream>
// #include <limits>
#include <numeric>
// #include <cassert>
#include<list>
#include<deque>
using namespace std;

using I = int;

struct MinMax
{
  I min;
  I max;
  bool ok(I value) const
  {
    return (min <= value) and (value <= max);
  }
};

struct Rule{
  vector<MinMax> data;
  bool ok(I value) const
  {
    return any_of(data.begin(),
		  data.end(),
		  [&value](MinMax const &m)
		  {
		    return m.ok(value);
		  });
  }
  Rule(string const &line)
  {
    string sx(next(find(line.begin(),
			line.end(),
			':')),
	      line.end());
    istringstream s(sx);

    MinMax a;
    char c, theOr[4];
    s>>a.min>>c>>a.max>>theOr;
    data.push_back(a);
    s>>a.min>>c>>a.max;
    data.push_back(a);
  }
  
};

bool obviousInvalid(I value, vector<Rule> const & rules)
{
  return none_of(rules.begin(),
		 rules.end(),
		 [value](Rule const &r)
		 {
		   return r.ok(value);
		 });

}


struct Ticket
{
  vector<I> numbers;
  auto begin() const {return numbers.begin();}
  auto end()   const {return numbers.end();}
  Ticket(string s)
  {
    char c;
    I i;
    istringstream in(s);
    while(not in.eof())
      {
	in>>i>>c;
	numbers.push_back(i);
      }
  }
  I operator[](size_t i) const
  {return numbers[i];}

  size_t size() const
  {return numbers.size();}

  int scanningErrorRate(vector<Rule> const &rules) const
  {
    auto it = find_if(begin(), end(),
		      [&rules](I value)
		      {
			return ::obviousInvalid (value, rules);
		      });
    if(it==end())
      return 0;
    else
      return *it;
  }
};


ostream& operator<<(ostream& cout, MinMax const &mm)
{
  cout<<mm.min<<"-"<<mm.max;
  return cout;
}
ostream& operator<<(ostream& cout, Rule const &r)
{
  assert(r.data.size()==2);
  cout<<": "<<r.data[0]<<" or "<<r.data[1]<<endl;
  return cout;
}

struct Input
{
  vector<Rule> rules;
  vector<Ticket> nearby;

  Input(deque<string> &&q)
    :rules{q.begin(), find(q.begin(),
			   q.end(), "")}
    ,nearby{
	next(find(q.begin(),
		  q.end(),
		  "nearby tickets:")),
	q.end()}
  {}
  
  Input(string filename)
    :Input([&filename](){ //Evaluated immediately
      ifstream in(filename);
      assert(in.is_open());
      string line;
      deque<string> q;
      while(getline(in,line))
	q.push_back(line);
      return q;
    }())
  {}

  I ticketScanningErrorRate() const
  {
    
    return accumulate(nearby.begin(),
		      nearby.end(),
		      0,
		      [this](I sum, Ticket const &ticket)
		      {
			return sum+ticket.scanningErrorRate(this->rules);
		      });
  }
  
};


