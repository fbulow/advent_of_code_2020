#include<gtest/gtest.h>
#include<vector>
#include<string_view>
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
  Board(string_view s)
  {
    //#############
    //#01 2 3 4 56#
    //###7#8#9#a###
    //  #b#c#d#e#
    //  #########
    //
    // b=10, c=11, d=12, e=13

    size_t i{0};
    data[0] = s[14];
    data[1] = s[15];
    data[2] = s[17];
    data[3] = s[19];
    data[4] = s[21];
    data[5] = s[23];
    data[6] = s[24];
    data[7] = s[29];
    data[8] = s[31];
    data[9] = s[33];
    data[10] = s[35]; //a
    data[11] = s[42]; //b
    data[12] = s[44]; //c
    data[13] = s[46]; //d
    data[14] = s[48]; //d

  }

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

  virtual bool clearWay(Pos from, Pos to)
  {
    switch(from)
      {
      case '0':
	  string path = "17b";
	  return all_of(path.begin(),
			path.end(),
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
  virtual vector<Move> moves(Pos c) const
  {
    auto const amphipod = get(c);
    if(amphipod==' ')
      return {};
      
    
    if(hallway(c))
      {
	auto room = sideRooms(amphipod);
	auto seven = room[0];
	auto b = room[1];
	if(get(b)==' ')
	  return {b};
	else if(get(b)==amphipod)
	  if(get(seven)==' ')
	    return {seven};
	return {};
      }
  }
  
  virtual bool done() const 
  {
    //#############
    //#01 2 3 4 56#
    //###7#8#9#a###
    //  #b#c#d#e#
    //  #########
    return
      ((*this)['7']=='A') 
      and ((*this)['b']=='A') 
      and ((*this)['8']=='B') 
      and ((*this)['c']=='B') 
      and ((*this)['9']=='C') 
      and ((*this)['d']=='C') 
      and ((*this)['a']=='D') 
      and ((*this)['e']=='D')
      ;
  }
};
