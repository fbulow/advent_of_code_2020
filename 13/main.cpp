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

using TimeStamp=long int;



struct
Plan{
  TimeStamp arrival;
  vector<TimeStamp> times;
  vector<TimeStamp> wait;

  Plan(ifstream&& in)
  {
    assert(in.is_open());
    in>>arrival;
    string line;
    getline(in, line);
    getline(in, line);
    auto b = line.begin();
    auto e = line.end();
    TimeStamp waitCount =0;
    while(b<e)
      {
	auto x =find(b,e, ',');
	string newNumber{b,x};
	try
	  {
	    times.emplace_back(stoll(newNumber));
	    wait.push_back(waitCount);
	  }
	catch(std::invalid_argument)
	  {}
	waitCount++;
	b=next(x);
      }
  }
  
  bool arrivalRequirement(TimeStamp t)
  {
    for (size_t i=0;i<times.size();i++)
      if((t+wait[i])%times[i] != 0)
	return false;
    return true;
  }
  
};

TimeStamp solveA(string filename)
{
  Plan p(ifstream{filename});
  auto t = nextAvaliableTime(p.arrival, p.times);
  auto d = departure(t, p.times).value();
  return (t-p.arrival)*d;
}

bool sovlesB(Plan const &p, TimeStamp t)
{
  for(size_t i =0; i< p.times.size(); i++)
    if((t+p.wait[i])%p.times[i] != 0)
      return false;
  return true;
}

struct MagicTimeBuilder
{
  TimeStamp candidate{0};
  TimeStamp step{1};

  void addBus(TimeStamp line,
	       TimeStamp wait)
  {
    while((candidate+wait)%line != 0)
      candidate+=step;
    step*=line;
  }
};



TimeStamp solveB(string filename)
{
  Plan p(ifstream{filename});
  MagicTimeBuilder mtb;
  for(size_t i=0; i < p.times.size(); i++)
    mtb.addBus(p.times[i],
	       p.wait[i]);
  return mtb.candidate;
}
