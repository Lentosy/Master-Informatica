#include "dubbelesamenhang.h"
#include <iostream>
#include <vector>

int main(void) {
    GraafMetKnoopdata<ONGERICHT, int> graaf;
    int a = graaf.voegKnoopToe(0);
    int b = graaf.voegKnoopToe(1);
    int c = graaf.voegKnoopToe(2);
    int d = graaf.voegKnoopToe(3);
    int e = graaf.voegKnoopToe(4);
    int f = graaf.voegKnoopToe(5);

    graaf.voegVerbindingToe(a, b);
    graaf.voegVerbindingToe(b, c);
    graaf.voegVerbindingToe(b, d);
    graaf.voegVerbindingToe(c, d);
    graaf.voegVerbindingToe(b, e);
    graaf.voegVerbindingToe(a, f);

    graaf.teken("graaf.dot");
    DubbeleSamenhang ds;
    std::vector<int> pad = ds.zoekScharnierpunten(&graaf);
    for(int i = 0; i < pad.size(); i ++) {
        std::cout << pad[i] << "\n";
    }
}