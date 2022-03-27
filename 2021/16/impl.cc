#include "impl.hh"
#include<string_view>
#include<cassert>
#include<string>
using namespace std;


Bin::Bin(string const &h)
  :string(h)
{}
Bin::operator Uint  () const
{
  return accumulate(cbegin(), cend(), Uint(0),
                    [](Uint sum, Uint nxt) ->Uint
                    {
                      return 2*sum+( (nxt=='0')?0:1 );
                    });
}
Bin::Bin(Hex const &h)

  :string(expand(h))
{}

string_view toBinary(char c)
{
  switch(c)
    {
    case '0':return "0000";
    case '1':return "0001";
    case '2':return "0010";
    case '3':return "0011";
    case '4':return "0100";
    case '5':return "0101";
    case '6':return "0110";
    case '7':return "0111";
    case '8':return "1000";
    case '9':return "1001";
    case 'A':return "1010";
    case 'B':return "1011";
    case 'C':return "1100";
    case 'D':return "1101";
    case 'E':return "1110";
    case 'F':return "1111";
    default:
      assert(false);
    }
}
string expand(string const & in)
{
  string ret;
  ret.reserve(4*size(in));
  for(char c:in)
    ret+=toBinary(c);
  return ret;
}

Iterator nextPacket(Iterator pos)
{
  advance(pos,3); //past version
  Uint typeId = Bin(string{pos, next(pos,3)});
  advance(pos,3); //past type id
  
  if(typeId == 4)
    {
      while(*pos=='1')
        advance(pos,5);//Past litteral block
      advance(pos,5);//Past last litteral block
    }
  else
    {
      auto lengtTypeId = *pos;
      advance(pos,1);
      if(lengtTypeId == '0')
        advance(pos,15);
      else
        advance(pos,11);
    }
  return pos;
}

Uint evalN(size_t n, Iterator begin)
{
  return Bin{string(begin, next(begin, n))};
}


Uint readNumberN(size_t N, Iterator &pos)
{
  auto begin = pos;
  advance(pos,N);
  return Bin(string(begin, pos));
}


Uint aggregate(Uint typeId, vector<Uint> const &arg)
{
  switch(typeId)
    {
    case 0:
      assert(arg.size()>0);
      return accumulate(arg.cbegin(), arg.cend(), 0);
    case 1:
      assert(arg.size()>0);
      return accumulate(arg.cbegin(), arg.cend(), 1,
                        [](Uint a, Uint b) ->Uint
                        {return a*b;});
    case 2:
      assert(arg.size()>0);
      return *min_element(arg.cbegin(), arg.cend());
    case 3:
      return *max_element(arg.cbegin(), arg.cend());

    case 5:
      {
        assert(arg.size()==2);
        return (arg[0]>arg[1])?1:0;
      }
    case 6:
      {
        assert(arg.size()==2);
        return (arg[0]<arg[1])?1:0;
      }
    case 7:
      {
        assert(arg.size()==2);
        return (arg[0]==arg[1])?1:0;
      }
          
    default:
      {
        cout<<"Unknown typeId: "<<typeId<<endl;
        assert(false);
        return 0;
      }
    }

}

Uint evalNext(Iterator& pos)//, Iterator end)
{
  advance(pos,3); //skip version
  auto typeId = readNumberN(3, pos);
  if(typeId == 4)
    {
        Uint ret{0};
        while(1 == readNumberN(1, pos))
          {
            ret*=Uint(Bin("10000"));
            ret+=readNumberN(4,pos);
          }
        ret*=Uint(Bin("10000"));
        ret+=readNumberN(4,pos);
        return ret;
    }
  else
    {
      vector<Uint> arg;
      auto lengthTypeId = readNumberN(1,pos);
      if (lengthTypeId == 0)
        {
          auto bitcount = readNumberN(15,pos);
          Iterator subend = next(pos, bitcount);
          while(pos<subend)
            arg.push_back(evalNext(pos));
          assert(pos==subend);
        }
      else // lengthTypeId == 1
        {
          auto const tot_size = readNumberN(11,pos);
          auto packetCount = tot_size;
          while(packetCount>0)
            {
              arg.push_back(evalNext(pos));
              packetCount--;
            }
          assert(arg.size()==tot_size);
        }
      return aggregate(typeId, arg);
    }
}

Uint Parser::get(unsigned int N)
{
  auto beg = pos;
  advance(pos,N);
  return accumulate(beg, pos, Uint(0),
                    [](Uint sum, auto x)
                    {return 2*sum+((x=='1')?1:0);});
}

Iterator Parser::getPos() const
{
  return pos;
}

Uint solutionA(Bin data)
{
  Parser p(move(data));
  Uint ret{0};
  
  while(p.remaining()>3)
    {
      ret+=p.get(3);
      Uint typeId = p.get(3);
      if(typeId == 4)
        {
          while(1==p.get(1))
            p.get(4);
          p.get(4);
        }
      else
        {
          auto lengtTypeId = p.get(1);
          if(lengtTypeId == 0)
            p.get(15);
          else
            p.get(11);
        }
    }
  return ret;
}
