
#include "chrono-simple.h"

void Chrono::start()
{
    begin = std::chrono::steady_clock::now();
}

void Chrono::stop()
{
    einde = std::chrono::steady_clock::now();
}

double Chrono::tijd() const
{
    std::chrono::duration<double> diff(einde - begin);

    return diff.count();
}