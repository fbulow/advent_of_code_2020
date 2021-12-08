#include<iostream>
#include<fstream>
#include<functional>
#include<numeric>
#include<algorithm>
#include<optional>
#include<cassert>
using namespace std;

class Ordered{
protected:
  string d;
  Ordered() = default;

  Ordered(string &&s)
    :d(move(s))
  {
    init();
  }

  void init(){sort(d.begin(), d.end());}
  
public:
  string const & data() const
  {
    return d;
  }
  size_t size() const
  {
    return d.size();
  }
  auto cbegin() const 
  {return d.cbegin();}
  auto cend() const
  {return d.cend();}
};

class Signal:public Ordered{
public:
  Signal()=default;

  Signal(string s)
    :Ordered(move(s))
  {}
  bool operator==(Signal const & other) const
  {
    return d == other.d;
  }
  friend istream& operator>>(istream& in, Signal  &s);
  friend ostream& operator<<(ostream& out, Signal const &s);
};

istream& operator>>(istream& in, Signal  &s)
{
  in>>s.d;
  s.init();
  return in;
}

ostream& operator<<(ostream& out, Signal const &s)
{
  out<<s.d;
  return out;
}


using Visual = optional<int>;

class Led:public Ordered{
public:
  Led(string s)
    :Ordered(move(s))
  {}
  
  bool operator==(Led const & other) const
  {
    return d == other.d;
  }

  Visual visual() const
  {
    if (d == "abcefg")
      return 0;
    else if (d=="cf")
      return 1;
    else if (d=="acdeg")
      return 2;
    else if (d=="acdfg")
      return 3;
    else if (d=="bcdf")
      return 4;
    else if (d=="abdfg")
      return 5;
    else if (d=="abdefg")
      return 6;
    else if (d=="acf")
      return 7;
    else if (d=="abcdefg")
      return 8;
    else if (d=="abcdfg")
      return 9;
    else
      return {};
  }
  
};

class Wiring{
  string d;
public:
  Wiring(string s="abcdefg")
    :d(move(s))
  {
    assert(d.size()==7);
  }

  char operator[](char c) const
  {
    return d[c-'a'];
  }
  Led operator[](Signal const &s) const
  {
    return [=, this]{
      string ret;
      ret.resize(s.size());
      std::transform(s.cbegin(),
                     s.cend(),
                     ret.begin(),
                     [this](char c){return (*this)[c];}
                     );
      return ret;
    }();
  }

  void deduce(array<Signal, 10> const & data)
  {
    array<bool, 10> seen;
    seen.fill(false);
    next_permutation();
    
    for(Signal const &x:data)
      {
        auto v = (*this)[x].visual();
        if(not v)
          return deduce(data);
        else if(seen[v.value()])
          return deduce(data);
        else
          seen[v.value()]=true;
      }
    assert(all_of(seen.begin(), seen.end(), [](bool x){return x;}));
  }
  
protected:
  bool next_permutation()
  {return std::next_permutation(d.begin(), d.end());}
};

struct Row{
  array<Signal, 10> all;
  array<Signal, 4> rhs;
  Row() = default;
  Row(istream &in)
  {
    in>>*this;
  }

  int value() const
  {
    Wiring w;
    w.deduce(all);
    return
      1000*w[rhs[0]].visual().value()
      +100*w[rhs[1]].visual().value()
      + 10*w[rhs[2]].visual().value()
      +  1*w[rhs[3]].visual().value();
  }

  
  friend istream& operator>>(istream&cin, Row &r);
};  

istream& operator>>(istream&in, Row &r)
{
  for(Signal &x: r.all)
    in>>x;
  string slask;
  in>>slask;
  for(auto &x: r.rhs)
    in>>x;
  return in;
}

using Data = vector<Row>;

Data input(istream& cin)
{
  Data ret;

  Row r(cin);
  while(not cin.eof())
    {
      ret.push_back(r);
      cin>>r;
    }

  return ret;
}


auto solution_a(Data const &in)
{
  return "See python main.py";
}

auto solution_b(Data const &in)
{
  return accumulate(
                    in.cbegin(),
                    in.cend(),
                    0,
                    [](long int s, Row const &r)
                    {
                      return s+r.value();
                    });
}

