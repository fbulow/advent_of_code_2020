#pragma once

enum class Dir {East, South};

Dir fromChar(char c)
{
  switch(c)
    {
    case '>':
      return Dir::East;
    case 'v':
      return Dir::South;
    }
  assert(false);
}



Dir otherDir(Dir d) 
{
  switch(d)
    {
    case Dir::East:
      return Dir::South;
    case Dir::South:
      return Dir::East;
    }
  assert(false);
}

struct Coord{
  int row;
  int col;
  friend bool operator<(Coord const & lhs, Coord const & rhs);
  Coord trans() const
  {
    return {col,row};
  }
};

bool operator<(Coord const & a, Coord const & b)
{
  if(a.row == b.row)
    return a.col<b.col;
  else
    return a.row<b.row;
}

TEST(Coord_, lessThan_)
{
  EXPECT_TRUE(Coord(1,0) < Coord(2,10));
  EXPECT_TRUE(Coord(1,0) < Coord(1,10));
  EXPECT_TRUE(Coord(0,11) < Coord(1,10));
  EXPECT_FALSE(Coord(1,1) < Coord(1,1));
}

struct Data{
  int Nrow{};
  int Ncol{};
  map<Coord, Dir> a;
  map<Coord, Dir> other;
  Data() = default;
  Data(vector<string> const & lines)
    :Nrow(lines.size())
    ,Ncol(lines[0].size())
    ,a{}
  {
    for(int row = 0; row<Nrow; row++)
      for(int col = 0; col<Ncol; col++)
        if('.'!=lines[row][col])
          a[{row, col}] = fromChar(lines[row][col]);
  }

  void swap()
  {
    ::swap(Nrow, Ncol);
    assert(a.size()==other.size());
    ::swap(other,a);
    assert(a.size()==other.size());
  }
  
  bool step()
  {
    auto first = trans_step(a);
    swap();
    auto second = trans_step(a);
    swap();
    return first or second;
  }
  
  bool trans_step(map<Coord, Dir> const &a) // move east, south still
  {
    bool ret = false;
    other.clear();
    int count = 0;
    assert(other.size()==count++);
    for(auto const & [coord, dir]:a)
      {
        if(Dir::South == dir)
          other[coord.trans()] = otherDir(dir);
        else
          {
            Coord dest{coord.row, (coord.col+1)%Ncol};
            if (not a.contains(dest))
              {
                other[dest.trans()] = otherDir(dir);
                ret = true;
              }
            else
              other[coord.trans()] = otherDir(dir);
          }
        assert(other.size()==count++);
      }
    return ret;
  }

  bool done() const
  {
    assert(a.size()==other.size());
    return all_of(a.cbegin(), a.cend(),
                  [this](auto const &key)
                  {
                    return other.contains(key.first.trans());
                  });
  }
  
  string str() const
  {
    ostringstream out;
    for(auto i{0}; i<Nrow;i++)
      {
        for(auto j{0}; j<Ncol;j++)
          {
            auto x = find_if(a.cbegin(),
                             a.cend(),
                             [i,j](auto x)
                             {
                               return (x.first.row==i) and (x.first.col==j);
                             });
            if(x==a.cend())
              out<<".";
            else if(x->second==Dir::South)
              out<<"v";
            else
              out<<">";
          }
        out<<endl;
      }
    return out.str();
  }

};


