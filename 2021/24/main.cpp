#include<gtest/gtest.h>

#include"instruction.hpp"
#include<sstream>
#include<vector>
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

istream& operator>>(istream& in, vector<Instruction> &v)
{
  Instruction i;
  while(not in.eof())
    {
      in>>i;
      if(not in.fail())
	v.push_back(i);
    }
  return in;
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
