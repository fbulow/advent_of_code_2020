#include "space.hh"
#include <gtest/gtest.h>
#include <gmock/gmock.h>

using namespace testing;

TEST(Space, availableDepth_reduced_when_adding_resident_to_empty)
{
  Space sut(2, 'A');
  ASSERT_THAT(sut.availableDepth(),Eq(2));
  sut.put('A');
  ASSERT_THAT(sut.availableDepth(),Eq(1));
}

TEST(Space, availableDepth_reduced_when_adding_non_resident_to_empty)
{
  Space sut(2, 'A');
  ASSERT_THAT(sut.availableDepth(),Eq(2));
  sut.put('B');
  ASSERT_THAT(sut.availableDepth(),Eq(1));
}

TEST(Space, burrow_isDone)
{
    Space sut(2,'A');
    sut.put('A');
    sut.put('A');
    EXPECT_TRUE(sut.isDone());
}

TEST(Space, burrow_isDone_false_when_none_resident_is_there)
{
  Space sut(2,'A');
  sut.put('B');
  sut.put('A');
  EXPECT_FALSE(sut.isDone());
}

TEST(Space, putting_empty_space_does_not_reduce_depth)
{
  Space sut(1);
  EXPECT_THAT(sut.availableDepth(), Eq(1));
  sut.put('.');
  EXPECT_THAT(sut.availableDepth(), Eq(1));
  sut.put('A');
  EXPECT_THAT(sut.availableDepth(), Eq(0));
}
