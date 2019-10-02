
#include "lgfloor.h"

#include "gtest/gtest.h"

TEST(LgFloor, lgfloor)
{
    ASSERT_DEATH(lgfloor(0), "");
    
    ASSERT_EQ(lgfloor(1), 0);
    ASSERT_EQ(lgfloor(2), 1);
    ASSERT_EQ(lgfloor(3), 1);
    ASSERT_EQ(lgfloor(64), 6);
    ASSERT_EQ(lgfloor(100), 6);
    ASSERT_EQ(lgfloor(200), 7);
    ASSERT_EQ(lgfloor(255), 7);
    ASSERT_EQ(lgfloor(10'000), 13);
}