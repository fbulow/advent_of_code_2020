#pragma once
// using Value = strong::type<int, class Value_,
//                           strong::arithmetic,
//                           strong::ordered,
//                           strong::incrementable,
//                           strong::equality>;

class Pair;

class Cell
{
  unique_ptr<Pair> ptr;
  int val;
public:
  Cell(int v)
    :val(v)
  {}
  Cell(Pair const &p)
    :ptr{make_unique<Pair>(p)}
  {
    
  }

  Cell(Cell const & other)
  {
    if (other.ptr)
      ptr = make_unique<Pair>(*other.ptr);
    else
      val=other.val;
  }

  bool is_int() const {return not ptr;}
  bool is_pair() const {return bool(ptr);}
  int& value() {return val;}
  int  value() const {return val;}
  Pair&       pair(){return *ptr;}
  Pair const& pair() const {return *ptr;}
};


class Pair{
protected:
  Cell head_;
  Cell tail_;
  Pair* parent{nullptr};
  void setParent(Pair* parent)
  {
    this->parent = parent;
  }
public:
  Pair(auto const& head, auto const & tail)
  :head_(head)
  ,tail_(tail)
  {
  }
  void setHead(auto x)
  {
    head_=x;
    if(head_.is_pair())
      head_.pair().setParent(this);
  }
  void setTail(auto x)
  {
    tail_=x;
    if(tail_.is_pair())
      tail_.pair().setParent(this);
  }
  Cell const & head() const { return head_; }
  Cell const & tail() const { return tail_; }
  Cell       & head()       { return head_; }
  Cell       & tail()       { return tail_; }
  
};




ostream& operator<<(ostream& cout, Pair const & p);

ostream& operator<<(ostream& cout, Cell const &c)
{
  if(c.is_int())
    cout<< c.value();
  else
    cout<< c.pair();
  return cout;
}

ostream& operator<<(ostream& cout, Pair const & p)
{
  cout
    <<"["
    << p.head()
    <<","
    << p.tail()
    <<"]";
  return cout;
}

// ostream& operator<<(ostream& cout, Pair*p)
// {
//   cout<< *p;
//   return cout;
// }


TEST(Pair_, print)
{
  cout<<Pair(1, 2)<<endl;
  cout<<Pair(9, Pair(8,2))<<endl;
  //  cout<<Pair(1,1)<<endl;
  //  cout<<Pair(1,Pair(2,2))<<endl;
}


Pair operator+(Pair const &a, Pair const &b)
{
  return Pair(a,b);
}

TEST(Pair_, add)
{
  {
    auto sut = Pair(1,2) + Pair(Pair(3,4),5);
    ostringstream out;
    out<< sut;
    EXPECT_EQ("[[1,2],[[3,4],5]]", out.str());
  }
}

class FromTheDepth
{
public:
  bool found;
  optional<int> left;
  optional<int> right;
};

FromTheDepth fromTheDepth(Pair const &p, unsigned int const depth=4)
{
  if(depth==0)
    return {true, p.head().value(), p.tail().value()};
  else
    {
      if(p.head().is_pair())
        {
          auto x = fromTheDepth(p.head().pair(), depth-1);
          if(x.found)
            {
              
            }
          return x;
        }
      else if(p.tail().is_pair())
        auto x = fromTheDepth(p.tail().pair(), depth-1);
      else
        return {false, {}, {}};
    }
}
TEST(Pair_, explode)
{
  auto sut = Pair(Pair(Pair(Pair(Pair(9,8),1),2),3),4);
}
