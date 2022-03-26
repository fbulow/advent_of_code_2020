#include"impl.hh"
#include<fstream>


TEST(solution, b)
{
  ifstream in("/home/fbulow/proj/advent_of_code/2021/16/input");
  string data;
  in>>data;

  Bin sut(Hex{move(data)});
  auto pos = sut.cbegin();
  EXPECT_LT(1241967936, evalNext(pos));

}


