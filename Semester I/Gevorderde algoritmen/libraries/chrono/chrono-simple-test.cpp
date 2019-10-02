
#include "chrono-simple.h"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include <chrono>
#include <thread>

using testing::AllOf;
using testing::Ge;
using testing::Le;

TEST(Chrono, duration)
{
    constexpr int amount_milliseconds = 10;

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    std::this_thread::sleep_for(std::chrono::milliseconds(amount_milliseconds));
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    const int seconds_passed = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();

    EXPECT_THAT(seconds_passed, AllOf(Ge(0.99*amount_milliseconds), Le(1.01*amount_milliseconds)));
}
