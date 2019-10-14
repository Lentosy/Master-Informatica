#include "DNASequentie.h"
#include <iostream>
#include <fstream>
#include <regex>
#include <cassert>
#include <string>



void controleerGelijkenissen() {
    std::ifstream human("human.dna");
    std::ifstream chimp("chimp.dna");
   
    std::vector<DNASequentie> mensen;
    std::vector<DNASequentie> chimpansees;

    std::string sequentie;
    while(human >> sequentie){
        mensen.push_back(sequentie);
    }

    while(chimp >> sequentie){
        chimpansees.push_back(sequentie);
    }

    std::ifstream oplossing("oplossing.txt"); // Vergelijk met de oplossing die gegeven wordt
    std::regex regex("^Mens (\\d*) komt overeen met chimpansee (\\d*) met afstand (\\d*)$");
    //Mens 3 komt overeen met chimpansee 45 met afstand 26
    std::smatch matches;
	std::string oplossingLijn;

    for(int i = 0; i < mensen.size(); i++){
        int besteAfstand = INT_MAX;
        int besteChimpansee;
        for(int j = 0; j < chimpansees.size(); j++){
            int nieuweAfstand = mensen[i].mutatieafstand(chimpansees[j]);
            if(nieuweAfstand < besteAfstand){
                besteAfstand = nieuweAfstand;
                besteChimpansee = j;
            }
        }

        std::getline(oplossing, oplossingLijn);
        std::regex_match(oplossingLijn, matches, regex);

        std::cout << "Mens ";
        std::cout << i << " [" << std::stoi(matches[1]) << "]";
        std::cout << " komt overeen met chimpansee ";
        std::cout << besteChimpansee << " [" << std::stoi(matches[2]) << "]";
        std::cout << " met afstand ";
        std::cout << besteAfstand << " [" << std::stoi(matches[3]) << "]";
        std::cout << "\n";

        assert(std::stoi(matches[1]) == i);
        assert(std::stoi(matches[2]) == besteChimpansee);
        assert(std::stoi(matches[3]) == besteAfstand);
        
    }
}
int main(void){
    controleerGelijkenissen();

    return 0;
}