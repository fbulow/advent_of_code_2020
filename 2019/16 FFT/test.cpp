#include <gtest/gtest.h>
#include "main.cpp"
#include "gmock/gmock.h"
#include <iterator>
#include <iostream>
#include <fstream>
#include "summation.hpp"
#include "cycle.hpp"
#include "offset.hpp" 
#include "get_message.hpp" 

TEST(keep_one_digit, all)
{
  EXPECT_EQ(0, keep_one_digit(0));
  EXPECT_EQ(0, keep_one_digit(10));
  EXPECT_EQ(0, keep_one_digit(-10));

  EXPECT_EQ(1, keep_one_digit(1));
  EXPECT_EQ(1, keep_one_digit(-11));
}

TEST(example, pattern)
{
  Pattern sut({0,1,0,-1}, 2);

  ASSERT_EQ(0, sut());
  ASSERT_EQ(1, sut());
  ASSERT_EQ(1, sut());
  ASSERT_EQ(0, sut());
  ASSERT_EQ(0, sut());
  ASSERT_EQ(-1, sut());
  ASSERT_EQ(-1, sut());
  ASSERT_EQ(0, sut());
  ASSERT_EQ(0, sut());
  ASSERT_EQ(1, sut());
  ASSERT_EQ(1, sut());
  ASSERT_EQ(0, sut());
  ASSERT_EQ(0, sut());
  ASSERT_EQ(-1, sut());
  ASSERT_EQ(-1, sut());
}
TEST(example, verify_first_line)
{
  Pattern sut({0,1,0,-1}, 1);

  ASSERT_EQ(1, sut());
  ASSERT_EQ(0, sut());
}

TEST(example, last_sum)
{
  auto data =signal("12345678");
  Summation sut(data);

  ASSERT_EQ(2, sut.size(8));
  ASSERT_EQ(8, sut(1, 8));
}

TEST(example, phase)
{
  ASSERT_EQ(signal("48226158"), 
            phase("12345678", vector<int>{0, 1, 0, -1}));

  ASSERT_EQ(signal("34040438"), 
            phase("48226158", vector<int>{0, 1, 0, -1}));
}

TEST(examples, phases)
{

  ASSERT_EQ(signal("24176176"),
            solutionA("80871224585914546619083218645595"));

  ASSERT_EQ(signal("73745418"),
            solutionA("19617804207202209144916044189917"));

  
}

TEST(solution, A)
{
  ifstream in(INPUT);
  string data;
  in>>data;
  ASSERT_EQ(signal("17978331"),
            solutionA(data));
  
}

TEST(summation, size)
{
  {
    vector<int> data {0};
    Summation sut(data);
    EXPECT_EQ(2, sut.size(1)); // First zero length
  }
  {
    vector<int> data {0,0};
    Summation sut(data);
    EXPECT_EQ(3, sut.size(1)); // First zero length
  }
  {
    vector<int> data {0,0};
    Summation sut(data);
    EXPECT_EQ(2, sut.size(2)); // First zero length
  }
  {
    vector<int> data {0,0,0};
    Summation sut(data);
    EXPECT_EQ(2, sut.size(2)); // First zero length
  }

}

TEST(summation, segment_zero_stride_one)
{
  {
    vector<int> data {0};
    Summation sut(data);
    EXPECT_EQ(0, sut(0,1)); //Empty
  }

  {
    vector<int> data {1};
    Summation sut(data);
    EXPECT_EQ(0, sut(0,1)); //Empty
  }

  {
    vector<int> data {1, 20};
    Summation sut(data);
    EXPECT_EQ(0, sut(0,1)); //Empty
  }
}

TEST(summation, segment_one)
{
  {
    vector<int> data {1};
    Summation sut(data);
    EXPECT_EQ(1, sut(1,1)); //The one.
  }
  {
    vector<int> data {1, 20};
    Summation sut(data);
    EXPECT_EQ(1, sut(1,1)); //The one.
  }
}

TEST(summation, sum_stride_one_element_two)
{
  vector<int> data {1, 20};
  Summation sut(data);
  EXPECT_EQ(20, sut(2,1));
}

TEST(summation, sum_stride_two_first_element_empty_list)
{
  vector<int> data = {1, 20};
  Summation sut(data);
  EXPECT_EQ(1, sut(0,2));
}

TEST(summation, sum_stride_two_second_segment_cropped)
{
  vector<int> data={1, 20};
  Summation sut(data);
  EXPECT_EQ(20, sut(1,2));
}

TEST(segmentStart, one)
{
  EXPECT_EQ(0, segmentStart(1, 1));
  EXPECT_EQ(1, segmentStart(2, 1));
  EXPECT_EQ(2, segmentStart(3, 1));

  EXPECT_EQ(1, segmentStart(1, 2));
  EXPECT_EQ(3, segmentStart(2, 2));
  EXPECT_EQ(5, segmentStart(3, 2));

  
}

TEST(summation, sum_stride_two)
{
  vector<int> data {1, 20, 300};
  Summation sut(data);
  EXPECT_EQ(320, sut(1,2));
}

TEST(summation, sum_stride_two_middle)
{
  vector<int> data {1, 20, 300, 400};
  Summation sut(data);
  EXPECT_EQ(320, sut(1,2));
}

TEST(cycle, all)
{
  EXPECT_EQ(0 , cycle(0));
  EXPECT_EQ(1 , cycle(1));
  EXPECT_EQ(0 , cycle(2));
  EXPECT_EQ(-1, cycle(3));

  EXPECT_EQ(0 , cycle(0+4));
  EXPECT_EQ(1 , cycle(1+4));
  EXPECT_EQ(0 , cycle(2+4));
  EXPECT_EQ(-1, cycle(3+4));
}

/*
The first seven digits of your initial input signal also represent the
message offset. The message offset is the location of the eight-digit
message in the final output list. Specifically, the message offset
indicates the number of digits to skip before reading the eight-digit
message. For example, if the first seven digits of your initial input
signal were 1234567, the eight-digit message would be the eight digits
after skipping 1,234,567 digits of the final output list. Or, if the
message offset were 7 and your final output list were
98765432109876543210, the eight-digit message would be 21098765. (Of
course, your real message offset will be a seven-digit number, not a
one-digit number like 7.)  */

TEST(offset, simple)
{
  ASSERT_EQ(1234567,
            offset(signal("12345678")));
}

TEST(message, get)
{
  ASSERT_EQ( 21098765, get_message( signal("98765432109876543210"), 7 ));
}

TEST(get_message, single_argument)
{
  auto const s = signal("00000072109876543210");
  ASSERT_EQ(7,        offset(s));
  ASSERT_EQ(21098765, get_message(s, offset(s)));
}

auto solutionB(string input)
{
  return get_message(
                     [input]{
                       string very_long;
                       very_long.reserve(1000*input.size() + 1 );
                       for(auto i=0;i<10000;i++)
                         very_long+=input;
  
                       return phase(very_long,
                                    vector<int>{0, 1, 0, -1},
                                    100);
                     }(),
                     offset(signal(input)));
}


TEST(solution, B)
{
  ifstream in(INPUT);
  string data;
  in>>data;
  auto b = solutionB(data);
  ASSERT_NE(27999102, b); //Grabbed offset _after_ doing the 100 phases...
            
  ASSERT_EQ(19422575,
            b);
  
}
