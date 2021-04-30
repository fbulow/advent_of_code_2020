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

