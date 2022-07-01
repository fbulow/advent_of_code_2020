#include<gtest/gtest.h>
#include<vector>
#include<string_view>
#include<algorithm>
#include<iterator>

#include"amphipod.hh"

using namespace std;

using Score = unsigned int;
using Move = char;
using Pos = char;

bool hallway(Pos p);
array<char, 2> sideRooms(Amphipod a);

struct Paths{
  string_view left;
  string_view right;
};

class Board{
  array<char, 14> data;
public:
  Board(){}
  Board(string_view s);

  virtual void fromTo(Pos from, Pos to)
  {
    //TODO implement me
  }

private:
  char& get(char i)
  {

  }
public:
  
  char operator[](char i) const;

  
  char& operator[](char i);

  
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
  virtual vector<Move> moves() const {return {};}
  virtual vector<Move> moves(Pos c) const;
  virtual vector<Move> movesFromHallway(Pos c)const;
  
  virtual bool done() const ;
};

