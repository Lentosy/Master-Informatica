#ifndef __CHRONO_HPP
#define __CHRONO_HPP

#include <ctime>

class Chrono
{
  public:
    Chrono();
    void start();
    void stop();
    double elapsed() const;

  private:
    clock_t begin, end;
};

Chrono::Chrono() {}

void Chrono::start()
{
    begin = clock();
}

void Chrono::stop()
{
    end = clock();
}

double Chrono::elapsed() const
{
    return static_cast<double>(end - begin) / CLOCKS_PER_SEC;
}

#endif