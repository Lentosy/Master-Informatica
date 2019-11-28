#include "binairetrie.h"



int main(void){
    Bincode bincode("code.dat"); // stel de code op 
    BinaireTrie huffmanTrie(bincode); // maak een huffmantrie met de bijhorende code
}




// priorityqueue: je kan er movable items op pushen, maar niet meer afhalen
// de top-operatie geeft een const referentie terug
