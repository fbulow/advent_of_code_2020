#include"board.hh"
using namespace std;

int main(int narg, char** argc)
{
  Board b;
  b.set('7', 'D');
  b.set('8', 'D');
  b.set('9', 'B');
  b.set('a', 'A');

  b.set('b', 'B');
  b.set('c', 'C');
  b.set('d', 'A');
  b.set('e', 'C');

  if(narg==1)
    {
      while(not cin.eof())
	{
	  string s;
	  cin>>s;
	  b.swap(s);
	  cout<<b<<endl;
	}
    }
  else
    for(int i=1;i<narg;i++)
      b.swap(argc[i]);
  cout<<b<<endl;
  
  return 0;
}
