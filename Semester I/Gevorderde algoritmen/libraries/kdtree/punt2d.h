
#ifndef PUNT2D_H
#define PUNT2D_H

#include <cassert>
#include <cmath>
#include <functional>
#include <sstream>
#include <iomanip>

class Punt2D
{
public:
    int x{0};
    int y{0};

    Punt2D() = default;
    Punt2D(int x, int y);
    Punt2D(const Punt2D& p) = default;
    Punt2D(Punt2D&& p) = default;
    Punt2D& operator=(const Punt2D& p) = default;
    Punt2D& operator=(Punt2D&& p) = default;
    virtual ~Punt2D() = default;

    bool friend operator==(const Punt2D& p1, const Punt2D& p2);
    bool friend operator!=(const Punt2D& p1, const Punt2D& p2);

    int afstand(const Punt2D& p) const;

    std::string to_string() const;
};

Punt2D::Punt2D(int x, int y) : x{x}, y{y}
{
}

bool operator==(const Punt2D& p1, const Punt2D& p2)
{
    return ((p1.x == p2.x) && (p1.y == p2.y));
}

bool operator!=(const Punt2D& p1, const Punt2D& p2)
{
    return !(p1 == p2);
}

int Punt2D::afstand(const Punt2D& p) const
{
    return (((p.x - x) * (p.x - x)) + ((p.y - y) * (p.y - y)));
}

std::string Punt2D::to_string() const
{
    std::stringstream out;

    out << "punt2(" << std::setw(5) << x << "," << std::setw(5) << y <<")";

    return out.str();
}

#endif