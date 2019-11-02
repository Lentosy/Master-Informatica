
#include <iostream>
#include <string>
#include "rabinkarp.hpp"

using namespace std;

int main(int argc, char** argv) {
    string text{"Death is Eternity in the Absence of Time, Eternist"};
    string pattern{"Eterni"};
    RabinKarp rk(257,256);
    rk.search(text,text.size(),pattern,pattern.size());
    cout << "Start locations of matches in text" <<endl;
    while(!rk.match_locations.empty()) {
        cout<< rk.match_locations.front()<<' ';
        rk.match_locations.pop();
    }
    cout<<endl;
    return 0;
}