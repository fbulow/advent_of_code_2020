#include <cmath>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <limits>
#include <numeric>
#include <cassert>
using namespace std;



optional<long int>  departure(long int arrival,
			      vector<long int> times)
{
  for(auto x: times)
    if(arrival%x == 0)
      return x;
  return {};
}

long int nextAvaliableTime(long int arrival,
			   vector<long int> times)
{
  while(not departure(arrival, times))
    arrival++;
  return arrival;
}

struct Plan{
  Plan(ifstream&& in)
  {
    assert(in.is_open());
    in>>arrival;
    string line;
    getline(in, line);
    getline(in, line);
    auto b = line.begin();
    auto e = line.end();
    while(b<e)
      {
	auto x =find(b,e, ',');
	string newNumber{b,x};
	try
	  {
	    times.emplace_back(stoll(newNumber));
	  }
	catch(std::invalid_argument)
	  {}
	b=next(x);
      }
  }
  
  long int arrival;
  vector<long int> times;
};

long int solveA(string filename)
{
  Plan p(ifstream{filename});
  auto t = nextAvaliableTime(p.arrival, p.times);
  auto d = departure(t, p.times).value();
  return (t-p.arrival)*d;
}

