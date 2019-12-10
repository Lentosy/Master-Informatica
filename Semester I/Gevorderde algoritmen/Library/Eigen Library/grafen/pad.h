#pragma once
#include <vector>
#include <iostream>
template< class T >
class Pad : public std::vector<int>{
public:
    T geefCapaciteit() const;
    void zetCapaciteit(const T& _capaciteit);
protected:
    T capaciteit;
};

template< class T >
T Pad<T>::geefCapaciteit() const{
    return capaciteit;
}

template< class T >
void Pad<T>::zetCapaciteit(const T& _capaciteit){
    capaciteit = _capaciteit;
}

template< class T >
std::ostream& operator<<(std::ostream& os,const Pad<T>& p){
    os << "Capaciteit= " << p.geefCapaciteit() << " :: ";
    if (p.size() > 0){
        os << p[0];
    }
    for (int i = 1; i < p.size(); i++ ){
        os << "->" << p[i];
    }
    os << "\n";
}