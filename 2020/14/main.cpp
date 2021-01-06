#include <fstream>
#include <string>
#include <vector>
// #include <cmath>
// #include <iostream>
// #include <limits>
#include <numeric>
// #include <cassert>
using namespace std;
  
struct Value{
  unsigned long int data;
public:
  Value(){}
  Value(auto const &other)
  :data(other)
  {}

  long unsigned int& operator()()
  {return data;}
  void operator*=(auto const &other)
  {data*=other;}
  void operator+=(Value const &other)
  {data+=other.data;}
  void operator+=(Value other)
  {
    data+= other.data;
  }
  void operator+=(int other)
  {
    data+= other;
  }
  Value operator+(Value other) const
  {
    other.data +=data;
    return other;
  }
  bool operator<(Value const & other) const
  {
    return data<other.data;
  }
  
  bool operator==(auto const &other) const
  {return data==other.data;};
  bool operator==(int other) const
  {return data==other;};
};



ostream& operator<<(ostream& cout, Value const &v)
{
  cout<<v.data;
  return cout;
}

struct Mask:string
{
  Value valueIfOneIs(char c) const
  {
    Value ret=0;
    int mult=1;
    for(auto x: *this)
      {
	ret*=2;
	if(x==c)
	  ret+=1;
      }
    return ret;
  }
  Value apply(Value v)
  {
    Value const positive = valueIfOneIs('1');
    Value const zero = valueIfOneIs('0');

    return (v.data|positive.data) & (~zero.data);
  }
};


  

Value getIndex(string line)
{
  return stoll(line.substr(1+line.find('['),
			   line.find(']')));
}

Value getValue(string line)
{
  return stoll(line.substr(line.find('=')+1));
}

using Memory = map<Value, Value>;

Value sumMemmory(Memory const &memory)
{
  return accumulate(memory.begin(),
		    memory.end(),
		    Value{0}, 
		    [](Value const v, auto const &pair){
		      return v+pair.second;
		    });
}

Value solveA(ifstream && in)
{
  Memory memory;
  string line;
  Mask m;
  Value index;
  while(getline(in, line))
    {
      if(not line.empty())
	{
	  if(line.starts_with("mask = "))
	    m = {line.substr(line.find('=')+2)};
	  else if(line.starts_with("mem["))
	    memory[getIndex(line)] = m.apply(getValue(line));
	}
    }
  return sumMemmory(memory);
}

Value solveA(string filename)
{
  return solveA(ifstream(filename));
}


struct MemoryMask: Mask
{};

unsigned long int reverse(unsigned long int value, unsigned long int ret=0)
{
  if(value==0)
    return ret;
  else
    return reverse(value/2, 2*ret+(value%2));
}


void setMemory(Memory &m,
	       unsigned long int floating,
	       unsigned long int a,
	       unsigned long int address,
	       Value const &v)
{
  if (floating == 0 and a == 0)
    m[reverse(address)] = v;
  else if(floating%2 == 0)
    {
      return setMemory(m,
		       floating/2,
		       a/2,
		       2*address+a%2,
		       v);
    }
  else
    for(auto i : {0,1})
      setMemory(m,
		floating/2,
		a/2,
		2*address+i,
		v);
}

void setMemory(Memory &m,
	       MemoryMask const &mask,
	       Value a,
	       Value const &v)
{
  a.data|=mask.valueIfOneIs('1').data;
  auto floating = mask.valueIfOneIs('X');
  if(floating==0)
    m[a]=v;
  else
    setMemory(m,
	      floating.data,
	      a.data,
	      0,
	      v);
}

Value solveB(ifstream &&in)
{
  Memory memory;
  string line;
  MemoryMask m;
  Value index;
  while(getline(in, line))
    {
      if(not line.empty())
	{
	  if(line.starts_with("mask = "))
	    m = {line.substr(line.find('=')+2)};
	  else if(line.starts_with("mem["))
	    setMemory(memory,
		      m,
		      getIndex(line),
		      getValue(line));
	}
    }
  return sumMemmory(memory);
}

Value solveB(string filename)
{return solveB(ifstream(filename));}
