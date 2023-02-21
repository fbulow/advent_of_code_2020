#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "tree.hh"
#include "nav.hh"

using namespace testing;
using namespace std;

TEST(Tree, increase_size_when_file_added)
{
  auto sut = Tree();
  sut.setPath("/");
  EXPECT_THAT(sut.size(), Eq(0));
  sut.addFile(1);
  EXPECT_THAT(sut.size(), Eq(1));
  sut.setPath("/a");
  EXPECT_THAT(sut.size(), Eq(0));
  sut.addFile(2);
  EXPECT_THAT(sut.size(), Eq(2));


  EXPECT_THAT(sut.totalSize("/"),  Eq(3));
  EXPECT_THAT(sut.totalSize("/a"), Eq(2));
  
}
     
TEST(Nav, cd_navigation)
{
  Nav sut;
  sut.cd("/");
  EXPECT_THAT(sut.path(), Eq("/"));
  sut.cd("a");
  EXPECT_THAT(sut.path(), Eq("/a"));
  sut.cd("e");
  EXPECT_THAT(sut.path(), Eq("/a/e"));
  sut.cd("..");
  EXPECT_THAT(sut.path(), Eq("/a"));
  sut.cd("..");
  EXPECT_THAT(sut.path(), Eq("/"));
  sut.cd("d");
  EXPECT_THAT(sut.path(), Eq("/d"));
}
