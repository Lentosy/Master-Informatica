
#include <string>
#include <vector>
#include "graaf.h"
using namespace std;


struct UitspraakSAT3 {
    string naam;
    vector<string> atomen;
};

class SAT3 {
protected:
    vector<UitspraakSAT3> uitspraken;
public:
    // te implementeren
    GraafMetKnoopdata<string> geefVertexCoverProbleem() const;
};