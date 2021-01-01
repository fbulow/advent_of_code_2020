#include <gtest/gtest.h>
#include "main.cpp"
#include "gmock/gmock.h"

TEST(Room, ctor)
{
  Room sut(READTEST);
  EXPECT_EQ(1, sut.count('a'));
  EXPECT_EQ(1, sut.count('b'));
  EXPECT_EQ(2, sut.count('c'));
  EXPECT_EQ(2, sut.count('d'));
  EXPECT_EQ(3, sut.count('e'));
}


TEST(Room, visible)
{
  Room(
.......#.
...#.....
.#.......
.........
..#L....#
....#....
.........
#........
...#.....

}


// TEST(solution, b)
// {
//   ASSERT_EQ(26, solutionA(EXAMPLE));
//   cout<<"Solution b: "<<solutionA(INPUT)<<endl;
// }

