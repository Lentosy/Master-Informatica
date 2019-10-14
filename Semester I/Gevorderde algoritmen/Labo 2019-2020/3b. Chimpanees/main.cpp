#include "DNASequentie.h"
#include <iostream>
#include <fstream>

int main(void){
    std::ifstream human("human.dna");
    std::ifstream chimp("chimp.dna");
   
    std::vector<DNASequentie> humans;
    std::vector<DNASequentie> chimpansees;

    std::string sequentie;
    while(human >> sequentie){
        humans.push_back(sequentie);
    }

    while(chimp >> sequentie){
        chimpansees.push_back(sequentie);
    }

    for(int i = 0; i < humans.size(); i++){
        int besteAfstand = INT_MAX;
        int besteChimpansee;
        for(int j = 0; j < chimpansees.size(); j++){
            int nieuweAfstand = humans[i].mutatieafstand(chimpansees[j]);
            if(nieuweAfstand < besteAfstand){
                besteAfstand = nieuweAfstand;
                besteChimpansee = j;
            }
        }
        std::cout << "Mens " << i << " komt overeen met chimpansee " << besteChimpansee << " met afstand " << besteAfstand << "\n";
    }




    return 0;
}