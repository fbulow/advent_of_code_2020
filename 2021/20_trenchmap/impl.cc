#include "impl.hh"
#include <sstream>
istream& operator>>(istream &in, Key &k)
{
  string s;
  in>>s;
  transform(s.begin(),
            s.end(),
            k.begin(),
            [](char c){return c=='#';});
            
  return in;
}

istream& operator>>(istream& in, Board &b)
{
  string line;
  Row r{0};
  in>>line;
  while(not in.eof())
    {
      for(Col c{0};c<Col{line.size()}; c++)
        if (line[value_of(c)] == '#')
          b.insert(Coord(r, c));
      in>>line;
    r++;
    }
  return in;
}

Key::Key(string  s)
{
  istringstream in(s);
  in>>*this;
}


void Key::invert()
{
  for(auto &b:*this)
    b=not b;
}

Board::Board(string s)
{
  istringstream in(s);
  in>>*this;
}

KeyIndex::KeyIndex(Coord const &coord, Board const &b)
  {
    size_t f = 0b100000000;
    for(auto r = get<Row>(coord)-Row{1}; r <= get<Row>(coord)+Row{1}; r++)
      for(auto c = get<Col>(coord)-Col{1}; c <= get<Col>(coord)+Col{1}; c++)
        {
          if (b.contains({r,c}))
            *this+=KeyIndex(f);
          f/=2;
        }
  }

ostream& operator<<(ostream& cout, Board const &b)
{
  auto row_min = get<Row>(*min_element(b.cbegin(),
                                       b.cend(),
                                       [](Coord const &a, Coord const &b)
                                       {
                                         return get<Row>(a) < get<Row>(b);
                                       }));
  auto row_max = get<Row>(*max_element(b.cbegin(),
                                       b.cend(),
                                       [](Coord const &a, Coord const &b)
                                       {
                                         return get<Row>(a) < get<Row>(b);
                                       }));
  auto col_min = get<Col>(*min_element(b.cbegin(),
                                       b.cend(),
                                       [](Coord const &a, Coord const &b)
                                       {
                                         return get<Col>(a) < get<Col>(b);
                                       }));
  auto col_max = get<Col>(*max_element(b.cbegin(),
                                       b.cend(),
                                       [](Coord const &a, Coord const &b)
                                       {
                                         return get<Col>(a) < get<Col>(b);
                                       }));

  for(Row row = row_min; row <= row_max ; row++)
    {
      for(Col col = col_min; col <= col_max ; col++)
        cout<< (b.contains(Coord{row, col})?'#':'.');
      cout<<endl;
    }
  return cout;
}  

ostream& operator<<(ostream& cout, Key const  & k)
{
  for(bool x:k)
    cout<<(x?'#':'.');
  return cout;
}

string Board::str() const
{
  ostringstream ss;
  ss<<*this;
  return ss.str();
}

Board iteration(Key const& k, Board const&b)  
{
  Board ret;
  
  Accumulator ac;
  for(Coord c: b)
    ac.poke(c);
  for(Coord c: ac)
    if(k[KeyIndex(c,b)])
      ret.insert(c);
  return ret;
}
