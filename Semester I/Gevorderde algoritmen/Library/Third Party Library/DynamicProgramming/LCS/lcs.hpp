#ifndef __LCS_HPP
#define __LCS_HPP

#include <string>
using std::string;
#include <vector>
using std::vector;

class LCSsolver : public string
{
  public:
    LCSsolver() = default;
    LCSsolver(const LCSsolver &) = default;
    LCSsolver(LCSsolver &&) = default;
    virtual ~LCSsolver() = default;
    LCSsolver &operator=(const LCSsolver &) = default;
    LCSsolver &operator=(LCSsolver &&) = default;
    LCSsolver(const string &word) : string{word} {};
    LCSsolver(string &&word) : string{move(word)} {};

    int get_lcs_length_bu(const string &other)
    {
        return this->get_lcs_length_bu(LCSsolver{other});
    }

    int get_lcs_length_bu(string &&other)
    {
        return this->get_lcs_length_bu(LCSsolver{move(other)});
    }

    int get_lcs_length_bu(const LCSsolver &);

  private:
    vector<vector<int>> lcs_length;
    vector<vector<string>> lcs_direction;
};

int LCSsolver::get_lcs_length_bu(const LCSsolver& other) {
    int FROM_LENGTH = length() + 1;
    int TO_LENGTH = other.length() +1;    
    lcs_length = vector<vector<int>>(FROM_LENGTH,vector<int>(TO_LENGTH));
    lcs_direction = vector<vector<string>>(FROM_LENGTH,vector<string>(TO_LENGTH));
    for(int i=1;i<FROM_LENGTH;i++){
        lcs_length[i][0] = 0;
    }
    for(int i=0;i<TO_LENGTH;i++){
        lcs_length[0][i] = 0;
    }
    for(int i=1;i<FROM_LENGTH;i++){
        for(int j=1;j<TO_LENGTH;j++){
            if((*this)[i-1]==other[j-1]){
                lcs_length[i][j] = lcs_length[i-1][j-1] +1;
                lcs_direction[i][j] = "diagonal";
            }
            else if(lcs_length[i-1][j]>lcs_length[i][j-1]){
                lcs_length[i][j] = lcs_length[i-1][j];
                lcs_direction[i][j] = "up";
            }
            else{
                lcs_length[i][j] = lcs_length[i][j-1];
                lcs_direction[i][j] = "left";
            }
        }
    }
    return lcs_length[FROM_LENGTH-1][TO_LENGTH-1];
}

#endif