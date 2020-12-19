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
  string name;
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
    :name(line.begin(), find(line.begin(),
			     line.end(),
			     ':'))
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

  bool operator==(auto const&other) const
  {
    return other.numbers==numbers;
  }
  
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


ostream& operator<<(ostream& cout, Ticket const &t)
{
  for(auto x: t.numbers)
    cout<<x<<",";
  return cout;
}

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

deque<string> readStream(string filename)
{
  ifstream in(filename);
  assert(in.is_open());
  string line;
  deque<string> q;
  while(getline(in,line))
    q.push_back(line);
  return q;
}

struct Input
{
  vector<Rule> rules;
  vector<Ticket> nearby;
  Ticket my;
  Input(deque<string> &&q)
    :rules{q.begin(), find(q.begin(),
			   q.end(), "")}
    ,nearby{
	next(find(q.begin(),
		  q.end(),
		  "nearby tickets:")),
	q.end()}
    ,my{*next(find(q.begin(),
		   q.end(),
		   "your ticket:"))}
  {}

  Input(string filename)
    :Input(readStream(filename))
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

void sliceToValues(vector<set<I>> &values, Ticket const &ticket)
{
  assert(values.size()==ticket.size());
  auto dest = values.begin();
  for(auto &t:ticket)
    {
      dest->insert(t);
      advance(dest, 1);
    }
}

// void select(vector<set<size_t>> &options, size_t index, size_t value)
// {
//   assert(options[index].contains(value));
//   options[index]={value};
//   for(auto &x: options)
//     x.erase(value);
// }

using Option = set<size_t>;

bool solved(vector<Option> const &options)
{
  if (not all_of(options.begin(),
		 options.end(),
		 [](auto x){return x.size()==1;}))
    return false;
  else
    {
      set<I> s;
      for(auto &x:options)
	s.insert(*x.begin());
      return s.size()==options.size();
    }
}

set<I> getKnown(vector<Option> const &data)
{
  set<I> ret;
  for (auto x: data)
    if (1 == x.size())
      ret.insert(*x.begin());
  return ret;
}

vector<Option> reduce(vector<Option> data)
{
  for(auto i:getKnown(data))
    for(auto &d:data)
      if(1<d.size())
	d.erase(i);
  return data;
}

int uncertainty(vector<Option> const &options)
{
  return accumulate(options.begin(),
		    options.end(),
		    0,
		    [](int sum, auto option)
		    {
		      return sum+option.size();
		    });
		    
}

vector<Option> recursiveReduce(vector<Option> data)
{
  auto u = uncertainty(data);
  data=reduce(data);
  while(uncertainty(data) < u)
    {
      u = uncertainty(data);
      data=reduce(data);
    }
  return data;
}

struct Conclude: Input
{
  Ticket my;
  vector<set<I>> values;
  vector<Option> options; // options[0].contains(5) means that rule[0] is met by all values in values[5].

  void setUpOptions()
  {
    options.resize(rules.size());
    for(int i=0;i<options.size();i++)
      for(int r=0;r<rules.size();r++)
	{
	  auto &rule = rules[r];
	  if( all_of(values[i].begin(),
		     values[i].end(),
		     [rule](I v){
		       return rule.ok(v);
		     }) )
	    options[r].insert(i);
	}
  }
  
  Conclude(deque<string> data)
    :Input(deque<string>(data.begin(), data.end()))
    ,my(*next(find(data.begin(), data.end(), "your ticket:")))
  {
    setUpValues();
    setUpOptions();
  }

  void setUpValues()
  {  
    values.resize(my.size());
    sliceToValues(values, my);
    for(auto &n:nearby)
      if(n.scanningErrorRate(rules) == 0)
	 sliceToValues(values, n);
      
  }
  
  Conclude(string filename)
    :Conclude(readStream(filename))
  {}
  
  // vector<set<size_t>> candidates;
  // vector<set<size_t>> values;

  // Conclude(string filename)
  //   :Input(filename)
  // {
  //   candidates.resize(rules.size());
  //   values.resize(rules.size());
    
  //   for(Ticket const &t: nearby)
  //     if(0==t.scanningErrorRate(rules))
  // 	for(size_t i=0; i < values.size() ; i++)
  // 	  values[i].insert(
	  
  // 	}
  // }

};
  

long int answer(vector<Rule> const &fields,
		vector<size_t> const &order,
		Ticket const &my)
{
  I prod = 1;
  for(size_t i =0 ; i < fields.size(); i++)
    if(fields[i].name.starts_with("departure"))
      prod*=my[order[i]];
  return prod;
}
		
