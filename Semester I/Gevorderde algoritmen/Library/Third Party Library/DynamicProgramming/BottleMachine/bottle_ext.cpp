#include "bottle_ext.hpp"
#include <iostream>

using namespace std;

int main(int argc, char **argv)
{
    BottleMachine bm;
    vector<int> available_volumes{20,50,100,250};
    int volume_to_fill = 570; // will require 4 bottles 2x250 1x50 1x20    
    int solution = bm.min_nr_bottles_td_ext(volume_to_fill,available_volumes,5);
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