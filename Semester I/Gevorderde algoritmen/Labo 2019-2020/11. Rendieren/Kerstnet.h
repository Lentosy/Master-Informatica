#include "simulanneal11.h"
#include <iostream>
using std::cout;
#include <vector>
using std::vector;
#include <cmath>
using std::exp;
#include <algorithm>
using std::shuffle;
#include <random>
using std::random_device;
using std::mt19937;



class Kerstnet : public SimulatedAnnealing<vector<int>> {
public:
    Kerstnet(vector<vector<double>>& kerstnet) : kerstnet{kerstnet} {}

private:
    vector<vector<double>> kerstnet;

    double T0();//initi"ele temperatuur
    bool terminateCond();//true als stoppen met zoeken
    double f(const vector<int>&);//objectieffunctie. Moet > 0 blijven
    vector<int> initialSolution();
    vector<int> pickAtRandom(const vector<int>&);
    double p(double T, double deltaf);//probabiliteit verandering
    void updateT();

};

double Kerstnet::T0(){ 
    return 100.0;
}

bool Kerstnet::terminateCond(){
    return T < 0.001;
}

void Kerstnet::updateT(){
    T *= 0.9999;
}

double Kerstnet::p(double T, double deltaf){ //exp(- (f(s0) - f(s)) /T))
    return exp(-(deltaf/T));
}

/*
* De waarde is de som van de afstanden van de sequentieële knopen
*/
double Kerstnet::f(const vector<int>& s){
    double waarde = 0;
    for(int i = 0; i < s.size() - 1; i++)
        waarde += kerstnet[s[i]][s[i + 1]];
    return waarde;
}


/*
* Maakt een permutatievector van de steden
*/
vector<int> Kerstnet::initialSolution(){
    std::vector<int> initial(kerstnet.size());
    for(int i = 0; i < initial.size(); i++)
        initial[i] = i;
    

    random_device rd;
    mt19937 g(rd());

    shuffle(initial.begin(), initial.end(), g);
    return initial;
}

/*
* Er wordt willekeurig een i en een j gezocht (0 <= i < j < 180)
* Heel het segment van s[i] tot s[j] wordt omgedraaid
* ... s[i] s[i + 1] s[i + 2] ... s[j - 2] s[j - 1] s[j] ... 
* wordt
* ... s[j] s[j - 1] s[j - 2] ... s[i + 2] s[i + 1] s[i] ... 
*/
vector<int> Kerstnet::pickAtRandom(const vector<int>& s){
    int i = 0, j = 0;
    while(i >= j){
        i = rand() % kerstnet.size();
        j = rand() % kerstnet.size();
    }

    vector<int> nieuw = s;
    std::reverse(nieuw.begin() + i, nieuw.begin() + j);
    return nieuw;
}

