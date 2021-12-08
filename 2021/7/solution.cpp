#include<fstream>
#include<functional>
#include<numeric>
#include"infint.hh"
#include<algorithm>
using namespace std;

using Data = vector<int>;

Data input(istream& cin)
{
  Data ret;
  
  int nr;
  char c=',';
  
  cin>>nr>>c;
  while(not cin.eof())
    {
      ret.push_back(nr);
      cin>>nr>>c;
    }
  ret.push_back(nr);
  return ret;
}

int cost(int target, Data const & pos)
{
  return accumulate(pos.begin(),
                    pos.end(),
                    int(0),
                    [target](int p, int sum){ return sum+abs(p - target); });
}

auto solution_a(Data const &in)
{
  auto const Max = *max_element(in.begin(), in.end());
  int best = cost(Max, in);
  auto const Min = *min_element(in.begin(), in.end());
  for (auto t = Min; t<Max; t++)
    {
      auto c = cost(t, in);
      if(c<best)
        best=c;
    }
  return best;
}

auto solution_b(Data const &in)
{
  return "";

}

