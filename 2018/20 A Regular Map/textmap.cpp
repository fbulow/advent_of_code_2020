#include "textmap.hpp"
#include <sstream>
#include <cassert>
#include "doors.hpp"
Textmap::Textmap(string in)
{
  istringstream x(in);
  init(x);
}

Textmap::Textmap(istream &in)
{
  init(in);
}

void Textmap::init(istream &in)
{
  char c = in.get();
  vector<char> row;
  while(not in.eof())
    {
      if(c=='\n')
        {
          data.push_back(row);
          row.clear();
        }
      else
          row.push_back(c);
      c = in.get();
    }
  assert(not data.empty());
}

ostream& operator<<(ostream& out, Textmap const &x)
{
  for(auto const & q: x.data)
    {
      for(char c: q)
        out<<c;
      out<<endl;
    }
  return out;
}

char Textmap::operator()(size_t row, size_t column) const {
    return data[row][column];
}

void Textmap::write_to(Doors &d) const {
    assert(not data.empty());
    for(size_t row=0;row<data.size();row++)
        for(size_t col=0;col<data[0].size();col++)
            switch(data[row][col])
            {
                case '-':
                {
                    int r = row/2;
                    int c = col/2;
                    d.push({r-1,c}, {r,c});
                    break;
                }
                case'|':
                {
                    int r = row/2;
                    int c = col/2;
                    d.push({r,c-1}, {r,c});
                    break;
                }
                case'X':
                    d.position={row/2, col/2};
            }
}

int operator<=>(RegMap::Caret left, RegMap::Caret right)
{
	if (left<right)
		return -1;
	else if(left==right)
		return 0;
	else
		return 1;
}
struct PosMap{
	RegMap::Caret c;
	RegMap &rm;
	Position pos;

	bool operator<(PosMap const &other)
	{
		switch (c <=> other.c)
		{
		case 1:
			return true;
		case -1:
			return false;
		case 0:
			switch (pos <=> other.pos)
			{
			case 1:
				return true;
			case -1:
				return false;
			case 0:
				return false;
			}
		}
	}
};

Doors::Doors(RegMap const &r)
{

}
