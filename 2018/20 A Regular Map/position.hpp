#pragma once
#include<compare>

using namespace std;

struct Position
{
	int row;
	int col;

	Position step(char direction) const;

	bool operator<(Position const& other) const{
		if(row< other.row)
			return true;
		else if(row==other.row)
			return col<other.col;
		else
			return false;
	}
  int operator<=> (Position const & other ) const {
		if(row < other.row)
			return -1;
		else if(row> other.row)
			return 1;
		else if (col < other .col)
			return -1;
		else if (col > other.col)
			return 1;
		else
			return 0;

	}
  bool operator==(Position const & other) const = default;
  void operator=(Position const & other);
};

