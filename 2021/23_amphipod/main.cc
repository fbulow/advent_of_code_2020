#include"incl.hh"
//#############
//#01 2 3 4 56#
//###7#8#9#a###
//  #b#c#d#e#
//  #########   
//   A B C D
// b=10, c=11, d=12, e=13

int steps(Pos from, Pos to)
{
  string_view s=
    "#############"
    "#01 2 3 4 56#"
    "###7#8#9#a###"
    "  #b#c#d#e#  "
    "  #########  ";

  struct Co
  {
    int x;
    int y;
    int width() const {return 13;}
    Co(int i)
     :x(i%width())
     ,y(i/width())
    {}
  };
  

  Co a(s.find(from));
  Co b(s.find(to));
  return abs(a.x-b.x)+abs(a.y-b.y);
}

TEST(steps, a_case)
{
  //#############
  //#01 2 3 4 56#
  //###7#8#9#a###
  //  #b#c#d#e#
  //  #########   

    EXPECT_EQ(3, steps('0', '7'));
    EXPECT_EQ(4, steps('3', '7'));
  }

int costPerStep(Amphipod a)
{
  auto i = a-'A';
  int ret =1;
  while(i-->0)
    ret*=10;
  return ret;
}

TEST(costPerStep, all_cases)
{
  EXPECT_EQ(costPerStep('A'), 1);
  EXPECT_EQ(costPerStep('B'), 10);
  EXPECT_EQ(costPerStep('C'), 100);
  EXPECT_EQ(costPerStep('D'), 1000);
}


Score solutionA(Board &board,
		function<int(Amphipod)> costPerStep = costPerStep,
		function<int(Pos, Pos)> steps = steps,
		Score score=0,
		Score bestScore = numeric_limits<Score>::max())
{
  if(score >= bestScore)
    return bestScore;
  if(board.done())
    {
      cout<<score<<endl;
      return score;
    }
  
  for(Pos from : {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e'})
    for(Pos to : board.moves(from))
      {
	auto s = steps(from, to);
	auto pod = board[from];
	auto cps = costPerStep(pod);
	auto scoreIncr = cps*s;
	std::swap(board[from], board[to]);
	bestScore =  solutionA(board,
			       costPerStep,
			       steps,
			       score + scoreIncr,
			       bestScore);
	std::swap(board[from], board[to]);
      }
  return bestScore;
}  


TEST(soution_a, actual)
{

}
TEST(soution_a, an_iteration)
{
  Board sut("#############"
	    "# A         #"	      
	    "### #B#C#D###"
	    "  #A#B#C#D#  "		      
	    "  #########  ");

  function<int(Amphipod)> costPerStep = [](Amphipod)->int{return 1;};
  function<int(Pos, Pos)> steps = [](Pos, Pos)->int{return 2;};

  
  auto ans = solutionA(sut, costPerStep, steps);
  EXPECT_EQ(2,
	    ans);
  
}

TEST(soution_a_social, an_iteration)
{
  Board sut("#############"
	    "# A         #"	      
	    "### #B#C#D###"
	    "  #A#B#C#D#  "		      
	    "  #########  ");

  auto ans = solutionA(sut, costPerStep, steps);
  EXPECT_EQ(2,
	    ans);
  
}

TEST(soution_a_social, an_two_iterations)
{
  Board sut("#############"     //#############          
	    "#     A     #"	//#01 2 3 4 56#                
	    "###B# #C#D###"	//###7#8#9#a###          
	    "  #A#B#C#D#  "	//  #b#c#d#e#            	      
	    "  #########  ");	//  #########            

  auto ans = solutionA(sut, costPerStep, steps);
  EXPECT_EQ(44,
	    ans);
  
}


TEST(soution_a, return_previous_best)
{
  struct : Board
  {
    vector<Move> moves(Pos c) const override {return {};};
  } board;

  auto f =  [](auto...){return 1;};
  EXPECT_EQ(10, 
	    solutionA(board, f,f, 20, Score(10)));
    
}

TEST(soution_a, return_new_score)
{
  struct : Board
  {
    bool done() const override {return true;}
    vector<Move> moves(Pos c) const override {return {};};
  } board;
  auto f =  [](auto...){return 1;};

  EXPECT_EQ(5, 
	    solutionA(board, f,f, 5, Score(10)));
    
}

TEST(soution_a, return_previous_best_if_failed)
{
  struct : Board
  {
    vector<Move> moves(Pos c) const override {return {};};
  } board;

  auto f =  [](auto...){return 1;};
  EXPECT_EQ(10, 
	    solutionA(board, f, f, 5, Score(10)));
    
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

TEST(solution, a)
{
  {
    Board b{
      "#############"
      "#...........#"
      "###B#C#B#D###"
      "  #A#D#C#A#  "
      "  #########  "};

    ASSERT_EQ(12521,
	      solutionA(b));
  }
  {
  Board b{
    "#############"
    "#           #"
    "###D#D#B#A###"
    "  #B#C#A#C#  "
    "  #########  "
  };
  
  EXPECT_LT(16240,
	    solutionA(b));
}
}
