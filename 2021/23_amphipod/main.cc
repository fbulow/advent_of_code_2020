#include<gtest/gtest.h>
#include<vector>
#include<string_view>
using namespace std;
//#############
//#01 2 3 4 56#
//###7#8#9#a###
//  #b#c#d#e#
//  #########   
//
// b=10, c=11, d=12, e=13

using Score = unsigned int;

using Move = char;
using Pos = char;

bool hallway(Pos p)
{
  return p<'7';
}

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
  
  virtual Score score() const {return {};}
  virtual vector<Move> moves() const {return {};}
  virtual vector<Move> moves(Pos c) const
  {
    switch((*this)[c])
      {
      case ' ':
	return {};
      case 'A':
	if (hallway(c))
	  {
	    switch((*this)['b'])
	      {
	      case ' ':
		return {'b'};
	      case 'A':
		if((*this)['7']==' ')
		  return {'7'};
		else
		  return {};
	      default:
		return {};
	      }
	  }
      };
    return {};
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


Score solutionA(Board const &board, Score bestScore = 10)
{
  switch(board.status())
    {
    case Board::Status::Failed:
      return bestScore;
    case Board::Status::Finished:
      return min(board.score(), bestScore);
    }
}

TEST(soution_a, return_previous_best)
{
  struct : Board
  {
    Status status() const override
    {return Status::Finished;}
    
    Score score() const override
    {
      return 20;
    }
    
  } board;

  EXPECT_EQ(10, 
	    solutionA(board, Score(10)));
    
}

TEST(soution_a, return_new_score)
{
  struct : Board
  {
    Status status() const override
    {return Status::Finished;}
    
    Score score() const override
    {
      return 5;
    }
    
  } board;

  EXPECT_EQ(5, 
	    solutionA(board, Score(10)));
    
}

TEST(soution_a, return_previous_best_if_failed)
{
  struct : Board
  {
    Status status() const override
    {return Status::Failed;}
    
    Score score() const override
    {
      return 5;
    }
    
  } board;

  EXPECT_EQ(10, 
	    solutionA(board, Score(10)));
    
}

TEST(soution_a, status_InProgress_when_there_are_moves)
{
  struct : Board
  {
    // Status status() const override
    // {return Status::InProgress;}
    
    vector<Move> moves() const override
    {
      return {{}};//contains one
    }
    
  } sut;

  EXPECT_EQ(Board::Status::InProgress,
	    sut.status());
}

TEST(soution_a, failed_when_not_done_and_no_moves)
{
  struct : Board
  {
    vector<Move> moves() const override
    {
      return {};//contains one
    }

    bool done() const override
    {
      return false;
    }
    
  } sut;

  EXPECT_EQ(Board::Status::Failed,
	    sut.status());
}

TEST(soution_a, done_when_done)
{
  struct : Board
  {
    bool done() const override
    {
      return true;
    }
    
  } sut;

  EXPECT_EQ(Board::Status::Finished,
	    sut.status());
}

TEST(board, ctor)
{
  // ############# 
  // #           # 
  // ###a#b#c#d### 
  //   #a#b#c#d#	  
  //   #########   
  //
  // b=10, c=11, d=12, e=13

    Board sut("#############"
	      "#01 2 3 4 56#"	      
	      "###7#8#9#a###"
	      "  #b#c#d#e#  "		      
	      "  #########  ");
  
  // EXPECT_EQ('0', sut[0]);
  // EXPECT_EQ('1', sut[1]);
  // EXPECT_EQ('2', sut[2]);
  // EXPECT_EQ('3', sut[3]);
  // EXPECT_EQ('4', sut[4]);
  // EXPECT_EQ('5', sut[5]);
  // EXPECT_EQ('6', sut[6]);
  // EXPECT_EQ('7', sut[7]);
  // EXPECT_EQ('8', sut[8]);
  // EXPECT_EQ('9', sut[9]);
  // EXPECT_EQ('a', sut[10]);
  // EXPECT_EQ('b', sut[11]);
  // EXPECT_EQ('c', sut[12]);
  // EXPECT_EQ('d', sut[13]);
  // EXPECT_EQ('e', sut[14]);

  EXPECT_EQ('0', sut['0']);
  EXPECT_EQ('1', sut['1']);
  EXPECT_EQ('2', sut['2']);
  EXPECT_EQ('3', sut['3']);
  EXPECT_EQ('4', sut['4']);
  EXPECT_EQ('5', sut['5']);
  EXPECT_EQ('6', sut['6']);
  EXPECT_EQ('7', sut['7']);
  EXPECT_EQ('8', sut['8']);
  EXPECT_EQ('9', sut['9']);
  EXPECT_EQ('a', sut['a']);
  EXPECT_EQ('b', sut['b']);
  EXPECT_EQ('c', sut['c']);
  EXPECT_EQ('d', sut['d']);
  EXPECT_EQ('e', sut['e']);

  
}

TEST(board, is_done)
{
    Board sut("#############"
	      "#           #"	      
	      "###A#B#C#D###"
	      "  #A#B#C#D#  "		      
	      "  #########  ");
    EXPECT_TRUE(sut.done());
}

TEST(board, is_not_done)
{
    Board sut("#############"
	      "#           #"	      
	      "###A#C#B#D###"
	      "  #A#B#C#D#  "		      
	      "  #########  ");
    EXPECT_FALSE(sut.done());
}

TEST(board, no_amphipod_no_move)
{
    Board sut("#############"
	      "#           #"	      
	      "### # # # ###"
	      "  # # # # #  "		      
	      "  #########  ");
    EXPECT_TRUE(sut.moves('0').empty());
}

TEST(board, A_can_move_to_b)
{
    Board sut("#############"
	      "#A          #"	      
	      "### # # # ###"
	      "  # # # # #  "		      
	      "  #########  ");
    EXPECT_EQ(sut.moves('0').size(), 1);
    EXPECT_EQ(sut.moves('0')[0], 'b');
}

TEST(board, A_can_move_to_seven)
{
    Board sut("#############"
	      "#A          #"	      
	      "### # # # ###"
	      "  #A# # # #  "		      
	      "  #########  ");
    EXPECT_EQ(sut.moves('0').size(), 1);
    EXPECT_EQ(sut.moves('0')[0], '7');
}

TEST(board, A_can_not_move_to_seven)
{
    Board sut("#############"
	      "#A          #"	      
	      "### # # # ###"
	      "  #B# # # #  "		      
	      "  #########  ");
    EXPECT_EQ(sut.moves('0').size(), 0);
}


TEST(board, A_can_not_move_to_seven_because_it_is_taken)
{
    Board sut("#############"
	      "#A          #"	      
	      "###B# # # ###"
	      "  #A# # # #  "		      
	      "  #########  ");
    EXPECT_EQ(sut.moves('0').size(), 0);
}



