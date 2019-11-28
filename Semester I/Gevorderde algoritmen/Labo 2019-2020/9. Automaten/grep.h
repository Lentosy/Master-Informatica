#pragma once

#include <string>
#include "regexp11.h"
#include "thompsonna.h"


class Grep {
    Grep(const Regexp& regexp, std::string& bestandsnaam); // maak zoekNA aan
    void zoek(); // zoekt regexp in bestandsnaam met behulp van zoekNA
private:
    Regexp regexp;
    std::string bestandsnaam;
    ZoekNA zoekNA;
};