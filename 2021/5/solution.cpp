#include<fstream>
#include<functional>
using namespace std;

class Column{
  int col;
public:
  int& operator()()
  {
    return col;
  }
  int const & operator()() const
  {
    return col;
  }
  Column operator-(Column const & other) const
  {
    Column ret;
    ret.col = col-other.col;
    return ret;
  }
  bool operator<(Column const & other) const
  {
    return col<other();
  }

  void operator+=(Column const & other)
  {
    col+=other.col;
  }

};


class Row{
  int col;
public:
  Row operator-(Row const & other) const
  {
    Row ret;
    ret.col = col-other.col;
    return ret;
  }
  int& operator()()
  {
    return col;
  }
  int const & operator()() const
  {
    return col;
  }
  bool operator<(Row const & other) const
  {
    return col<other.col;
  }
  void operator+=(Row const & other)
  {
    col+=other.col;
  }
};

bool operator==(Row const &a, Row const &b)
{
  return a()==b();
}
bool operator==(Column const &a, Column const &b)
{
  return a()==b();
}



class Direction
{
  Row r;
  Column c;
public:
  void minimize()
  {
    if(r()!=0)
      r()/=abs(r());
    if(c()!=0)
      c()/=abs(c());
  }
  Row const & row() const
  {return r;}
  Column const & column() const
  {return c;}
  
  Direction(Row r, Column c)
    :r(r)
    ,c(c)
  {
  }
};

struct Point: tuple<Row, Column>
{
  friend istream& operator>>(istream& in, Point &p);
  friend void operator+= (Point &p, Direction const &d);
  Direction operator-(Point const & other) const
  {
    return {
      get<Row>(*this)-get<Row>(other),
      get<Column>(*this)-get<Column>(other)
    };
  }
};

istream& operator>>(istream& in, Point &p)
{
  in >> get<Row>(p)();
  char c;
  in>>c;
  if(in.good())
    assert(c==',');
  in >> get<Column>(p)();
  return in;
}

void operator+= (Point &p, Direction const &d)
{
  get<Row>(p)+=d.row();
  get<Column>(p)+=d.column();
}

int norm(Direction const &d)
{
  return d.row()()*d.row()() + d.column()()*d.column()();
}

struct Line
{
  Point start;
  Point end;
  friend istream& operator>>(istream& in, Line &p);
  void draw(function<void(Point const&)> f)
  {
    f(start);
    if(start == end)
      return;
    auto dir = end-start;
    dir.minimize();
    Point nxt(start);
    nxt+=dir;
    while(norm(nxt-start) < norm(end-start))
      {
        f(nxt);
        nxt+=dir;
      }
    f(end);
  }
};

istream& operator>>(istream& in, Line &x)
{
  string sep;
  in >> x.start >> sep >> x.end;
  if(in.good())
  assert(sep=="->");
  return in;
}


using Data = vector<Line>;

Data input(istream& cin)
{
  Data data;

  Line l;
  cin>> l;
  while(cin.good())
    {
      data.push_back(l);
      cin>> l;
    }
  return data;
}

bool operator<(Point const & lhs, Point const& rhs)
{
  if(get<Row>(lhs) == get<Row>(rhs))
    return get<Column>(lhs)<get<Column>(rhs);
  else
    return get<Row>(lhs)<get<Row>(rhs);
};

#include<ranges>
using namespace ranges::views;
template<class T>
auto axial(auto const & in)
{
  return in|filter([](Line const &l){
    return
      get<T>(l.start) == get<T>(l.end);
  });
}

auto solution_a(Data const &in)
{
  map<Point,unsigned int> thermals;

  auto f = [&thermals](auto &x){
    thermals[x]++;
  };

  for(auto x : in)
    if(get<Row>(x.start)() == get<Row>(x.end)()
       or
       get<Column>(x.start)() == get<Column>(x.end)())
      x.draw(f);
  return count_if(thermals.begin(),
                  thermals.end(),
                  [](auto it)
                  {
                    assert(it.second!=0);
                    return it.second>=2;
                  });
}

auto solution_b(Data const &in)
{
  map<Point,unsigned int> thermals;

  auto f = [&thermals](auto &x){
    thermals[x]++;
  };

  for(auto x : in)
    x.draw(f);

  auto ans = count_if(thermals.begin(),
                  thermals.end(),
                  [](auto it)
                  {
                    assert(it.second!=0);
                    return it.second>=2;
                  });
  assert(ans!=8155);
  return ans;
}

