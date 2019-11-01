#include "rssgraaf.h"
#include <regex>
#include <iostream>

int main(void) {
    std::ifstream input("rss.txt");
    //gezin 6 leest de blog van gezin 1
    std::regex regex("gezin (\\d*) leest de blog van gezin (\\d*)");
    std::smatch matches;
    std::string line;

    RSSGraaf graaf;
    // Eerste keer inlezen om de verschillende gezinsnummers te ontdekken
    std::map<int, int> gezinNummerOpKnoopNummer;
    while(std::getline(input, line)){
        std::regex_match(line, matches, regex);
        int van = std::stoi(matches[1]);
        int naar = std::stoi(matches[2]);
        gezinNummerOpKnoopNummer[van] = -1;
        gezinNummerOpKnoopNummer[naar] = -1;
    } 

    // Elk gezinsnummer afbeelden op een knoopnummer in de graaf
    std::map<int, int>::iterator iterator = gezinNummerOpKnoopNummer.begin();
    while(iterator != gezinNummerOpKnoopNummer.end()){
        iterator->second = graaf.voegKnoopToe(iterator->first);
        iterator++;
    }

    // Tweede maal overlopen om de verbindingen toe te voegen
    input.close();
    input.open("rss.txt");
    while(std::getline(input, line)){
        std::regex_match(line, matches, regex);
        int van = std::stoi(matches[1]);
        int naar = std::stoi(matches[2]);
        int knoopnrVan = gezinNummerOpKnoopNummer[van];
        int knoopnrNaar = gezinNummerOpKnoopNummer[naar];
        graaf.voegVerbindingToe(knoopnrVan, knoopnrNaar);    
    } 

    graaf.teken("dot/graaf.dot");
    
    std::vector<int> optimalePad;
    graaf.geefOptimalePad(optimalePad);
    
    for(int i = 0; i < optimalePad.size(); i++){
        std::cout << optimalePad[i] << "\n";
    }

    return 0;
}