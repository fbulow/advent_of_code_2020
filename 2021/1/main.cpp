#include <fstream>
#include <string>
#include <array>

using namespace std;

template<int width>
class Window{
  template<int N>
  friend istream& operator>>(istream& in, Window<N> &w);
  array<int, width> data;
  int position{0};
  int next_position() const
  {
    return (position+1)%width;
  }
  int newest_value() const
  {return data[position];}

  int oldest_value() const
  {return data[next_position()];}
    
public:
  Window(istream &in)
  {
    for(auto i = 0; i<width ;i++)
      in>>(*this);
  }
  bool increased() const
  {
    return newest_value()>oldest_value();
  }
};
 
template<int width>
istream& operator>>(istream& in, Window<width> &w)
{
  w.position = w.next_position();
  in>>w.data[w.position];
  return in;
}

template<int width>
unsigned int sliding_average_increases(istream &in)
{
  Window<width+1> w(in);
  
  unsigned int ret{0};
  while(not in.eof())
    {
      if(w.increased())
        ret++;
      in>>w;
    }
  return ret;
}

auto solution_a(istream &in){return sliding_average_increases<1>(in);}
auto solution_b(istream &in){return sliding_average_increases<3>(in);}
