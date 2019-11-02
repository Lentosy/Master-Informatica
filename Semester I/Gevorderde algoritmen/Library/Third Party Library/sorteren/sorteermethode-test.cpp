
#include "../intstring/intstring.h"
#include "heapsort.h"
#include "insertionsort.h"
#include "mergesort.h"
#include "optimized-mergesort.h"
#include "quicksort.h"
#include "shellsort.h"
#include "sortvector.h"
#include "stlsort.h"

#include "gtest/gtest.h"

#include <utility>

template <typename T>
class SortingmethodTest : public ::testing::Test
{
protected:
    T sortingmethod;

    static constexpr int amount_test_data[7] = {0, 4, 8, 10, 256, 1000, 1234};
};

////////////////////////////////////////////////////////////////////////////////

using sortingmethods = ::testing::Types<STLSort<int>,
                                        InsertionSort<int>,
                                        ShellSort<int>,
                                        MergeSort<int>,
                                        OptimizedMergeSort<int>,
                                        QuickSort<int>,
                                        HeapSort<int>>;

TYPED_TEST_SUITE(SortingmethodTest, sortingmethods);

TYPED_TEST(SortingmethodTest, sort)
{
    for (const auto& amount : this->amount_test_data)
    {
        Sortvector<int> test(amount);
        test.vul_random_zonder_dubbels();

        this->sortingmethod(test);

        ASSERT_TRUE(test.is_range());
        ASSERT_TRUE(test.is_gesorteerd());
        ASSERT_TRUE(std::is_sorted(test.begin(), test.end()));

        test.vul_random();
        decltype(test) original(test);

        this->sortingmethod(test);

        ASSERT_TRUE(std::is_permutation(test.begin(), test.end(), original.begin()));
        ASSERT_TRUE(test.is_gesorteerd());
        ASSERT_TRUE(std::is_sorted(test.begin(), test.end()));
    }
}

TYPED_TEST(SortingmethodTest, sort_reverse)
{
    for (const auto& amount : this->amount_test_data)
    {
        Sortvector<int> test(amount);
        test.vul_omgekeerd();

        this->sortingmethod(test);

        ASSERT_TRUE(test.is_range());
        ASSERT_TRUE(test.is_gesorteerd());
        ASSERT_TRUE(std::is_sorted(test.begin(), test.end()));
    }
}

TYPED_TEST(SortingmethodTest, sort_already_sorted)
{
    for (const auto& amount : this->amount_test_data)
    {
        Sortvector<int> test(amount);
        test.vul_range();

        this->sortingmethod(test);

        ASSERT_TRUE(test.is_range());
        ASSERT_TRUE(test.is_gesorteerd());
        ASSERT_TRUE(std::is_sorted(test.begin(), test.end()));
    }
}

TYPED_TEST(SortingmethodTest, sort_empty)
{
    Sortvector<int> test(0);

    this->sortingmethod(test);

    ASSERT_TRUE(test.is_range());
    ASSERT_TRUE(test.is_gesorteerd());
    ASSERT_TRUE(std::is_sorted(test.begin(), test.end()));
}

////////////////////////////////////////////////////////////////////////////////

struct TestValue
{
    TestValue(int first, int second) : first{first}, second{second}
    {
    }

    TestValue() = default;
    TestValue(const TestValue& other) = default;
    TestValue& operator=(const TestValue& other) = default;
    TestValue(TestValue&& other) = default;
    TestValue& operator=(TestValue&& other) = default;
    virtual ~TestValue() = default;

    int first{0};
    int second{0};
};

bool operator<(const TestValue& lhs, const TestValue& rhs)
{
    return (lhs.first < rhs.first);
}

bool operator>(const TestValue& lhs, const TestValue& rhs)
{
    return (lhs.first > rhs.first);
}

bool operator==(const TestValue& lhs, const TestValue& rhs)
{
    return (lhs.first == rhs.first);
}

bool operator<=(const TestValue& lhs, const TestValue& rhs)
{
    return ((lhs.first < rhs.first) || (lhs.first == rhs.first));
}

template <typename T>
class StableSortingmethodTest : public SortingmethodTest<T>
{
};

using stable_sortingmethods =
        ::testing::Types<InsertionSort<TestValue>, MergeSort<TestValue>, OptimizedMergeSort<TestValue>>;

TYPED_TEST_SUITE(StableSortingmethodTest, stable_sortingmethods);

TYPED_TEST(StableSortingmethodTest, sort_stable)
{
    for (const auto& amount : this->amount_test_data)
    {
        std::vector<TestValue> test(amount);

        std::random_device rd;
        std::mt19937 eng{rd()};
        std::uniform_int_distribution dist{0, (amount / 10)};

        int value = 0;
        for (auto& test_data : test)
        {
            test_data.first = dist(eng);
            test_data.second = value;
            value++;
        }

        this->sortingmethod(test);

        bool is_stable = true;

        int i = 1;
        while (i < test.size() && is_stable)
        {
            if ((test[i - 1].first == test[i].first) && (test[i - 1].second >= test[i].second))
            {
                is_stable = false;
            }

            i++;
        }

        ASSERT_TRUE((i >= test.size()) && is_stable);
    }
}