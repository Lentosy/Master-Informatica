
#include "kmp.h"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

using ::testing::ElementsAreArray;

TEST(kmp, prefix_table)
{
    KnuthMorrisPratt kmp{"ababaa"};

    ASSERT_THAT(kmp.geef_prefix_tabel(), ElementsAreArray({-1, 0, 0, 1, 2, 3, 1}));

    kmp = KnuthMorrisPratt{"abcbababab"};

    ASSERT_THAT(kmp.geef_prefix_tabel(), ElementsAreArray({-1, 0, 0, 0, 0, 1, 2, 1, 2, 1, 2}));

    kmp = KnuthMorrisPratt{"abacabac"}; // Gecheckt door prof. Cnops

    ASSERT_THAT(kmp.geef_prefix_tabel(), ElementsAreArray({-1, 0, 0, 1, 0, 1, 2, 3, 4}));

    kmp = KnuthMorrisPratt{"ababaca"};

    ASSERT_THAT(kmp.geef_prefix_tabel(), ElementsAreArray({-1, 0, 0, 1, 2, 3, 0, 1}));

    kmp = KnuthMorrisPratt{"pxpypxpypxpx"}; // Gecheckt door prof. Cnops

    ASSERT_THAT(kmp.geef_prefix_tabel(), ElementsAreArray({-1, 0, 0, 1, 0, 1, 2, 3, 4, 5, 6, 7, 2}));
}

TEST(kmp, kmp_table)
{
    KnuthMorrisPratt kmp{"abacabac"}; // Gecheckt door prof. Cnops

    ASSERT_THAT(kmp.geef_kmp_tabel(), ElementsAreArray({-1, 0, 0, 1, 0, 0, 0, 1, 4}));

    kmp = KnuthMorrisPratt{"pxpypxpypxpx"}; // Gecheckt door prof. Cnops

    ASSERT_THAT(kmp.geef_kmp_tabel(), ElementsAreArray({-1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 7, 2}));
}

// TEST(kmp, search)
// {
//     std::string pattern{"aba"};
//     std::string text{"ababa"};

//     std::queue<int> results = KnuthMorrisPratt{pattern}.zoek(text);

//     ASSERT_EQ(results.size(), 2);
//     ASSERT_EQ(results.front(), 0);
//     results.pop();
//     ASSERT_EQ(results.front(), 2);
//     results.pop();
// }
