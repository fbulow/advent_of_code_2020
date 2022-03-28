#include"impl.hh"
#include<fstream>

Uint evalNextPacketB(Parser &p)
{
  Uint ret{0};
  auto version = p.get(3);
  auto typeId = p.get(3);
  if(typeId == 4)
    {
      while(1==p.get(1).toInt())
        ret = ret*16 + p.get(4);
      ret = ret*16 + p.get(4);
      return ret;
    }
  else
    {
      vector<Uint> arg;
      if(0 == p.get(1).toInt()) //length type ID
        {
          auto end = next(p.getPos(), p.get(15));
          while ( p.getPos()<end )
            arg.push_back(evalNextPacketB(p));
        }
      else
        {
          auto count = p.get(11);
          while(count>0)
            {
              arg.push_back(evalNextPacketB(p));
              count--;
            }
        }
      return aggregate(typeId, arg);
    }
}

Uint evalNextPacket(Parser &p)
{
  auto ret = p.get(3);//Version
  switch(p.get(3).toInt()) //type ID
    {
    case 4:
      {
        while(1==p.get(1))
          p.get(4);
        p.get(4);
        return ret;
      }
    default:
      {
        if(0 == p.get(1)) //length type ID
          {
            auto end = next(p.getPos(), p.get(15));
            while ( p.getPos()<end )
              ret+=evalNextPacket(p);
          }
        else
          {
            auto count = p.get(11);
            while((count--)>0)
              ret+=evalNextPacket(p);
          }
        return ret;
      }
    }
}

Uint solutionA(Bin data)
{
  Parser p(move(data));
  return evalNextPacket(p);
}

Uint solutionB(Bin data)
{
  Parser p(move(data));
  return evalNextPacketB(p);
}

TEST(solution, b)
{
  ifstream in("/home/fbulow/proj/advent_of_code/2021/16/input");
  string data;
  in>>data;

  Uint const ans = solutionB(Bin(Hex{data}));
  ASSERT_LT(Uint(1241967936), ans);
  ASSERT_GT(Uint("18446744071782855412"), ans);
  ASSERT_EQ(Uint(912901337844), ans);

}


