#pragma once
#include<functional>
#include<array>
#include<cassert>
using Int = long long int;

struct Input
{
  
  Int w{0},x{0},y{0},z{0};
protected:
  void a(int inp);
  void b(int inp);
  void c(int inp);
  void d(int inp);
  void e(int inp);
  void f(int inp);
  void g(int inp);
  void h(int inp);
  void i(int inp);
  void j(int inp);
  void k(int inp);
  void l(int inp);
  void m(int inp);
  void n(int inp);
};
 
class State: public Input
{
  int fn{0};
public:
  bool done() const {return fn>=14;}
  State inp(int) const;

  std::array<Int,4> data() const {return {w,x,y,z};}
  
  bool pass() const
  {
    assert(done());
    return z==0;
  }
};

