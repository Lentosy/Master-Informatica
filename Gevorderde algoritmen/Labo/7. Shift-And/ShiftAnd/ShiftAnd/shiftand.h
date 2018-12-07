#include "bitpatroon.h"
#include <queue>
#include <iostream>
#include <map>
typedef unsigned int uint;
typedef unsigned char uchar;

class Shiftand{
	public:
	//naaldlengte moet kleiner dan patroonlengte zijn,
	//anders wordt een exceptie opgegooid.
	    Shiftand(const uchar* naald,uint _naaldlengte);
	    void zoek(std::queue<const uchar*>& plaatsen, const uchar* hooiberg, uint hooiberglengte);
	    
	    
	                     
	private:
	    Bitpatroon letterpatroon[256]; // S, tabel R is overbodig. Veronderstelt enkel karakters van de Extended ASCII encoding.
	    const uchar* naald;
	    uint naaldlengte;
};
    
Shiftand::Shiftand(const uchar* naald, uint naaldlengte) : naald{naald}, naaldlengte{naaldlengte}{
	
	//geen forloop over de 256 waarden, want de defaultconstructor van Bitpatroon zet toch uint op 0, 
	//dus voor de karakters die niet in de naald voorkomen, is het bitpatroon al goed
		
	for(int j = 0; j < naaldlengte; j++){
		Bitpatroon& s = letterpatroon[*(naald + j)];
		s |=  Bitpatroon::eenbit(j);			
	}
}

void Shiftand::zoek(std::queue<const uchar*>& plaatsen, const uchar* hooiberg, uint hooiberglengte){
	Bitpatroon R; // extra bitpatroon R_{-1}, waarvan elke bit onwaar is
	Bitpatroon matchmask = Bitpatroon::eenbit(this->naaldlengte - 1);
	for(int j = 0; j < hooiberglengte; j++){
		R = ( R.shiftrechts(1) | Bitpatroon::eenbit(0)) & letterpatroon[*(hooiberg + j)]; // de shift-and 
		if(R.en(matchmask)){
			plaatsen.push(hooiberg + j - naaldlengte + 1);
		}	
	}
}





