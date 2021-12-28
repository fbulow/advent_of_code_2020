#pragma once

using Vari = variant<char, int>;

bool isComma(auto& iterator)
{
  if(not holds_alternative<char>(iterator))
    return false;
  else
    return ',' == get<char>(iterator);
}

int depth_change(auto& iterator) 
{
  if(not holds_alternative<char>(iterator))
    return 0;
  else
    switch(get<char>(iterator))
      {
      case '[':
        return 1;
      case ']':
        return -1;
      default:
        return 0;
      }
}


struct SnailFishNumber{
  list<variant<char, int>> data;

  SnailFishNumber(string const &s)
  {
    istringstream in(s);
    char next = in.peek();
    if( (next>='0') and (next<='9') ) // Just a single regluar number.
      {
        int i;
        in>> i;
        data.push_back({i});
        return;
      }
    while(not in.eof())
      {
        next = in.peek();
        if(  (next == '[') or
             (next == ']') or
             (next == ',')
             )
          {
            char c;
            in>>c;
            data.push_back({c});
          }
        else
          {
            int i;
            in>> i;
            if(not in.eof())
              data.push_back({i});
          }
      }
  }
  friend ostream& operator<<(ostream& cout, SnailFishNumber const & s);
  friend long int magnitude(SnailFishNumber const &);
  auto find_boom()
  {
    int level=0;
    auto ret = data.begin();
    while(ret!=data.end())
      {
        level+= depth_change(*ret);
        if(level==5)
          return ret;
        else
          {
            advance(ret,1);
            assert(ret!=data.begin());
          }
      }
    return ret;
  }
  pair<int, int> getFragments(auto it)
  {
    return {
      get<int>(*next(it)),
      get<int>(*next(it,3))};
  }
  
  void toZero(auto it)
  {
    *it = {0};
    data.erase(next(it), next(it,5));
  }

  string str() const
  {
    ostringstream cout;
    cout<<*this;
    return cout.str();
  }
  
  auto nextInt(auto beg)
  {
    return find_if(beg,
                   data.end(),
                   [](Vari const &x)
                   {return holds_alternative<int>(x);});
  }

  auto prevInt(auto beg)
  {
    return find_if(make_reverse_iterator(beg),
                   data.rend(),
                   [](Vari const &x)
                   {return holds_alternative<int>(x);});
  }

  long int magnitude() const;
  bool explode();
  auto find_split()
  {
    return find_if(data.begin(),
                   data.end(),
                   [](Vari &x)
                   {
                     if(holds_alternative<int>(x))
                       return get<int>(x)>=10;
                     else
                       return false;
                   });
  }
  bool split()
  {
    auto it = find_split();
    if(it == data.end())
      return false;

    auto s = get<int>(*it);
    auto a = s/2;
    auto b = s/2+s%2;
    
    *it={']'};
    data.insert(it,{'['});
    data.insert(it,{a});
    data.insert(it,{','});
    data.insert(it,{b});
    
    return true;
  }

  bool reduction_step()
  {
    return explode() or split();
  }
  void reduce()
  {
    while(reduction_step())
      {}
  }
  void operator+=(string const &other)
  {
    operator+=(SnailFishNumber(other));
  }

  void operator+=(SnailFishNumber &&other)
  {
    data.insert(data.begin(), {'['});
    data.insert(data.end(), {','});
    data.insert(data.end(), other.data.begin(), other.data.end());
    data.insert(data.end(), {']'});
  }
};

TEST(add, example)
{
  SnailFishNumber sut("[1,2]");
  sut+="[[3,4],5]";
  EXPECT_EQ("[[1,2],[[3,4],5]]", sut.str());
}

TEST(split, example)
{
  {
    SnailFishNumber sut("[[[[0,7],4],[15,[0,13]]],[1,1]]");
    EXPECT_TRUE(sut.split());
    EXPECT_EQ("[[[[0,7],4],[[7,8],[0,13]]],[1,1]]", sut.str());
  }
  SnailFishNumber sut("[8,9]");
  EXPECT_FALSE(sut.split());
}

TEST(find_split, example)
{
  SnailFishNumber sut("[[[[0,7],4],[15,[0,13]]],[1,1]]");
  EXPECT_EQ(15, get<int>(*sut.find_split()));
  get<int>(*sut.find_split()) = 0;
  EXPECT_EQ(13, get<int>(*sut.find_split()));
}

ostream& operator<<(ostream& cout, variant<char, int> const & x)
{
  if(holds_alternative<char>(x))
    cout<<get<char>(x);
  else
    cout<<get<int>(x);
  return cout;
}
ostream& operator<<(ostream& cout, SnailFishNumber const & s)
{
  for(auto x:s.data)
    cout<<x;
  return cout;
}

TEST(SnailFishNumber, ctor)
{
  string const s = "[[1,9],[8,5]]" ;
  SnailFishNumber sut(s);
  ostringstream cout;
  cout<<sut;
  EXPECT_EQ(s, cout.str());
}

TEST(find_boom, example)
{
  SnailFishNumber sut("[[[[[9,8],1],2],3],4]");
  auto it = sut.find_boom();
  EXPECT_EQ('[', 
            get<char>(*it));
  EXPECT_EQ(9, 
            get<int>(*next(it)));

  auto [lhs, rhs] = sut.getFragments(it);
  EXPECT_EQ(9, lhs);
  EXPECT_EQ(8, rhs);
  
  sut.toZero(it);
  EXPECT_EQ("[[[[0,1],2],3],4]", sut.str());

  get<int>(*sut.nextInt(next(it)))+= rhs;
  EXPECT_EQ("[[[[0,9],2],3],4]", sut.str());
  
}

bool SnailFishNumber::explode()
{
  auto it = find_boom();
  if(it==data.end())
    return false;
  auto [lhs, rhs] = getFragments(it);
  toZero(it);
  {
    auto nxt = nextInt(next(it));
    if(nxt!=data.end())
      get<int>(*nxt)+= rhs;
  }
  {
    auto nxt = prevInt(it);
    if(nxt!=data.rend())
      get<int>(*nxt)+= lhs;
  }
  return true;
}

TEST(explode_, example_)
{
  {
    SnailFishNumber sut("[[[[[9,8],1],2],3],4]");
    EXPECT_TRUE(sut.explode());
    EXPECT_EQ("[[[[0,9],2],3],4]", sut.str());
  }
  {
    SnailFishNumber sut("[7,[6,[5,[4,[3,2]]]]]");
    EXPECT_TRUE(sut.explode());
    EXPECT_EQ("[7,[6,[5,[7,0]]]]", sut.str());
  }
  {
    SnailFishNumber sut("[[6,[5,[4,[3,2]]]],1]");
    EXPECT_TRUE(sut.explode());
    EXPECT_EQ("[[6,[5,[7,0]]],3]", sut.str());
  }
  {
    SnailFishNumber sut("[[3,[2,[1,[7,3]]]],[6,[5,[4,[3,2]]]]]");
    EXPECT_TRUE(sut.explode());
    EXPECT_EQ("[[3,[2,[8,0]]],[9,[5,[4,[3,2]]]]]", sut.str());
  }
  {
    SnailFishNumber sut("[[3,[2,[8,0]]],[9,[5,[4,[3,2]]]]]");
    EXPECT_TRUE(sut.explode());
    EXPECT_EQ("[[3,[2,[8,0]]],[9,[5,[7,0]]]]", sut.str());
  }
  {
    SnailFishNumber sut("[3,2]");
    EXPECT_FALSE(sut.explode());
  }
}

TEST(nextInt_, example_)
{
  SnailFishNumber sut("[[[[[9,8],1],2],3],4]");
  EXPECT_EQ(9,
            get<int>(*sut.nextInt(sut.find_boom())));
                                      
}

SnailFishNumber addAll(vector<string> s)
{
  return accumulate(next(s.begin()),
                    s.end(),
                    SnailFishNumber(s[0]),
                    [](SnailFishNumber tot,
                       string nxt)
                    {
                      tot+=nxt;
                      tot.reduce();
                      return tot;
                    });
}

TEST(add_all, example)
{
  auto sut = addAll({
                "[[[0,[5,8]],[[1,7],[9,6]]],[[4,[1,2]],[[1,4],2]]]",
                "[[[5,[2,8]],4],[5,[[9,9],0]]]",
                "[6,[[[6,2],[5,6]],[[7,6],[4,7]]]]",
                "[[[6,[0,7]],[0,9]],[4,[9,[9,0]]]]",
                "[[[7,[6,4]],[3,[1,3]]],[[[5,5],1],9]]",
                "[[6,[[7,3],[3,2]]],[[[3,8],[5,7]],4]]",
                "[[[[5,4],[7,7]],8],[[8,3],8]]",
                "[[9,3],[[9,9],[6,[4,9]]]]",
                "[[2,[[7,7],7]],[[5,8],[[9,3],[0,2]]]]",
                "[[[[5,2],5],[8,[3,7]]],[[5,[7,5]],[4,4]]]"});
  
  EXPECT_EQ("[[[[6,6],[7,6]],[[7,7],[7,0]]],[[[7,7],[7,7]],[[7,8],[9,9]]]]",
            sut.str());
  
  EXPECT_EQ(4140,
            magnitude(sut));
}

void show(auto beg, auto end)
{
  cout<<endl<<"--> ";
  while (beg!=end)
    {
      cout<<*beg;
      advance(beg,1);
    }
  cout<<endl;
}

long int magnitude(auto beg, auto end)
{
  if(holds_alternative<int>(*beg))
      return get<int>(*beg);
  else
    {
      assert('['==get<char>(*beg));
      int level=1;
      auto left_end = find_if(next(beg),
                              end,
                              [&level](auto x)
                              {
                                level+= depth_change(x);
                                return (level==1) and isComma(x);
                              });
      
      auto right_start = next(left_end);
      return
        3*magnitude(next(beg), left_end) +
        2*magnitude(right_start, prev(end));
    }
}

long int magnitude(SnailFishNumber const &s)
{
  return magnitude(s.data.cbegin(), s.data.cend());
}


TEST(magnitude, example)
{
  EXPECT_EQ(9,
            magnitude(SnailFishNumber("9")));

  EXPECT_EQ(3,
            magnitude(SnailFishNumber("[1,0]")));
  EXPECT_EQ(2,
            magnitude(SnailFishNumber("[0,1]")));

  EXPECT_EQ(129, magnitude(SnailFishNumber("[[9,1],[1,9]]")));
}
