#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <fstream>

#include "tree.hh"
#include "nav.hh"
#include "row_type.hh"
#include "sol_a.hh"


using namespace testing;
using namespace std;

TEST(row_type, example)
{
  EXPECT_THAT(rowType("$ cd .."),		Eq(RowType::Cd));
  EXPECT_THAT(rowType("$ cd .."),		Eq(RowType::Cd));
  EXPECT_THAT(rowType("$ cd /"),		Eq(RowType::Cd));
  EXPECT_THAT(rowType("$ cd a"),		Eq(RowType::Cd));
  EXPECT_THAT(rowType("$ cd d"),		Eq(RowType::Cd));
  EXPECT_THAT(rowType("$ cd e"),		Eq(RowType::Cd));
  EXPECT_THAT(rowType("$ ls"),		Eq(RowType::Ignore));
  EXPECT_THAT(rowType("$ ls"),		Eq(RowType::Ignore));
  EXPECT_THAT(rowType("$ ls"),		Eq(RowType::Ignore));
  EXPECT_THAT(rowType("$ ls"),		Eq(RowType::Ignore));
  EXPECT_THAT(rowType("14848514 b.txt"),	Eq(RowType::File));
  EXPECT_THAT(rowType("2557 g"),		Eq(RowType::File));
  EXPECT_THAT(rowType("29116 f"),		Eq(RowType::File));
  EXPECT_THAT(rowType("4060174 j"),	Eq(RowType::File));
  EXPECT_THAT(rowType("5626152 d.ext"),	Eq(RowType::File));
  EXPECT_THAT(rowType("584 i"),		Eq(RowType::File));
  EXPECT_THAT(rowType("62596 h.lst"),	Eq(RowType::File));
  EXPECT_THAT(rowType("7214296 k  "),	Eq(RowType::File));
  EXPECT_THAT(rowType("8033020 d.log"),	Eq(RowType::File));
  EXPECT_THAT(rowType("8504156 c.dat"),	Eq(RowType::File));
  EXPECT_THAT(rowType("dir a"),		Eq(RowType::Ignore));
  EXPECT_THAT(rowType("dir d"),		Eq(RowType::Ignore));
  EXPECT_THAT(rowType("dir e"),		Eq(RowType::Ignore));
}

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

  
  auto const s = sut.allTotalSizes();
  EXPECT_THAT(s.size(), Eq(2));
  EXPECT_THAT(s, Contains(2));
  EXPECT_THAT(s, Contains(3));

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

TEST(SolA, example)
{
  auto sut = SolA();
  sut
    <<"$ cd /"
    <<"$ ls"
    <<"dir a"
    <<"14848514 b.txt"
    <<"8504156 c.dat"
    <<"dir d"
    <<"$ cd a"
    <<"$ ls"
    <<"dir e"
    <<"29116 f"
    <<"2557 g"
    <<"62596 h.lst"
    <<"$ cd e"
    <<"$ ls"
    <<"584 i"
    <<"$ cd .."
    <<"$ cd .."
    <<"$ cd d"
    <<"$ ls"
    <<"4060174 j"
    <<"8033020 d.log"
    <<"5626152 d.ext"
    <<"7214296 k";
  
  EXPECT_THAT(sut.ans(), Eq(95437));
}


TEST(SolA, empty_dir_doubles)
{
  auto sut = SolA();
  sut
    <<"$ cd /"
    <<"$ cd a"
    <<"$ cd b"
    <<"1 foo";
  EXPECT_THAT(sut.ans(), Eq(3));
}


TEST(SolA, actual)
{
  auto sut = SolA();
    
  std::ifstream in(INPUT);
  std::string row;
  std::getline(in, row);
  while(not in.eof())
    {
      sut<<row;
      std::getline(in, row);
    }

  auto ans = sut.ans();
  EXPECT_THAT(ans, Gt(1140385));
  cout <<"Solution a: "<<ans<<std::endl;
}
