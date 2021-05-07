#include "vault.hpp"
#include <gtest/gtest.h>

ostream& operator<<(ostream& out, Vault const &v)
{
  for(auto const &x:v.map)
    out<<x<<endl;
  return out;
}


TEST(isLock, all_cases)
{
  ASSERT_TRUE(isLock('A'));
  ASSERT_FALSE(isLock('a'));
  ASSERT_TRUE(isLock('B'));
  ASSERT_FALSE(isLock('b'));
  ASSERT_FALSE(isLock('#'));
  ASSERT_FALSE(isLock('@'));
  ASSERT_FALSE(isLock('+'));
  ASSERT_FALSE(isLock('.'));
}

TEST(isKey, all_cases)
{
  ASSERT_TRUE(isKey('a'));
  ASSERT_FALSE(isKey('A'));
  ASSERT_TRUE(isKey('b'));
  ASSERT_FALSE(isKey('B'));
  ASSERT_FALSE(isKey('#'));
  ASSERT_FALSE(isKey('@'));
  ASSERT_FALSE(isKey('+'));
  ASSERT_FALSE(isKey('.'));
}

bool operator<(Destination const & lhs, Destination const &rhs)
{
  return lhs.name < rhs.name;
}

bool operator==(Destination const & lhs, Destination const &rhs)
{
  return lhs.name == rhs.name;
}

set<Destination> destinations(Vault v)
{
  set<Destination> ret;
  unsigned int steps{1};
  while(not v.no_snabela())
    {
      for(auto x:v.step())
        ret.insert({x,steps});
      steps++;
    }
  return ret;
}

unsigned int minimal_steps(Vault const&v, int consumed_steps)
{
  auto opt=destinations(v);
  if(opt.empty())
    return consumed_steps;
  
  vector<unsigned int> steps;
  steps.resize(opt.size());
  transform(opt.begin(),
            opt.end(),
            steps.begin(),
            [v](Destination d)
            {
              return minimal_steps({v, d.name}, d.steps);
            });
  return consumed_steps + *min_element(steps.begin(),
                                       steps.end());

}

Vault::Vault(vector<string> map)
  :map{move(map)}
{
  assert(all_of(next(this->map.begin()),
                this->map.end(),
                [N = this->map[0].size()](auto &x){return x.size()==N;}));

}
Vault::Vault(Vault const &other, char c)
    :Vault(other.map)
  {
    assert(isKey(c));
    auto replace = [&](char what, char with){
      for(auto &row: map)
        {
          auto it = find(row.begin(), row.end(), what);
          if(it !=row.end())
            {
              *it=with;
              return true;
            }
        }
      return false;
    };

    char door = c-'a'+'A';
    bool must_pass =
      replace('@',  '.') and
      replace(c,    '@') ;
    assert(must_pass);
    replace(door, '.');//May fail.
  }
