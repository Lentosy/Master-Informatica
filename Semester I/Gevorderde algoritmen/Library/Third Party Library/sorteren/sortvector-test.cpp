
#include "sortvector.h"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

using testing::ElementsAreArray;
using testing::Not;
using testing::UnorderedElementsAreArray;

TEST(Sortvector, constructor)
{
    ASSERT_NO_THROW(Sortvector<int> test{0});
    ASSERT_NO_THROW(Sortvector<int> test2(10));

    ASSERT_NO_THROW(Sortvector<double> test3{0});
    ASSERT_NO_THROW(Sortvector<double> test4(10));
}

TEST(Sortvector, vul_range)
{
    Sortvector<int> test(10);
    test.vul_range();

    ASSERT_THAT(test, ElementsAreArray({0, 1, 2, 3, 4, 5, 6, 7, 8, 9}));
}

TEST(Sortvector, vul_omgekeerd)
{
    Sortvector<int> test(10);
    test.vul_omgekeerd();

    ASSERT_THAT(test, ElementsAreArray({9, 8, 7, 6, 5, 4, 3, 2, 1, 0}));
}

TEST(Sortvector, draai_om)
{
    Sortvector<int> test(10);
    test.vul_range();
    test.draai_om();

    ASSERT_THAT(test, ElementsAreArray({9, 8, 7, 6, 5, 4, 3, 2, 1, 0}));
}

TEST(Sortvector, shuffle)
{
    Sortvector<int> test(10);
    test.vul_range();

    ASSERT_THAT(test, ElementsAreArray({0, 1, 2, 3, 4, 5, 6, 7, 8, 9}));

    test.shuffle();

    ASSERT_THAT(test, Not(ElementsAreArray({0, 1, 2, 3, 4, 5, 6, 7, 8, 9})));
    ASSERT_THAT(test, UnorderedElementsAreArray({0, 1, 2, 3, 4, 5, 6, 7, 8, 9}));
}

TEST(Sortvector, is_range)
{
    Sortvector<int> test;

    ASSERT_TRUE(test.is_range());

    test = Sortvector<int>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    ASSERT_TRUE(test.is_range());

    test = Sortvector<int>{0, 1, 2, 5, 4, 5, 6, 7, 8, 9};

    ASSERT_FALSE(test.is_range());

    test = Sortvector<int>{0, 1, 2, 5, 4, 5, 6, 7, 7, 9};

    ASSERT_FALSE(test.is_range());
}

TEST(Sortvector, is_gesorteerd)
{
    Sortvector<int> test;

    ASSERT_TRUE(test.is_gesorteerd());

    test = Sortvector<int>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    ASSERT_TRUE(test.is_gesorteerd());

    test = Sortvector<int>{0, 1, 2, 5, 4, 5, 6, 7, 8, 9};

    ASSERT_FALSE(test.is_gesorteerd());

    test = Sortvector<int>{0, 1, 2, 5, 4, 5, 6, 7, 7, 9};

    ASSERT_FALSE(test.is_gesorteerd());

    test = Sortvector<int>{9, 8, 7, 6, 5, 4, 3, 2, 1, 0};

    ASSERT_FALSE(test.is_gesorteerd());
}