#include<array>
#include<iostream>
using namespace std;

using Int = long long int;

struct Alu{
  Int w=0,x=0,y=0,z=0;
  size_t it{0};
  array<Int,14> input;
  void inp(Int &a)
  {
    //- Read an input value and write it to variable a.
    a=input[it++];
  }
  
  void add(Int& a, Int b)
  {
    //- Add the value of a to the value of b, then store the result in variable a.
    a+=b;
  }
  
  void mul(Int& a, Int b)
  {
    //- Multiply the value of a by the value of b, then store the result in variable a.
    a*=b;
  }

  void div(Int& a, Int b)
  {
    //- Divide the value of a by the value of b, truncate the result to an integer, then store the result in variable a. (Here, "truncate" means to round the value toward zero.)
    a/=b;
  }

  void mod(Int& a, Int b)
  {
    //- Divide the value of a by the value of b, then store the remainder in variable a. (This is also called the modulo operation.)
    a%=b;
  }
  void eql(Int& a, Int b)
  {
    //- If the value of a and b are equal, then store the value 1 in variable a. Otherwise, store the value 0 in variable a.
    a=(a==b)?1:0;
  }

  Int run()
  {
    w=0;
    x=0;
    y=0;
    z=0;
    it=0;
    
    inp(w);
    mul(x, 0);
    add(x, z);
    mod(x, 26);
    div(z, 1);
    add(x, 12);
    eql(x, w);
    eql(x, 0);
    mul(y, 0);
    add(y, 25);
    mul(y, x);
    add(y, 1);
    mul(z, y);
    mul(y, 0);
    add(y, w);
    add(y, 7);
    mul(y, x);
    add(z, y);
    inp(w);
    mul(x, 0);
    add(x, z);
    mod(x, 26);
    div(z, 1);
    add(x, 13);
    eql(x, w);
    eql(x, 0);
    mul(y, 0);
    add(y, 25);
    mul(y, x);
    add(y, 1);
    mul(z, y);
    mul(y, 0);
    add(y, w);
    add(y, 8);
    mul(y, x);
    add(z, y);
    inp(w);
    mul(x, 0);
    add(x, z);
    mod(x, 26);
    div(z, 1);
    add(x, 13);
    eql(x, w);
    eql(x, 0);
    mul(y, 0);
    add(y, 25);
    mul(y, x);
    add(y, 1);
    mul(z, y);
    mul(y, 0);
    add(y, w);
    add(y, 10);
    mul(y, x);
    add(z, y);
    inp(w);
    mul(x, 0);
    add(x, z);
    mod(x, 26);
    div(z, 26);
    add(x, -2);
    eql(x, w);
    eql(x, 0);
    mul(y, 0);
    add(y, 25);
    mul(y, x);
    add(y, 1);
    mul(z, y);
    mul(y, 0);
    add(y, w);
    add(y, 4);
    mul(y, x);
    add(z, y);
    inp(w);
    mul(x, 0);
    add(x, z);
    mod(x, 26);
    div(z, 26);
    add(x, -10);
    eql(x, w);
    eql(x, 0);
    mul(y, 0);
    add(y, 25);
    mul(y, x);
    add(y, 1);
    mul(z, y);
    mul(y, 0);
    add(y, w);
    add(y, 4);
    mul(y, x);
    add(z, y);
    inp(w);
    mul(x, 0);
    add(x, z);
    mod(x, 26);
    div(z, 1);
    add(x, 13);
    eql(x, w);
    eql(x, 0);
    mul(y, 0);
    add(y, 25);
    mul(y, x);
    add(y, 1);
    mul(z, y);
    mul(y, 0);
    add(y, w);
    add(y, 6);
    mul(y, x);
    add(z, y);
    inp(w);
    mul(x, 0);
    add(x, z);
    mod(x, 26);
    div(z, 26);
    add(x, -14);
    eql(x, w);
    eql(x, 0);
    mul(y, 0);
    add(y, 25);
    mul(y, x);
    add(y, 1);
    mul(z, y);
    mul(y, 0);
    add(y, w);
    add(y, 11);
    mul(y, x);
    add(z, y);
    inp(w);
    mul(x, 0);
    add(x, z);
    mod(x, 26);
    div(z, 26);
    add(x, -5);
    eql(x, w);
    eql(x, 0);
    mul(y, 0);
    add(y, 25);
    mul(y, x);
    add(y, 1);
    mul(z, y);
    mul(y, 0);
    add(y, w);
    add(y, 13);
    mul(y, x);
    add(z, y);
    inp(w);
    mul(x, 0);
    add(x, z);
    mod(x, 26);
    div(z, 1);
    add(x, 15);
    eql(x, w);
    eql(x, 0);
    mul(y, 0);
    add(y, 25);
    mul(y, x);
    add(y, 1);
    mul(z, y);
    mul(y, 0);
    add(y, w);
    add(y, 1);
    mul(y, x);
    add(z, y);
    inp(w);
    mul(x, 0);
    add(x, z);
    mod(x, 26);
    div(z, 1);
    add(x, 15);
    eql(x, w);
    eql(x, 0);
    mul(y, 0);
    add(y, 25);
    mul(y, x);
    add(y, 1);
    mul(z, y);
    mul(y, 0);
    add(y, w);
    add(y, 8);
    mul(y, x);
    add(z, y);
    inp(w);
    mul(x, 0);
    add(x, z);
    mod(x, 26);
    div(z, 26);
    add(x, -14);
    eql(x, w);
    eql(x, 0);
    mul(y, 0);
    add(y, 25);
    mul(y, x);
    add(y, 1);
    mul(z, y);
    mul(y, 0);
    add(y, w);
    add(y, 4);
    mul(y, x);
    add(z, y);
    inp(w);
    mul(x, 0);
    add(x, z);
    mod(x, 26);
    div(z, 1);
    add(x, 10);
    eql(x, w);
    eql(x, 0);
    mul(y, 0);
    add(y, 25);
    mul(y, x);
    add(y, 1);
    mul(z, y);
    mul(y, 0);
    add(y, w);
    add(y, 13);
    mul(y, x);
    add(z, y);
    inp(w);
    mul(x, 0);
    add(x, z);
    mod(x, 26);
    div(z, 26);
    add(x, -14);
    eql(x, w);
    eql(x, 0);
    mul(y, 0);
    add(y, 25);
    mul(y, x);
    add(y, 1);
    mul(z, y);
    mul(y, 0);
    add(y, w);
    add(y, 4);
    mul(y, x);
    add(z, y);
    inp(w);
    mul(x, 0);
    add(x, z);
    mod(x, 26);
    div(z, 26);
    add(x, -5);
    eql(x, w);
    eql(x, 0);
    mul(y, 0);
    add(y, 25);
    mul(y, x);
    add(y, 1);
    mul(z, y);
    mul(y, 0);
    add(y, w);
    add(y, 14);
    mul(y, x);
    add(z, y);
    return z;
  }
};
template<int depth>
bool iterate(Alu &a)
{
  if constexpr (depth<14)
    {
      for(Int i = 9 ; i>0 ;i--)
        {
          a.input[depth] = i;
          if(iterate<depth+1>(a))
            return true;
        }
      return false;
    }
  else
    {
      return a.run()==0;
    }
                 
}

int main()
{
  Alu sut;
  iterate<0>(sut);
  for(auto x:sut.input)
    cout<<x<<", ";
  cout<<endl;
  return 0;
}
