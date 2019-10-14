#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

class DNASequentie : public std::string {
public:
    DNASequentie(const std::string& s) : std::string(s) {}
    int mutatieafstand(const DNASequentie& other) const;
};


int DNASequentie::mutatieafstand(const DNASequentie& ander) const {
    
    std::vector<std::vector<int>> resultaten(this->size() + 1, std::vector<int>(ander.size() + 1));

    
    for(int i = this->size() - 1; i > 0; i--){
        for(int j = ander.size() - 1; j > 0; j--){
            if((*this)[i] == ander[j]){
                resultaten[i - 1][j - 1] = resultaten[i][j];
            } else {//if ((*this)[i] != ander[j]){
                resultaten[i - 1][j - 1] = 1 + std::min({resultaten[i][j], resultaten[i][j - 1], resultaten[i - 1][j]});
            }
        }
    }

    return resultaten[0][0];
}

