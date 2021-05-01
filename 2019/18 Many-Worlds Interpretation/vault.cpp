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

set<Destination> options(Vault v)
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
  auto opt=options(v);
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
