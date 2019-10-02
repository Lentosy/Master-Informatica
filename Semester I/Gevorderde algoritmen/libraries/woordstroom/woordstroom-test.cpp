#include <iostream>
#include <istream>
#include <string>
#include <vector>

#include "woordstroom.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

using ::testing::ElementsAreArray;

TEST(woordstroom_test, lees)
{
    std::string woord;
    Woordstroom stroom{"test.txt"};

    std::vector<std::string> woorden;

    while (stroom >> woord)
    {
        woorden.push_back(woord);
    }

    // Hello World! 123abcABC.987!poi{a1a}
    // 1A2Blolzor.

    EXPECT_THAT(woorden,
                ElementsAreArray({"Hello",
                                  " ",
                                  "World",
                                  "! 123",
                                  "abcABC",
                                  ".987!",
                                  "poi",
                                  "{",
                                  "a",
                                  "1",
                                  "a",
                                  "}\n1",
                                  "A",
                                  "2",
                                  "Blolzor",
                                  ".\n"}));
}
