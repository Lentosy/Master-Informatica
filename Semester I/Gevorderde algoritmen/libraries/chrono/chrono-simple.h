#ifndef CHRONO_SIMPLE_H
#define CHRONO_SIMPLE_H

#include <chrono>

class Chrono
{
public:
    Chrono() = default;

    void start();
    void stop();
    double tijd() const;

private:
    std::chrono::time_point<std::chrono::steady_clock> begin;
    std::chrono::time_point<std::chrono::steady_clock> einde;
};

#endif
