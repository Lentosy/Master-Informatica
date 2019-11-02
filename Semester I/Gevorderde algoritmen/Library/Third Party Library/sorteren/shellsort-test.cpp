
#include "shellsort.h"
#include "sortvector.h"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

using testing::ElementsAreArray;

TEST(ShellSort, tokuda)
{
    ShellSort<int> sort;

    std::vector<long long> tokuda_sequence = sort.tokuda(1'000'000);

    ASSERT_THAT(
            tokuda_sequence,
            ElementsAreArray(
                    {1, 4, 9, 20, 46, 103, 233, 525, 1'182, 2'660, 5'985, 13'467, 30'301, 68'178, 153'401, 345'152}));
}