#include <limits>

using I = size_t;

class QuickCups:public list<I>
{
  size_t N;
  list<I> pickUp{};
  vector<list<I>::iterator> qfind; 
  
  void append(I value)
  {
    assert(value<qfind.size());
    push_back(value);
    qfind[value] = prev(end());
  }

public:

  QuickCups(string s, I size)
    :N{size}
  {
    qfind.resize(size+1);
    for(char c:s)
      append(c-'0');
    for(I i = s.size(); i<size ;i++)
      append(i+1);
  }

  string toString()
  {
    ostringstream ret;
    ret<<*begin();
    auto it = next(begin());
    while(it!=end())
      {
        ret<<" "<<*it;
        advance(it, 1);
      }
    return ret.str();
  }

  size_t nextDown(size_t c)
  {
    if(c<=1)
      return N;
    else
      return c-1;
  }

  void shiftUntilFirstOneIs(size_t c)
  {
    splice(end(), *this, begin(), qfind[c]);
  }
  
  void move()
  {
    pickUp.splice(pickUp.begin(), *this, next(begin()), next(begin(), 4));
    auto nd = nextDown(*begin());
    while (find(pickUp.begin(),
                pickUp.end(), nd)!=pickUp.end())
      nd = nextDown(nd);
    splice(next(qfind[nd]), pickUp);
    splice(end(), *this, begin(), next(begin()));
  }
};

string sovleA(string s)
{
  QuickCups x(s,9);
  for(auto i=0;i<100;i++)
    x.move();
  x.shiftUntilFirstOneIs(1);

  ostringstream ret;
  for(auto q:x)
    ret<<q;
  
  return ret.str().substr(1);
}

unsigned long int solveB(string s)
{
  QuickCups x(s,1000000);
  for(auto i=0;i<10000000;i++)
    x.move();
  x.shiftUntilFirstOneIs(1);
  return (*next(x.begin(),1)) * (*next(x.begin(),2));
}
