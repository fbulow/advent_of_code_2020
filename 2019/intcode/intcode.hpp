#include <map>
#include <deque>
#include <queue>
#include <fstream>
#include <sstream>

using namespace std;
using I = long long int;

class IntCode;
ostream& operator<<(ostream &out, IntCode const &ic);

unsigned int mode(I index, I command);
unsigned int opcode(I command);


class IntCode
{
  friend ostream& operator<<(ostream &out, IntCode const &ic);
  int instructionPointer;
  map<I, I> memory;
  
public:
  I& ref(I index, I command);
  
  int relativeBase{0};
  queue<I> input;
  queue<I> output;
  IntCode(string const &s, I pos=0)
    :IntCode(istringstream(s), pos)
  {}
  
  IntCode(istream &&in, I pos=0);

  I& operator[](I i);
  bool operator==(IntCode const &other)const;

  I first(){return memory.begin()->second;}
  I last(){return memory.rbegin()->second;}

  void run();
  
  bool step();
};


