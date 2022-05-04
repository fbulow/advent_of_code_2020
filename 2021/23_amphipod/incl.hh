#include<gtest/gtest.h>
#include<vector>
#include<string_view>
#include<algorithm>

using namespace std;

using Score = unsigned int;
using Move = char;
using Pos = char;
using Amphipod = char;

bool hallway(Pos p);
array<char, 2> sideRooms(Amphipod a);

class Board{
  array<char, 14> data;
public:
  Board(){}
  Board(string_view s);

  char operator[](char i) const
  {
    if((i>='0') and (i<='9'))
       return data[i-'0'];
    else
      return data[10+(i-'a')];
  }
  
  enum class Status {Finished, Failed, InProgress};
  virtual Status status() const
  {
    if(done())
      return Status::Finished;
    else if(moves().size()>0)
      return Status::InProgress;
    else
      return Status::Failed;
  }

  virtual bool clearWay(Pos from, Pos to) const
  {
    switch(from)
      {
      case '0':
	  string path = "17b";
	  return all_of(path.begin(),
			next(find(path.begin(), path.end(), to)),
			[this](Pos p){return (*this)[p]==' ';});
      }
    return true;
  }
private:
  Amphipod get(Pos c) const
  {return (*this)[c];}
  
public:
  virtual Score score() const {return {};}
  virtual vector<Move> moves() const {return {};}
  virtual vector<Move> moves(Pos c) const;
  
  virtual bool done() const ;
};
