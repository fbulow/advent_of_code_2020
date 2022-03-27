#include"impl.hh"
#include<fstream>


TEST(solution, b)
{
  ifstream in("/home/fbulow/proj/advent_of_code/2021/16/input");
  string data;
  in>>data;

  Bin sut(Hex{move(data)});
  
  auto pos = sut.cbegin();
  Uint const ans = evalNext(pos);
  ASSERT_LT(1241967936, ans);
  ASSERT_GT(Uint(18446744071782855412), ans);
  cout<<ans<<endl;

}


