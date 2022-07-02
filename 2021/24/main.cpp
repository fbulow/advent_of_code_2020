#include<gtest/gtest.h>

#include"instruction.hpp"
#include"state.hpp"
#include<sstream>
using namespace std;

TEST(Instruction, command)
{
  EXPECT_EQ(Instruction::Command::inp, Instruction::command("inp"));
  EXPECT_EQ(Instruction::Command::add, Instruction::command("add"));
  EXPECT_EQ(Instruction::Command::mul, Instruction::command("mul"));
  EXPECT_EQ(Instruction::Command::div, Instruction::command("div"));
  EXPECT_EQ(Instruction::Command::mod, Instruction::command("mod"));
  EXPECT_EQ(Instruction::Command::eql, Instruction::command("eql"));
}

TEST(Instruction, read_inp)
{
  Instruction sut;
  stringstream in("inp w");
  in>> sut;
  EXPECT_EQ(sut.cmd, Instruction::Command::inp);
  EXPECT_EQ(sut.a, 'w');
  EXPECT_EQ(sut.b, 0);

}

TEST(Instruction, read_add)
{
  Instruction sut;
  stringstream in("add a 2");
  in>> sut;
  EXPECT_EQ(sut.cmd, Instruction::Command::add);
  EXPECT_EQ(sut.a, 'a');
  EXPECT_EQ(sut.b, '2');
}

TEST(Instruction, read_multiple_trailing_whitespace)
{
  stringstream in("add a 2 mul x y ");
  vector<Instruction> sut;
  in>>sut;

  EXPECT_EQ(sut.size(), 2);
}

TEST(Instruction, read_multiple_trailing_no_whitespace)
{
  stringstream in("add a 2 mul x y");
  vector<Instruction> sut;
  in>>sut;

  EXPECT_EQ(sut.size(), 2);
}

TEST(State, ctor)
{
  State sut;
  EXPECT_EQ(0, sut.w());
  EXPECT_EQ(0, sut.x());
  EXPECT_EQ(0, sut.y());
  EXPECT_EQ(0, sut.z());
}

TEST(State, inp)
{
  State sut;
  sut.apply({Instruction::Command::add, 'w', '5'});
  
  EXPECT_EQ(5, sut.w());
  EXPECT_EQ(0, sut.x());
  EXPECT_EQ(0, sut.y());
  EXPECT_EQ(0, sut.z());
}
