
#include "quicksort.h"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include <algorithm>

class QuickSortTest : public ::testing::Test, public QuickSort<int>
{
public:
    void place_median_of_3_left(std::vector<int>& v, int a, int b, int c)
    {
        return QuickSort<int>::place_median_of_3_left(v, a, b, c);
    }
};

TEST_F(QuickSortTest, place_median_of_3_left)
{
    std::vector<std::pair<std::vector<int>, int>> data = {
            {{1, 2, 3}, 2},
            {{1, 1, 3}, 1},
            {{1, 2, 2}, 2},
            {{1, 1, 1}, 1},
    };

    for (auto& [values, expected_answer] : data)
    {
        do
        {
            std::vector<int> current_values{values};
            place_median_of_3_left(current_values, 0, 1, 2);

            ASSERT_EQ(current_values[0], expected_answer);

        } while (std::next_permutation(values.begin(), values.end()));
    }
}