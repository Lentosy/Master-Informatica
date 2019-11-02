#ifndef BITPATROON_H
#define BITPATROON_H

using uint = unsigned int;
constexpr int patroonlengte = sizeof(uint) * 8;

class Bitpatroon
{
public:
    uint bits;

    Bitpatroon(uint u = 0);

    // Bit operaties

    const Bitpatroon operator&(const Bitpatroon& b) const;
    const Bitpatroon operator|(const Bitpatroon& b) const;
    const Bitpatroon& operator&=(const Bitpatroon& b);
    const Bitpatroon& operator|=(const Bitpatroon& b);

    // Logische operaties

    bool en(const Bitpatroon& b) const;
    bool of(const Bitpatroon& b) const;

    // Let op: shiftoperaties verplaatsen niets als verplaatsing >= patroonlengte.

    const Bitpatroon shiftlinks(uint verplaatsing) const;
    const Bitpatroon shiftrechts(uint verplaatsing) const;

    // Niet beveiligd: u moet kleiner dan patroonlengte zijn.

    static Bitpatroon eenbit(uint u);
};

Bitpatroon::Bitpatroon(uint u) : bits{u} {};

const BitpatroonBitpatroon Bitpatroon::operator&(const Bitpatroon& b) const
{
    return Bitpatroon(bits & b.bits);
}

const Bitpatroon Bitpatroon::operator|(const Bitpatroon& b) const
{
    return Bitpatroon(bits | b.bits);
}

const Bitpatroon& Bitpatroon::operator&=(const Bitpatroon& b)
{
    bits &= b.bits;
    return *this;
}

const Bitpatroon& Bitpatroon::operator|=(const Bitpatroon& b)
{
    bits |= b.bits;
    return *this;
}

bool Bitpatroon::en(const Bitpatroon& b) const
{
    return (bits & b.bits) != 0;
}

bool Bitpatroon::of(const Bitpatroon& b) const
{
    return (bits | b.bits) != 0;
}

const Bitpatroon Bitpatroon::shiftlinks(uint verplaatsing) const
{
    return Bitpatroon(bits << verplaatsing);
}

const Bitpatroon Bitpatroon::shiftrechts(uint verplaatsing) const
{
    return Bitpatroon(bits >> verplaatsing);
}

static Bitpatroon Bitpatroon::eenbit(uint u)
{
    return Bitpatroon(static_cast<uint>(1) << (patroonlengte - 1 - u));
}

#endif
