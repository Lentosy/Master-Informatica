
#include "kdtree.h"

#include "gtest/gtest.h"

#include <string>

class KdTreeTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        voorbeeld_dichtste_buur.voeg_toe(Punt2D{0, 5});
        voorbeeld_dichtste_buur.voeg_toe(Punt2D{4, 1});
        voorbeeld_dichtste_buur.voeg_toe(Punt2D{-5, 0});
        voorbeeld_dichtste_buur.voeg_toe(Punt2D{6, -2});
        voorbeeld_dichtste_buur.voeg_toe(Punt2D{-1, 1});
    }

    // void TearDown() override
    // {
    // }

    KdTree voorbeeld_dichtste_buur;
};

std::ostream& operator<<(std::ostream& os, const Punt2D& punt)
{
    return os << "Punt2D(x = " << punt.x << ", y = " << punt.y << ");";
}

TEST_F(KdTreeTest, zoek_dichtste_buur)
{
    Punt2D zoek_punt{1, -1};

    auto [gevonden_dichtste_punt, kleinste_afstand, aantal_bezochte_knopen] =
            voorbeeld_dichtste_buur.zoek_dichtste_buur(zoek_punt);

    ASSERT_EQ(gevonden_dichtste_punt, (Punt2D{-1, 1}));
}
