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

Bin Packet::version() const
{
  auto it = data.cbegin();
  return Bin(string{it, next(it,3)});
}

Bin Packet::typeId() const
{
  auto it = next(data.cbegin(), 3);
  return Bin(string{it, next(it,3)});
}


Bin Litteral::value() const
{
  Bin ret("");
  auto it = next(data.cbegin(), 6);
  while((*it)=='1')
    {
      advance(it, 1);
      ret+=string(it, next(it,4));
      advance(it, 4);
    }
  advance(it, 1);
  ret+=string(it, next(it,4));
  return ret;
}

Iterator nextPacket(Iterator pos, Iterator begin, Iterator end)
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

Uint solutionA(Bin data)
{
  Uint ret{0};
  auto pos = data.cbegin();
  auto b = data.cbegin();
  auto e = data.cend();

  while(distance(pos, e)>3)
    {
      ret+=evalN(3,pos);
      pos = nextPacket(pos, b, e);
    }
  return ret;
}

Uint readNumberN(size_t N, Iterator &pos)
{
  auto begin = pos;
  advance(pos,N);
  return Bin(string(begin, pos));
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
          Iterator subend = next(pos, readNumberN(15,pos));
          while(pos<subend)
            arg.push_back(evalNext(pos));
          assert(pos==subend);
        }
      else // lengthTypeId == 1
        {
          auto packetCount = readNumberN(11,pos);
          while(packetCount>0)
            {
              arg.push_back(evalNext(pos));
              packetCount--;
            }
        }
      switch(typeId)
        {
        case 0:
          return accumulate(arg.cbegin(), arg.cend(), 0);
        case 1:
          return accumulate(arg.cbegin(), arg.cend(), 1,
                            [](auto a, auto b){return a*b;});
        case 2:
          return accumulate(next(arg.cbegin()), arg.cend(), *arg.cbegin(),
                            [](auto a, auto b){return (a<b)?a:b;});
        case 3:
          return accumulate(next(arg.cbegin()), arg.cend(), 0,
                            [](auto a, auto b){return (a<b)?b:a;});
        case 5:
          {
            assert(arg.size()==2);
            return arg[0]>arg[1];
          }
        case 6:
          {
            assert(arg.size()==2);
            return arg[0]<arg[1];
          }
        case 7:
          {
            assert(arg.size()==2);
            return arg[0]==arg[1];
          }
          
        default:
          {
            cout<<"Unknown typeId: "<<typeId<<endl;
              assert(false);
            return 0;
          }
        }
    }
}
