#include "space.hh"
#include <gtest/gtest.h>
#include <gmock/gmock.h>

using namespace testing;
TEST(Space, empty_if_only_residents)
{
  Space sut(2, 'A');
  ASSERT_THAT(sut.getTop(), Eq('.'));
  sut.put('A');
  ASSERT_THAT(sut.getTop(), Eq('.'));
}

TEST(Space, depth_reduced_when_adding_resident_to_empty)
{
  Space sut(2, 'A');
  ASSERT_THAT(sut.depth(),Eq(2));
  sut.put('A');
  ASSERT_THAT(sut.depth(),Eq(1));
}

TEST(Space, depth_reduced_when_adding_non_resident_to_empty)
{
  Space sut(2, 'A');
  ASSERT_THAT(sut.depth(),Eq(2));
  sut.put('B');
  ASSERT_THAT(sut.depth(),Eq(1));
}
