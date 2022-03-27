#include"impl.hh"
#include<fstream>

TEST(evalN, three)
{
  {
    Bin sut{"111111111"};
    EXPECT_EQ(7, evalN(3, sut.cbegin()));
  }{
  Bin sut{"001111111"};
  EXPECT_EQ(1, evalN(3, sut.cbegin()));
  }{
  Bin sut{"010111111"};
  EXPECT_EQ(2, evalN(3, sut.cbegin()));
  }{
  Bin sut{"001111111"};
  EXPECT_EQ(3, evalN(4, sut.cbegin()));
  }
}


TEST(nextPackage, operator_type_id_zero)
{
  //       00111000000000000110111101000101001010010001001000000000
  Bin sut("0011100000000000011011AAAAAAAAAAABBBBBBBBBBBBBBBB0000000");
  //       VVVTTTILLLLLLLLLLLLLLLAAAAAAAAAAABBBBBBBBBBBBBBBB

  auto b = sut.cbegin();
  auto e = sut.cend();
  EXPECT_EQ("0011100000000000011011",
            string(b, nextPacket(b,b,e)));
}

TEST(nextPackage, litteral_package)
{
  Bin sut("110100101111111000101000");
  //       VVVTTTAAAAABBBBBCCCCC
  auto b = sut.cbegin();
  auto e = sut.cend();
  EXPECT_EQ("110100101111111000101",
            string(b, nextPacket(b,b,e)));
}

TEST(hex_to_bin, example)
{
  {
    Bin sut{Hex{"D2FE28"}};
    EXPECT_EQ("110100101111111000101000", sut);
  }
  {
    Bin sut("110100101111111000101000");
    EXPECT_EQ("110100101111111000101000", sut);
  }
}

TEST(solution_a, examples)
{
  EXPECT_EQ(16, solutionA(Hex{"8A004A801A8002F478"}));
  EXPECT_EQ(12, solutionA(Hex{"620080001611562C8802118E34"}));
  EXPECT_EQ(23, solutionA(Hex{"C0015000016115A2E0802F182340"}));
  EXPECT_EQ(31, solutionA(Hex{"A0016C880162017C3686B18A3D4780"}));

  ifstream in("/home/fbulow/proj/advent_of_code/2021/16/input");
  string data;
  in>>data;
  
  EXPECT_EQ(934, solutionA(Hex{move(data)}));
  
}

TEST(eval, eigth_example)
{
  Bin sut(Hex{"9C0141080250320F1802104A08"});
  auto pos = sut.cbegin();
  EXPECT_EQ(1, evalNext(pos));
}

TEST(eval, seventh_example)
{
  Bin sut(Hex{"9C005AC2F8F0"});
  auto pos = sut.cbegin();
  EXPECT_EQ(0, evalNext(pos));
}

TEST(eval, sixth_example)
{
  Bin sut(Hex{"F600BC2D8F"});
  auto pos = sut.cbegin();
  EXPECT_EQ(0, evalNext(pos));
}


TEST(eval, fifth_example)
{
  Bin sut(Hex{"D8005AC2A8F0"});
  auto pos = sut.cbegin();
  EXPECT_EQ(1, evalNext(pos));
}

TEST(eval, fourth_example)
{
  Bin sut(Hex{"CE00C43D881120"});
  auto pos = sut.cbegin();
  EXPECT_EQ(9, evalNext(pos));
}

TEST(eval, third_example)
{
  Bin sut(Hex{"880086C3E88112"});
  auto pos = sut.cbegin();
  EXPECT_EQ(7, evalNext(pos));
}

TEST(eval, second_example)
{
  Bin sut(Hex{"04005AC33890"});
  auto pos = sut.cbegin();
  EXPECT_EQ(54, evalNext(pos));
}

TEST(eval, first_example)
{
  Bin sut(Hex{"C200B40A82"});
  auto pos = sut.cbegin();
  EXPECT_EQ(3, evalNext(pos));
}


TEST(eval, literal_example)
{
  Bin sut{"110100101111111000101000"};
  //       VVVTTTAAAAABBBBBCCCCC
  auto pos = sut.cbegin();
  EXPECT_EQ(2021, evalNext(pos));

  EXPECT_EQ("110100101111111000101",
            string(sut.cbegin(), pos));
}
