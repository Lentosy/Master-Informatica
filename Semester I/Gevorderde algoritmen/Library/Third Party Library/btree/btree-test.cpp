
#ifndef BKNOOP_UNITTEST_H
#define BKNOOP_UNITTEST_H

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "btree.h"

#include <algorithm>
#include <vector>

using ::testing::Eq;
using ::testing::Pair;

class BTreeTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        for (int i : keys)
        {
            bt.voegtoe(i, i);
        }
    }

    // void TearDown() override {}

    constexpr static int KNOOP_GROOTTE = 3;
    std::vector<int> keys = {52, 86, 24, 36, 84, 6,  11, 3,  92, 34, 26, 20, 44, 9,  77, 67, 95,
                             35, 29, 5,  47, 54, 37, 78, 18, 15, 12, 53, 14, 50, 85, 73, 89};
    Schijf<BTree<int, int, KNOOP_GROOTTE>::BKnoop> s;
    BTree<int, int, KNOOP_GROOTTE> bt{s};
};

TEST_F(BTreeTest, iterator)
{
    std::sort(std::begin(keys), std::end(keys));

    auto keys_it = keys.begin();

    for (const auto& p : bt)
    {
        ASSERT_EQ(p.first, (*keys_it));
        ASSERT_EQ(p.second, (*keys_it));

        keys_it++;
    }
}

TEST_F(BTreeTest, voegtoe)
{

    // std::cout << bt.dot_code() << std::endl;
    //
    // digraph {
    // "  36  77  " [shape=rectangle] [label="  36  77  "];
    // "  11  24  " [shape=rectangle] [label="  11  24  "];
    // "  36  77  " -> "  11  24  ";
    // "  52  " [shape=rectangle] [label="  52  "];
    // "  36  77  " -> "  52  ";
    // "  86  " [shape=rectangle] [label="  86  "];
    // "  36  77  " -> "  86  ";
    // "  6  " [shape=rectangle] [label="  6  "];
    // "  11  24  " -> "  6  ";
    // "  14  18  " [shape=rectangle] [label="  14  18  "];
    // "  11  24  " -> "  14  18  ";
    // "  34  " [shape=rectangle] [label="  34  "];
    // "  11  24  " -> "  34  ";
    // "  44  " [shape=rectangle] [label="  44  "];
    // "  52  " -> "  44  ";
    // "  54  " [shape=rectangle] [label="  54  "];
    // "  52  " -> "  54  ";
    // "  84  " [shape=rectangle] [label="  84  "];
    // "  86  " -> "  84  ";
    // "  92  " [shape=rectangle] [label="  92  "];
    // "  86  " -> "  92  ";
    // "  3  5  " [shape=rectangle] [label="  3  5  "];
    // "  6  " -> "  3  5  ";
    // "  9  " [shape=rectangle] [label="  9  "];
    // "  6  " -> "  9  ";
    // "  12  " [shape=rectangle] [label="  12  "];
    // "  14  18  " -> "  12  ";
    // "  15  " [shape=rectangle] [label="  15  "];
    // "  14  18  " -> "  15  ";
    // "  20  " [shape=rectangle] [label="  20  "];
    // "  14  18  " -> "  20  ";
    // "  26  29  " [shape=rectangle] [label="  26  29  "];
    // "  34  " -> "  26  29  ";
    // "  35  " [shape=rectangle] [label="  35  "];
    // "  34  " -> "  35  ";
    // "  37  " [shape=rectangle] [label="  37  "];
    // "  44  " -> "  37  ";
    // "  47  50  " [shape=rectangle] [label="  47  50  "];
    // "  44  " -> "  47  50  ";
    // "  53  " [shape=rectangle] [label="  53  "];
    // "  54  " -> "  53  ";
    // "  67  73  " [shape=rectangle] [label="  67  73  "];
    // "  54  " -> "  67  73  ";
    // "  78  " [shape=rectangle] [label="  78  "];
    // "  84  " -> "  78  ";
    // "  85  " [shape=rectangle] [label="  85  "];
    // "  84  " -> "  85  ";
    // "  89  " [shape=rectangle] [label="  89  "];
    // "  92  " -> "  89  ";
    // "  95  " [shape=rectangle] [label="  95  "];
    // "  92  " -> "  95  ";
    // }
}

#endif /* BKNOOP_UNITTEST_H */
