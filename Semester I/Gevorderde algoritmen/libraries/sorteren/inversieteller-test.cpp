
#include "inversieteller.h"

#include "gtest/gtest.h"

TEST(InversieTeller, geef_aantal_inversies)
{
    InversieTeller<int> teller;

    std::vector<int> test{5, 8, 3, 1, 7, 2, 6};

    ASSERT_EQ(teller.geef_aantal_inversies(test), 12);

    test = std::vector<int>{2, 4, 1, 3, 5};

    ASSERT_EQ(teller.geef_aantal_inversies(test), 3);

    test = std::vector<int>{1, 20, 6, 4, 5};

    ASSERT_EQ(teller.geef_aantal_inversies(test), 5);
}