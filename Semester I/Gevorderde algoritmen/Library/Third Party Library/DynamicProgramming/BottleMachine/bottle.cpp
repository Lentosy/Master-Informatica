#include "bottle.hpp"
#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char ** argv) {
    BottleMachine bm;
    vector<int> available_volumes{20,50,100,250};
    int volume_to_fill = 670; // will require 5 bottles 2x250 1x100 1x50 1x20
    int solution = bm.min_nr_bottles_td(volume_to_fill,available_volumes);    
    if(solution > 0) {
        cout<< "You need "<<solution<<" bottles to most efficiently fill the volume"<<endl;
    }
    else {
        cout << "The volume couldn't be constructed from the bottles \n";
        for(int v:available_volumes){
            cout<<v<<" ";
        }
        cout<<endl;
    }
    return 0;
}