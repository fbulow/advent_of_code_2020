#include <fstream>
#include <string>
#include <vector>
// #include <cmath>
// #include <iostream>
// #include <limits>
#include <numeric>
// #include <cassert>
using namespace std;
  
using Value = unsigned long int;

struct Mask:string
{
  Value valueIfOneIs(char c)
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

    return (v|positive) & (~zero);
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

Value solveA(ifstream && in)
{
  map<Value, Value> memory;
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
  return accumulate(memory.begin(),
		    memory.end(),
		    Value{0}, 
		    [](Value const v, auto const &pair){
		      return v+pair.second;
		    });
}


Value solveA(string filename)
{
  return solveA(ifstream(filename));
}
