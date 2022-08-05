#include "board.hh"
#include <cassert>
ostream& operator<<(ostream& cout, Board const& b)
{
  return cout<<b.s<<endl<<b.score<<endl;
}


Board::Board()
{
  for(char c: string_view("0123456789abcde"))
    {
      auto index=s.find(c);
      toIndex.insert({c, index});
      s[index]=' ';
    }
}

void Board::set(char coord, char pod)
{
  s[toIndex[coord]]=pod;
}

void Board::swap(string_view t)
{
  swap(t[0], t[1]);
}

int Board::incr(size_t ia, size_t ib) const
{
  auto pod = s[ia];
  if(pod==' ')
    pod = s[ib];
  int rate = [=]
  {
    switch(pod)
      {
      case 'A':
	return 1;
      case 'B':
	return 10;
      case 'C':
	return 100;
      case 'D':
	return 1000;
      }
    assert(false);
  }();

  static const int N = s.size()/5; //rowWidth
  return rate*( abs(int(ia)/N - int(ib)/N) + abs(int(ia)%N - int(ib)%N));
}


void Board::swap(char a, char b)
{
  auto ia = toIndex[a];
  auto ib = toIndex[b];

  score+= incr(ia,ib);
  
  auto c = s[ia];
  
  s[ia]= s[ib];
  s[ib] = c;
}
