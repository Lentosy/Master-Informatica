#include <iostream>
using std::cout;
#include <vector>
using std::vector;
#include <utility>
using std::pair;
using std::make_pair;
#include <cmath>
using std::sqrt;
#include "Kerstnet.h"
#include "pugixml.cpp"
using pugi::xml_document;
using pugi::xml_node;
using pugi::xml_attribute;
using pugi::xml_object_range;
using pugi::xml_node_iterator;
#include <ctime>

vector<vector<double>> leesXML(const char* xmlBestand) {
    xml_document doc;
    if (!doc.load_file(xmlBestand)) exit(1);
    xml_node netwerk = doc.root().first_child(); // netwerk tag

    // dynamisch het aantal knooppunten bepalen

    int aantalKnooppunten = 0;
    for(auto&& knooppunt : netwerk.children()){
        aantalKnooppunten++;
    }

    vector<vector<double>> kerstnet(aantalKnooppunten, vector<double>(aantalKnooppunten));

    vector<pair<double, double>> coordinatenPerKnooppunt(aantalKnooppunten);
    xml_node knooppunt = netwerk.first_child(); // eerste knooppunt tag
    while(knooppunt) {
        
        double x = std::stod(knooppunt.attribute("xcoordinaat").value());
        double y = std::stod(knooppunt.attribute("ycoordinaat").value());
        int i = std::stoi(knooppunt.attribute("nummer").value());
        coordinatenPerKnooppunt[i] = make_pair(x, y);
        knooppunt = knooppunt.next_sibling();
        
    }

    for(int i = 0; i < kerstnet.size(); i++){
        pair<double, double> vanCoordinaat = coordinatenPerKnooppunt[i];
        for(int j = 0; j < kerstnet[i].size(); j++){
            pair<double, double> naarCoordinaat = coordinatenPerKnooppunt[j];
            
            double X = (naarCoordinaat.first - vanCoordinaat.first) * (naarCoordinaat.first - vanCoordinaat.first);
            double Y = (naarCoordinaat.second - vanCoordinaat.second) * (naarCoordinaat.second - vanCoordinaat.second);
            double afstand = sqrt(X + Y);
            kerstnet[i][j] = afstand;
        }
    }

    return kerstnet;
}



int main(void) {
    srand(time(0));
    vector<vector<double>> afstanden = leesXML("kerstnet.xml");

    Kerstnet kerstnet(afstanden);

    vector<int> oplossing = kerstnet.oplossing();
    double waarde = 0;
    for(int i = 0; i < oplossing.size() - 1; i++){
        cout << oplossing[i] << " -> ";
        waarde += afstanden[oplossing[i]][oplossing[i + 1]];
    }
    cout << oplossing[oplossing.size() - 1] << "\n";

    cout << "Oplossing met padlengte " << waarde << " km\n";



}