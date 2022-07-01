#include<fstream>
#include<functional>
#include<numeric>
#include"infint.hh"
using namespace std;



using Hab = array<InfInt, 9>; //Habitat

Hab step(Hab const & pop)
{
  Hab ret;
  ret[0] = pop[1];
  ret[1] = pop[2];
  ret[2] = pop[3];
  ret[3] = pop[4];
  ret[4] = pop[5];
  ret[5] = pop[6];
  ret[6] = pop[7]+pop[0];
  ret[7] = pop[8];
  ret[8] = pop[0];
  return ret;
}

Hab cycle(Hab h, unsigned int cycles)
{
  if(cycles == 0 )
    return h;
  else
    return cycle(step(h), cycles-1);
}

auto value(Hab h)
{
  return accumulate(h.begin(), h.end(), InfInt(0));
}

using Data = vector<int>;

Data input(istream& cin)
{
  Data ret;
  int nr;
  char c;
  cin>>nr;
  while(cin.good())
    {
      ret.push_back(nr);
      cin>>c>>nr;
      assert(c==',');
    }
  return ret;
}


auto solution_a(Data const &in)
{
  Hab pop{0,0,0,0,0,0,0,0,0};
  for (auto x:in)
    pop[x]++;
  
  return value(cycle(pop, 80));
}

auto solution_b(Data const &in)
{
  Hab pop{0,0,0,0,0,0,0,0,0};
  for (auto x:in)
    pop[x]++;
  
  return value(cycle(pop, 256));

}

