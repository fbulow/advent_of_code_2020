#include "space.hh"

bool Space::corridorIsBlocked() const
{
  if(isHallway())
    return getTop()!='.';
  else
    return false;
}


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

TEST(Space, corridor_stepsToCorridor)
{
  Space sut(1);
  sut.put('A');
  ASSERT_EQ(sut.stepsToCorridor(), 0);
}

TEST(Space, burrow_stepsToCorridor)
{
  Space sut(3);
  sut.put('A');
  ASSERT_EQ(sut.stepsToCorridor(), 2);
  sut.put('A');
  ASSERT_EQ(sut.stepsToCorridor(), 1);
}


TEST(Space, canMoveTo)
{
  Space hallway(1);
  EXPECT_FALSE(hallway.canMoveTo(Space(2,'A')));

  hallway.put('A');
  EXPECT_TRUE(hallway.canMoveTo(Space(2,'A')));
  EXPECT_FALSE(hallway.canMoveTo(Space(2,'B'))); //Wrong burrow
  EXPECT_FALSE(hallway.canMoveTo(Space(0,'A'))); //is full
}

TEST(Space, canMoveTo_cannot_leave_own_burrow_if_only_residents) 
{
  Space burrow(2,'A');
  burrow.put('A');

  //cannot leave home when only residents there
  EXPECT_FALSE(burrow.canMoveTo(Space(1)));
}

TEST(Space, canMoveTo_burrow_with_a_bad_apple)
{
  Space hallway(1);
  hallway.put('A');

  Space burrow(3, 'A');
  burrow.put('B');
  burrow.put('A');

  EXPECT_FALSE(hallway.canMoveTo(burrow)); //there is a 'B' in there
}

TEST(Space, moveTo)
{
  Space hallway(1);
  hallway.put('A');

  Space burrow(3, 'A');
  ASSERT_TRUE(hallway.moveTo(burrow));
  ASSERT_THAT(hallway.getTop(), Eq('.'));
  ASSERT_THAT(burrow.getTop(), Eq('A'));

  ASSERT_FALSE(burrow.moveTo(hallway));
  
}

TEST(Space, hard_move)
{
  Space from(2,'A');
  from.put('A');
  from.put('B');

  Space to(1);

  
}

TEST(Space, corridorIsBlocked_hallway)
{
  Space sut;
  EXPECT_FALSE(sut.corridorIsBlocked());
  sut.put('A');
  EXPECT_TRUE(sut.corridorIsBlocked());
}

TEST(Space, corridorIsBlocked_burrow)
{
  Space sut(2);
  EXPECT_FALSE(sut.corridorIsBlocked());
  sut.put('A');
  EXPECT_FALSE(sut.corridorIsBlocked());
}
