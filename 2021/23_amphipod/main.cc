#include"incl.hh"
//#############
//#01 2 3 4 56#
//###7#8#9#a###
//  #b#c#d#e#
//  #########   
//   A B C D
// b=10, c=11, d=12, e=13




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

TEST(hallway, all)
{
  EXPECT_TRUE(hallway('0'));
  EXPECT_TRUE(hallway('1'));
  EXPECT_TRUE(hallway('2'));
  EXPECT_TRUE(hallway('3'));
  EXPECT_TRUE(hallway('4'));
  EXPECT_TRUE(hallway('5'));
  EXPECT_TRUE(hallway('6'));
  EXPECT_FALSE(hallway('7'));
  EXPECT_FALSE(hallway('8'));
  EXPECT_FALSE(hallway('9'));
  EXPECT_FALSE(hallway('a'));
  EXPECT_FALSE(hallway('b'));
  EXPECT_FALSE(hallway('c'));
  EXPECT_FALSE(hallway('d'));
  EXPECT_FALSE(hallway('e'));
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
  ASSERT_EQ(sut.moves('0').size(), 1);
  EXPECT_EQ(sut.moves('0')[0], 'b');
}
TEST(board, C_can_move_to_d)
  {
    Board sut("#############"
	      "#   C       #"
	      "### # # # ###"
	      "  # # # # #  "		      
	      "  #########  ");
    EXPECT_EQ(sut.moves('2').size(), 1);
    EXPECT_EQ(sut.moves('2')[0], 'd');
}

TEST(board, A_can_move_back)
  {
    Board sut("#############"
	      "#         A #"
	      "### # # # ###"
	      "  # # # # #  "		      
	      "  #########  ");
    EXPECT_EQ(sut.moves('5').size(), 1);
    EXPECT_EQ(sut.moves('5')[0], 'b');
}

TEST(board, A_can_not_move_back)
{
  Board sut("#############"
	    "#     X   A #"
	    "### # # # ###"
	    "  # # # # #  "		      
	    "  #########  ");
  EXPECT_EQ(sut.moves('5').size(), 0);
}

TEST(board, A_can_not_move_back_two)
{
  Board sut("#############"
	    "#   X     A #"
	    "### # # # ###"
	    "  # # # # #  "		      
	    "  #########  ");
  EXPECT_EQ(sut.moves('5').size(), 0);
}

TEST(board, A_can_move_back_two)
{
  Board sut("#############"
	    "# X       A #"
	    "### # # # ###"
	    "  # # # # #  "		      
	    "  #########  ");
  EXPECT_EQ(sut.moves('5').size(), 1);
}

TEST(board, A_can_move_anywhere)
{
  Board sut("#############"
	    "#           #"
	    "### # # # ###"
	    "  #B# # # #  "		      
	    "  #########  ");
  EXPECT_EQ(sut.moves('b').size(), 7);
}

TEST(board,  can_move_left)
{
  Board sut("#############"
	    "#   X       #"
	    "### # # # ###"
	    "  #B# # # #  "		      
	    "  #########  ");
  EXPECT_EQ(sut.moves('b').size(), 2);
}


TEST(board, no_clear_way)
{
  {
    struct Cut:Board
    {
      Cut(string_view s)
	:Board(s)
      {}
      
      bool clearWay(Pos from, Pos to) const override
      {
	return false;
      }
    } sut("#############"
	  "#A          #"	      
	  "### # # # ###"
	  "  # # # # #  "		      
	  "  #########  ");
    EXPECT_EQ(sut.moves('0').size(), 0);
  }
}

TEST(board, A_can_move_to_seven)
{
    Board sut("#############"
	      "#A          #"	      
	      "### # # # ###"
	      "  #A# # # #  "		      
	      "  #########  ");
    ASSERT_EQ(sut.moves('0').size(), 1);
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

TEST(board, cannot_move_when_already_home)
{
    Board sut("#############"
	      "#A          #"	      
	      "### # # # ###"
	      "  #A# # # #  "		      
	      "  #########  ");
    EXPECT_EQ(sut.moves('b').size(), 0);
}



TEST(sideRooms, allCases)
{
  auto str = [](array<char,2> x){
    string ret;
    ret+=x[0];
    ret+=x[1];
    return ret;
  };
  
  EXPECT_EQ("7b", str(sideRooms('A')));
  EXPECT_EQ("8c", str(sideRooms('B')));
  EXPECT_EQ("9d", str(sideRooms('C')));
  EXPECT_EQ("ae", str(sideRooms('D')));
}

TEST(clearWay, way_is_clear)
{
//#############
//#01 2 3 4 56#
//###7#8#9#a###
//  #b#c#d#e#
//  #########

    Board sut("#############"
	      "#           #"
	      "### # # # ###"
	      "  # # # # #  "
	      "  #########  ");

    EXPECT_TRUE(sut.clearWay('0', 'b' ));
}

TEST(clearWay, way_is_not_clear)
{
//#############
//#01 2 3 4 56#
//###7#8#9#a###
//  #b#c#d#e#
//  #########

    Board sut("#############"
	      "# X         #"
	      "### # # # ###"
	      "  # # # # #  "
	      "  #########  ");

    EXPECT_FALSE(sut.clearWay('0', 'b' ));
}
