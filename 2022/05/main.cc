#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <fstream>

#include "stack.hh"
#include "instruction_processor.hh"
#include "row_type.hh"
#include <iostream>

using namespace testing;

TEST(stack, is_empty_at_first)
{
  Stack sut;
  EXPECT_THAT(sut.top(), Eq(' '));
  sut.push_bottom('A');
  EXPECT_THAT(sut.top(), Eq('A'));
  sut.push_bottom('B');
  EXPECT_THAT(sut.top(), Eq('A'));
  sut.push_top('C');
  EXPECT_THAT(sut.top(), Eq('C'));
  
  EXPECT_THAT(sut.pop(), Eq('C'));
  EXPECT_THAT(sut.pop(), Eq('A'));
  EXPECT_THAT(sut.pop(), Eq('B'));
}

TEST(InstructionProcessor, message)
{
  InstructionProcessor sut;
  sut.applyRow("[Z] [G] [J] [J] [W] [S] [H] [S] [G]");
  EXPECT_THAT(sut.message(),
	      Eq("ZGJJWSHSG"));
}

TEST(rowType, setup)
{
  EXPECT_THAT(rowType("[Z] [M] [P]"), Eq(RowType::Setup));
  EXPECT_THAT(rowType("move 1 from 2 to 1"), Eq(RowType::Move));
  EXPECT_THAT(rowType(""), Eq(RowType::Ignore));
  EXPECT_THAT(rowType(" 1   2   3 "), Eq(RowType::Ignore));
}

TEST(InstructionProcessor, example)
{
  InstructionProcessor sut;
  sut
    .applyRow("    [D]    ")
    .applyRow("[N] [C]    ")
    .applyRow("[Z] [M] [P]")
    .applyRow(" 1   2   3 ")
    .applyRow("")
    .applyRow("move 1 from 2 to 1");

  EXPECT_THAT(sut.message(),
	      Eq("DCP"));

  sut.applyRow("move 3 from 1 to 3");
  EXPECT_THAT(sut.message(),
	      Eq(" CZ"));
}

TEST(Solution, a)
{
  InstructionProcessor sut;
  
  std::ifstream in(INPUT);
  std::string row;
  std::getline(in, row);
  while(not in.eof())
    {
      sut.applyRow(row);
      std::getline(in, row);
    }
  std::cout<<"ans a: "<<sut.message()<<std::endl;
}
