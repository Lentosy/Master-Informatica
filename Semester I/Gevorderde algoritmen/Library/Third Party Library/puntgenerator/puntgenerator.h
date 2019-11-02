#ifndef PUNTGENERATOR_H
#define PUNTGENERATOR_H

#include <cmath>

// Genereert random punten
// We zijn ondertussen al vergeten waar de wiskundige functie vandaan komt

// Indien je random punten nodig hebt, gebruik dan de ingebouwde random klassen van C++ 11
// Gebruik niet srand() of rand(), deze zijn verouderd!

// TODO unit test

class Puntgenerator
{
public:
    Puntgenerator() : a(0), d(0.5), q(1), r(1.008)
    {
    }

    double geefpunt()
    {
        if (a + d < q)
        {
            return ((a += d) * sin(r));
        }
        else
        {
            a = -d;
            d *= r;
            return (q *= r * r);
        }
    }

protected:
    double a;
    double d;
    double q;
    double r;
};

#endif
