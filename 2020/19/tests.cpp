#include <gtest/gtest.h>
#include "main.cpp"

TEST(rule, ctor_known)
{
  EXPECT_FALSE(Rule("0: 8 11").known());
  EXPECT_TRUE(Rule("72: \"b\"").known());
}

TEST(rule, ctor_left)
{
  Rule sut("0: 8 11");

  EXPECT_EQ(2, sut.left.size());
  EXPECT_EQ(8, sut.left[0]);
  EXPECT_EQ(11, sut.left[1]);

  EXPECT_EQ(0, sut.right.size());

}

TEST(rule, ctor_right)
{
  Rule sut("123: 72 | 52 121");
  EXPECT_EQ(1, sut.left.size());
  EXPECT_EQ(72, sut.left[0]);

  EXPECT_EQ(2, sut.right.size());
  EXPECT_EQ(52, sut.right[0]);
  EXPECT_EQ(121, sut.right[1]);
  
}

TEST(getIndex, test)
{
  EXPECT_EQ(123, getIndex("123: 72 | 52 121"));
}

TEST(RegexBuilder, test)
{
  auto sut = RegexBuilder({
      "72: \"b\"",
      "0: 72 72"});
  EXPECT_EQ("b", sut.get(72));
  EXPECT_EQ("bb", sut.get(0));
}

TEST(just, match)
{
  EXPECT_TRUE(regex_match("aba", regex("a(ab|ba)")));
}

TEST(RegexBuilder, theOr)
{
  auto sut = RegexBuilder({
      "71: \"a\"",
      "72: \"b\"",
      "0: 71 | 72"});
  EXPECT_EQ("b", sut.get(72));
  EXPECT_EQ("(a|b)", sut.get(0));
}


TEST(getInput, rules)
{
  auto re = getRegexpA(EXAMPLE);
  EXPECT_TRUE(regex_match("aab", re));
  EXPECT_TRUE(regex_match("aba", re));
  EXPECT_FALSE(regex_match("abb", re));
}

TEST(solution, a)
{
  auto ans = solveA(INPUT);
  ASSERT_EQ(109, ans);
  cout<<"Solution a: "<<ans<<endl;
}

TEST(parseRuleEight, first)
{
  regex re(parseRuleEight("a"));
  EXPECT_TRUE(regex_match("a", re));
  EXPECT_TRUE(regex_match("aa", re));
  EXPECT_TRUE(regex_match("aaa", re));

  EXPECT_FALSE(regex_match("", re));
}
TEST(parseRuleEleven, first)
{
  regex re(parseRuleEleven("a", "b", 10));
  EXPECT_TRUE(regex_match("ab",re));
  EXPECT_TRUE(regex_match("aabb",re));
  EXPECT_TRUE(regex_match("aaabbb",re));

  EXPECT_FALSE(regex_match("aabbb",re));
}

TEST(solution, b)
{
  cout<<"_GLIBCXX_REGEX_STATE_LIMIT "<<_GLIBCXX_REGEX_STATE_LIMIT<<endl;
  auto ans = solveB(INPUT);
  cout<<"Solution b: "<<ans<<endl;
}
