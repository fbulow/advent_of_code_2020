#include "input.hh"
#include <cassert>
State State::inp(int v) const
{
  assert(not done());
  auto ret = *this;
  ret.fn++;
  switch(fn)
    {      
    case 0:
      ret.a(v);return ret;
    case 1:
      ret.b(v);return ret;
    case 2:
      ret.c(v);return ret;
    case 3:
      ret.d(v);return ret;
    case 4:
      ret.e(v);return ret;
    case 5:
      ret.f(v);return ret;
    case 6:
      ret.g(v);return ret;
    case 7:
      ret.h(v);return ret;
    case 8:
      ret.i(v);return ret;
    case 9:
      ret.j(v);return ret;
    case 10:
      ret.k(v);return ret;
    case 11:
      ret.l(v);return ret;
    case 12:
      ret.m(v);return ret;
    case 13:
      ret.n(v);return ret;
    }
  assert(false);
}


void eql(Int&a, Int b)
{
  if(a==b)
    a=1;
  else
    a=0;
}

void Input::a(int inp){w = inp;  ;
 x *=  0;
 x +=  z;
 x %=  26;
 z /=  1;
 x +=  12;
   eql(   x ,  w);;
 eql( x ,  0);;
 y *=  0;
 y +=  25;
 y *=  x;
 y +=  1;
 z *=  y;
 y *=  0;
 y +=  w;
 y +=  7;
 y *=  x;
 z +=  y;
 }void Input::b(int inp){w = inp;  ;
 x *=  0;
 x +=  z;
 x %=  26;
 z /=  1;
 x +=  13;
   eql(   x ,  w);;
 eql( x ,  0);;
 y *=  0;
 y +=  25;
 y *=  x;
 y +=  1;
 z *=  y;
 y *=  0;
 y +=  w;
 y +=  8;
 y *=  x;
 z +=  y;
 }void Input::c(int inp){w = inp;  ;
 x *=  0;
 x +=  z;
 x %=  26;
 z /=  1;
 x +=  13;
   eql(   x ,  w);;
 eql( x ,  0);;
 y *=  0;
 y +=  25;
 y *=  x;
 y +=  1;
 z *=  y;
 y *=  0;
 y +=  w;
 y +=  10;
 y *=  x;
 z +=  y;
 }void Input::d(int inp){w = inp;  ;
 x *=  0;
 x +=  z;
 x %=  26;
 z /=  26;
 x +=  -2;
   eql(   x ,  w);;
 eql( x ,  0);;
 y *=  0;
 y +=  25;
 y *=  x;
 y +=  1;
 z *=  y;
 y *=  0;
 y +=  w;
 y +=  4;
 y *=  x;
 z +=  y;
 }void Input::e(int inp){w = inp;  ;
 x *=  0;
 x +=  z;
 x %=  26;
 z /=  26;
 x +=  -10;
   eql(   x ,  w);;
 eql( x ,  0);;
 y *=  0;
 y +=  25;
 y *=  x;
 y +=  1;
 z *=  y;
 y *=  0;
 y +=  w;
 y +=  4;
 y *=  x;
 z +=  y;
 }void Input::f(int inp){w = inp;  ;
 x *=  0;
 x +=  z;
 x %=  26;
 z /=  1;
 x +=  13;
   eql(   x ,  w);;
 eql( x ,  0);;
 y *=  0;
 y +=  25;
 y *=  x;
 y +=  1;
 z *=  y;
 y *=  0;
 y +=  w;
 y +=  6;
 y *=  x;
 z +=  y;
 }void Input::g(int inp){w = inp;  ;
 x *=  0;
 x +=  z;
 x %=  26;
 z /=  26;
 x +=  -14;
   eql(   x ,  w);;
 eql( x ,  0);;
 y *=  0;
 y +=  25;
 y *=  x;
 y +=  1;
 z *=  y;
 y *=  0;
 y +=  w;
 y +=  11;
 y *=  x;
 z +=  y;
 }void Input::h(int inp){w = inp;  ;
 x *=  0;
 x +=  z;
 x %=  26;
 z /=  26;
 x +=  -5;
   eql(   x ,  w);;
 eql( x ,  0);;
 y *=  0;
 y +=  25;
 y *=  x;
 y +=  1;
 z *=  y;
 y *=  0;
 y +=  w;
 y +=  13;
 y *=  x;
 z +=  y;
 }void Input::i(int inp){w = inp;  ;
 x *=  0;
 x +=  z;
 x %=  26;
 z /=  1;
 x +=  15;
   eql(   x ,  w);;
 eql( x ,  0);;
 y *=  0;
 y +=  25;
 y *=  x;
 y +=  1;
 z *=  y;
 y *=  0;
 y +=  w;
 y +=  1;
 y *=  x;
 z +=  y;
 }void Input::j(int inp){w = inp;  ;
 x *=  0;
 x +=  z;
 x %=  26;
 z /=  1;
 x +=  15;
   eql(   x ,  w);;
 eql( x ,  0);;
 y *=  0;
 y +=  25;
 y *=  x;
 y +=  1;
 z *=  y;
 y *=  0;
 y +=  w;
 y +=  8;
 y *=  x;
 z +=  y;
 }void Input::k(int inp){w = inp;  ;
 x *=  0;
 x +=  z;
 x %=  26;
 z /=  26;
 x +=  -14;
   eql(   x ,  w);;
 eql( x ,  0);;
 y *=  0;
 y +=  25;
 y *=  x;
 y +=  1;
 z *=  y;
 y *=  0;
 y +=  w;
 y +=  4;
 y *=  x;
 z +=  y;
 }void Input::l(int inp){w = inp;  ;
 x *=  0;
 x +=  z;
 x %=  26;
 z /=  1;
 x +=  10;
   eql(   x ,  w);;
 eql( x ,  0);;
 y *=  0;
 y +=  25;
 y *=  x;
 y +=  1;
 z *=  y;
 y *=  0;
 y +=  w;
 y +=  13;
 y *=  x;
 z +=  y;
 }void Input::m(int inp){w = inp;  ;
 x *=  0;
 x +=  z;
 x %=  26;
 z /=  26;
 x +=  -14;
   eql(   x ,  w);;
 eql( x ,  0);;
 y *=  0;
 y +=  25;
 y *=  x;
 y +=  1;
 z *=  y;
 y *=  0;
 y +=  w;
 y +=  4;
 y *=  x;
 z +=  y;
 }void Input::n(int inp){w = inp;  ;
 x *=  0;
 x +=  z;
 x %=  26;
 z /=  26;
 x +=  -5;
   eql(   x ,  w);;
 eql( x ,  0);;
 y *=  0;
 y +=  25;
 y *=  x;
 y +=  1;
 z *=  y;
 y *=  0;
 y +=  w;
 y +=  14;
 y *=  x;
 z +=  y;
  }
