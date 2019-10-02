#ifndef VOLGENDPADZOEKER_H
#define VOLGENDPADZOEKER_H

#include "stroomnetwerk.h"
#include "vergrotendpad.h"

template <class T>
class Stroomnetwerk;

template <class T>
class VolgendPadZoeker
{
public:
    VolgendPadZoeker() = default;
    VolgendPadZoeker(const VolgendPadZoeker&) = default;
    VolgendPadZoeker(VolgendPadZoeker&&) = default;
    virtual VolgendPadZoeker& operator=(const VolgendPadZoeker&) = default;
    virtual VolgendPadZoeker& operator=(VolgendPadZoeker&&) = default;
    virtual ~VolgendPadZoeker() = default;

    virtual Pad<T>
    zoek_volgend_vergrotend_pad(const Stroomnetwerk<T>& stroomnetwerk) = 0;
};

#endif
