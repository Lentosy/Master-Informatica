#pragma once
#include <queue>
#include <string>
#include <typeinfo>
#include "ZoekInformatie.h"


class ZoekAlgoritme {
public:

    // Elk zoekalgoritme verwacht een patroon
    ZoekAlgoritme(const std::string& patroon) : patroon{patroon} {}

    // Het patroon wordt gezocht in de tekst
    virtual std::queue<int> zoek(const std::string& tekst, ZoekInformatie& zoekInformatie) const = 0;

    // De naam van het zoekalgoritme
    const char* naam() const;

protected:
    const std::string patroon;
};

const char* ZoekAlgoritme::naam() const {
    return (typeid(*this).name() + 6); // name() returns output :  'class CLASSNAME'   ,so we do +6 to get rid of the class word
}