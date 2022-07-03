#include<gtest/gtest.h>

#include"instruction.hpp"
#include"state.hpp"
#include<sstream>
#include"enums.hh"
using namespace std;

TEST(Instruction, _command)
{
  EXPECT_EQ(Command::inp, command("inp"));
  EXPECT_EQ(Command::add, command("add"));
  EXPECT_EQ(Command::mul, command("mul"));
  EXPECT_EQ(Command::div, command("div"));
  EXPECT_EQ(Command::mod, command("mod"));
  EXPECT_EQ(Command::eql, command("eql"));
}

TEST(Instruction, read_inp)
{
  Instruction sut;
  stringstream in("inp w");
  in>> sut;
  EXPECT_EQ(sut.cmd, Command::inp);
  EXPECT_EQ(sut.a, 'w');
  EXPECT_EQ(sut.b, 0);

}

TEST(Instruction, read_add)
{
  Instruction sut;
  stringstream in("add a 2");
  in>> sut;
  EXPECT_EQ(sut.cmd, Command::add);
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
  sut.apply({Command::add, 'w', '5'});
  
  EXPECT_EQ(5, sut.w());
  EXPECT_EQ(0, sut.x());
  EXPECT_EQ(0, sut.y());
  EXPECT_EQ(0, sut.z());

  sut.apply({Command::add, 'w', '5'});
  EXPECT_EQ(10, sut.w());
  EXPECT_EQ(0, sut.x());
  EXPECT_EQ(0, sut.y());
  EXPECT_EQ(0, sut.z());


  sut.apply({Command::add, 'x', '5'});
  EXPECT_EQ(10, sut.w());
  EXPECT_EQ(5, sut.x());
  EXPECT_EQ(0, sut.y());
  EXPECT_EQ(0, sut.z());
}
