#include<fstream>

using namespace std;

using Data = vector<string>;

Data const & input()
{
  static vector<string> data;
  if(data.empty())
    {
      string s;
      cin>>s;
      while(while cin.good())
        {
          data.push_back(s);
          cin>>s;
        }
    }
  return data;
}


auto solution_a(Data const &in)
{
  return 0;
}

auto solution_b(Data const &in)
{
  return 0;
}

