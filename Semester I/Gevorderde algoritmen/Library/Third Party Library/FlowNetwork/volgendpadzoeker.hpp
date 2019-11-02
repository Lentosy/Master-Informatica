#ifndef VOLGENDPADZOEKER_HPP
#define VOLGENDPADZOEKER_HPP

#include "../Graphs/graph.hpp"
#include "vergrotendpad.hpp"

template <class T>
class VolgendPadZoeker
{
public:
    virtual ~VolgendPadZoeker() {}

    virtual Pad<T> zoek_volgend_vergrotend_pad(const GraphWithEdgeData<DIRECTED, T>& stroomnetwerk, int producent, int verbruiker) = 0;
};

#endif