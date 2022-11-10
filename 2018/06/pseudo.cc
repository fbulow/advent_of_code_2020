//pseudo code

using namespace std;

using Adjacent = array<4, Coord>;

Board::addToNextEdge(Adjacent const &a)
{
  for pos in a: add to edge if free
}

Board::floodFillOneStep()
{
  assert(all pos in edge are free);
  for( Coords pos : edge() )
    {
      if(get(pos)==Board::free)
	{
	  auto a = adjacent(pos);
	  auto v = newValue(get(pos), a);
	  assert(v!=Board::free)
	  addToNextEdge(a);
	  nxt.set(pos, v);
	}
    }
  stepDone();
}

void stepDone()
{
  swap(currentBoard, nextBoard);
  swap(currentEdge, nextEdge);
  nextEdge.clear();
}
  

string solA(Board b)
{
  while(b.thereAreUnknowns())
    b.floodFillOneStep()

  return largestExcluding(b.histogram(), b.infiniteAreas())
}

string solA(vector<Coord> const &points)
{

  return solA(Board(Box(points), points));
}

#include<gtest/gtest.h>
#include<gmock/gmock.h>
using namespace testing;

TEST(example, a)
{
  istringstream in("1, 1\n"
		   "1, 6\n"
		   "8, 3\n"
		   "3, 4\n"
		   "5, 5\n"
		   "8, 9\n");
  vector<Coord> v;
  in>>v;
  auto ans = solA(v);
  cout << "Solution A :"<<ans<<endl;
}
