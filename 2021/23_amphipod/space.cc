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
