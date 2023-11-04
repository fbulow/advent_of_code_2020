#include"include.hh"

TEST(allSequencesOfOpenings, example)
{
  bool calledWithExamplePath = false;
  allSequenceOfOpenings([&calledWithExamplePath](Path const &p)
  {
    calledWithExamplePath |= (p == examplePath());
  });
  EXPECT_TRUE(calledWithExamplePath);
}
