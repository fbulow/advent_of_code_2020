#include<iostream>
#include<fstream>
#include<functional>
#include<numeric>
#include<algorithm>
#include<optional>
#include<cassert>
#include<memory>
#include"strong_type.hpp"
using namespace std;

using Row = strong::type<int, struct Row_,
                         strong::arithmetic,
                         strong::ordered,
                         strong::incrementable,
                         strong::equality>;

using Col = strong::type<int, struct Row_,
                         strong::arithmetic,
                         strong::ordered,
                         strong::incrementable,
                         strong::equality>;

class OctoProxy{
  int* parent{NULL};
public:
  OctoProxy() = default;
  OctoProxy(int& a) {parent = &a;}
  void operator=(int v)
  {
    if(parent)
      *parent = v;
  }
  operator int() const
  {
    if(parent)
      return *parent;
    else
      return 0;
  }
  void operator++()
  {
    if(parent == NULL)
      return;
    else if(*parent==0)
      return;
    else
      (*parent)++;
  }

  bool trigger()
  {
    if(parent)
      if( (*parent)>9 )
        {
          *parent = 0;
          return true;
        }
    return false;
  }
  
};

class Data{
  array<int, 100> d;
public:
  Data(array<int, 100> d)
    :d(move(d))
  {}
  Data(Data const &other)
  {
    copy(other.d.cbegin(), other.d.cend(),
         d.begin());
  }
private:
  bool offBoard(int a, int b)
  {
    return (a<0) or (b<0) or (a>9) or (b>9);
  }
public:
  void increase_all()
  {
    for(auto&x:d)
      x++;
  }

private:
  OctoProxy operator()(int a, int b)
  {
    if (offBoard(a,b))
      return {};
    else
      return {d[10*a+b]};
  }
public:
  OctoProxy operator()(Row a, Col b)
  {
    return operator()(value_of(a), value_of(b));
  }
  bool all_zero() const
  {
    return all_of(d.cbegin(),
                  d.cend(),
                  [](auto x){return x==0;});
  }
  
  
};

unsigned int fizzle_out(Row const i, Col const j, Data &d)
{
  unsigned int ret =0;
  if(d(i,j).trigger())
    {
      ret++;
      for(auto row = i-Row(1); row <= i+Row(1); row++)
        for(auto col = j-Col(1); col <= j+Col(1); col++)
          if( (row!=i) or (col!=j) ) //Off center
            {
              auto octo = d(row,col);
              ++octo;
              ret+=fizzle_out(row, col, d);
            }
    }
  return ret;
}

unsigned int step(Data &d)
{
  d.increase_all();
  unsigned int ret{0};
  for(Row i{0};i<Row(10); i++)
    for(Col j(0);j<Col(10); j++)
        ret+=fizzle_out(i, j, d);
  return ret;
}

Data input(istream& cin)
{
  array<int, 100> d;
  auto i =0;
  while(not cin.eof())
    {
      char c;
      cin>>c;
      d[i++] = c-'0';
    }
  return {d};
}

auto total_flashes(Data d, unsigned int cycles)
{
  unsigned int ret(0);
  for(int i=0;i<cycles;i++)
    ret+=step(d);
  return ret;
}

auto solution_a(Data const &in)
{
  return total_flashes(in, 100);
}

auto solution_b(Data in)
{
  auto steps=0;
  while(not in.all_zero())
    {
      steps++;
      step(in);
    }
      
  return steps;
}

