#include "stofzuigergraaf.h"
#include <regex>
#include <iostream>

int main(void) {
    std::ifstream input("rss.txt");
    //gezin 6 leest de blog van gezin 1
    std::regex regex("gezin (\\d*) leest de blog van gezin (\\d*)");
    std::smatch matches;
    std::string line;

    RSSGraaf graaf;
    while(std::getline(input, line)){
        std::regex_match(line, matches, regex);
        int van = std::stoi(matches[1]);
        int naar = std::stoi(matches[2]);
        int knoopnrVan = graaf.voegKnoopToe(van);
        int knoopnrNaar = graaf.voegKnoopToe(naar);

        graaf.voegVerbindingToe(knoopnrVan, knoopnrNaar);
    } 
    
    std::vector<int>& optimalePad = graaf.geefOptimalePad();
    for(int i = 0; i < optimalePad.size(); i++){
        std::cout << optimalePad[i] << "\n";
    }

    return 0;
}