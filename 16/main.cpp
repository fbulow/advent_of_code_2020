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
  bool allValuesOk(auto values) const
  {
    return all_of(values.begin(),
		  values.end(),
		  [this](auto &x){return ok(x);});
  }
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

  bool obviousInvalid(vector<Rule> const & rules)
  {
    return any_of(numbers.begin(),
		  numbers.end(),
		  [&rules](auto n){
		    return ::obviousInvalid(n, rules);
		  });
  }
    
  
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
      dest++;
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
struct Options: public vector<Option>
{
  Options(vector<Option> &&data)
    :vector<Option>(move(data))
  {}
  Options() = default;
    
  
  bool solved() const 
  {
    if (not all_of(begin(),
		   end(),
		   [](auto x){return x.size()==1;}))
      return false;
    else
      {
	set<I> s;
	for(auto &x:*this)
	  s.insert(*x.begin());
	return s.size()==size();
      }
  }

  set<I> getKnown() const 
  {
    set<I> ret;
    for (auto x: *this)
      if (1 == x.size())
	ret.insert(*x.begin());
    return ret;
  }

  void reduce()
  {
    for(auto i:getKnown())
      for(auto &d:*this)
	if(1<d.size())
	  d.erase(i);
  }
  int uncertainty() const
  {
    return accumulate(begin(),
		      end(),
		      0,
		      [](int sum, auto option)
		      {
			return sum+option.size();
		      });
		    
  }
  bool failed() const
  {
    if( any_of(begin(),
	       end(),
	       [](auto &x){return x.empty();}) )
      return true;
    else
      {
	set<size_t> s;
	for(auto &x: *this)
	  for(auto &v: x)
	    s.insert(v);
	return s.size() < size(); //Has failed if elemnts are missing.
      }
  }
};

Options recursiveReduce(Options data)
{
  auto u = data.uncertainty();
  data.reduce();
  while(data.uncertainty() < u)
    {
      u = data.uncertainty();
      data.reduce();
    }
  return data;
}

struct Conclude: Input
{
  Ticket my;
  vector<set<I>> values;
  Options options; // options[0].contains(5) means that rule[0] is met by all values in values[5].

  void setUpOptions()
  {
    assert(rules.size()==my.size());
    assert(my.size()==values.size());

    auto const N = values.size();
    
    options.resize(N);
    for(int v=0;v<N;v++) //Value set
      for(int r=0;r<N;r++)//Rule
	{
	  if(rules[r].allValuesOk(values[v]))
	    options[r].insert(v);
	  if(none_of(rules.begin(),
		     rules.end(),
		     [this, v](auto &r){return r.allValuesOk(values[v]);}))
	    {
	      cout<<"v "<<v<<endl;
	      for(auto x:values[v])
		{
		  cout<<x<<"  ";
		  for(int r=0;r<N;r++)//Rule
		    if(rules[r].ok(x))
		      cout<<r<<", ";
		  cout<<endl;
		}
	    assert(false);
	    }
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
    assert(my.scanningErrorRate(rules) == 0);
    sliceToValues(values, my);
    for(auto &n:nearby)
      if(not n.obviousInvalid(rules))
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
  long int prod = 1;
  for(size_t i =0 ; i < fields.size(); i++)
    if(fields[i].name.starts_with("departure"))
      prod*=my[order[i]];
  return prod;
}
		
long int solutionB(string filename)
{
  Conclude sut(filename);
  auto const opt = recursiveReduce(sut.options);


  vector<size_t> order(sut.options.size());

  transform(opt.begin(),
	    opt.end(),
	    order.begin(),
	    [](auto x){return *x.begin();});

  // return sut.my[1  ]* 
  //   sut.my[5  ]* 
  //   sut.my[9  ]* 
  //   sut.my[7  ]* 
  //   sut.my[15 ]*
  //   sut.my[12 ];
  
  return answer(sut.rules,
		order,
		sut.my);
  
}
