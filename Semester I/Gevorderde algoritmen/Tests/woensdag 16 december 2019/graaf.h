#include <cassert>
#include <fstream>
#include <string>
#include <sstream>
#include <cstring>

/**********************************************************************

   Class: Graaf

   beschrijving: Graaf is de basisklasse voor een hi�rarchie van ijlegraafklassen.
				  Deze hiërarchie zal klassen bevatten voor grafen met data behorend bij
				  knopen en/of takken. Deze data worden opgeslagen in vectoren,
				  zodat kan worden opgezocht op index.
		Ad knopen:      Deze zijn opeenvolgend genummerd. Knopen kunnen niet individueel verwijderd worden.
						Wel kunnen alle knopen samen verwijderd worden (door wis()), en kunnen knopen
						één voor één toegevoegd worden.
		Ad verbindingen: Deze kunnen naar hartenlust toegevoegd en verwijderd worden. Als een
						verbinding wordt verwijderd, wordt het nummer op de stack van
						vrijgekomenVerbindingsnummers gezet. Worden verbindingen toegevoegd,
						dan worden eerst deze vrijgekomen nummers opnieuw gebruikt, alvorens nieuwe nummers
						worden toegevoegd. hoogsteVerbindingsnummer kan nooit verkleinen, en de
						vector met takdata zal altijd hoogsteVerbindingsnummer elementen bevatten.


***************************************************************************/
#ifndef __GRAAF_H
#define __GRAAF_H


#include <stdexcept>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <stack>
#include <exception>




template<class Takdata>
class GraafMetTakdata {
public:
	typedef std::map<int, int>  Burenlijst;      // beeldt knoopnummer (van buur) af op verbindingsnummer

		// Construeert een graaf met een aantal knopen (default 0), zonder verbindingen.
	Graaf(int n = 0);

	// Voegt een nieuwe 'lege' knoop toe, d.w.z. zonder verbindingen.
	// Geeft knoopnummer van toegevoegde knoop terug (begint bij 0).
	virtual int voegKnoopToe();

	// Voegt verbinding toe tussen knoopnummers 'van' en 'naar'.
	// Gooit GraafExceptie indien verbinding al bestaat of knoopnummers ongeldig zijn.
	// Geeft verbindingsnummer van toegevoegde verbinding terug (begint bij 0).
	// Bij ongerichte graaf wordt terugverbinding ook toegevoegd (met zelfde verbindingnummer!)
	virtual int voegVerbindingToe(int van, int naar);

	// Verwijdert de verbinding tussen knoopnummers 'van' en 'naar', incl. de terugverbinding indien ongericht.
	// Gooit GraafExceptie indien knoopnummers ongeldig zijn.
	// Geen exceptie indien de verbinding niet bestond.
	// Andere verbindingen worden niet 'hernummerd'. Er komen dus mogelijks "gaten" in de verbindingsnummers.
	virtual void verwijderVerbinding(int van, int naar);

	// Geeft het aantal knopen van de graaf.
	int aantalKnopen() const;

	// Geeft het aantal verbindingen van de graaf. 
	// Bij ongerichte graaf worden verbindingen NIET dubbel geteld!
	int aantalVerbindingen() const;

	// Geeft het verbindingsnummer van de verbinding tussen 'van' en 'naar'.
	// Geeft -1 indien die verbinding niet bestaat.
	// Gooit een GraafExceptie indien knoopnummers ongeldig zijn.
	// Opgelet: performantie is O(log(producent)) waarbij producent aantal verbindingen vanuit 'van' is.
	int verbindingsnummer(int van, int naar) const;

	// Toegang tot de burenlijsten:
	const Burenlijst &operator[](int i) const { return burenlijsten[i]; }
	Burenlijst &operator[](int i) { return burenlijsten[i]; }  // deze kan als lvalue gebruikt worden

	bool heeftNegatieveLus() const;

protected:
    //Noot: toevoegfunctie zonder takdata op te geven kan alleen gebruikt als de klasse
    //      Takdata een defaultconstructor heeft.
    int voegVerbindingToe(int van, int naar); 
    int voegVerbindingToe(int van, int naar, const Takdata&);
    //Noot: verwijderVerbinding wordt ongewijzigd overgenomen van Graaf!

    //TakData vrijgeven (eventueel voor wijziging). Geeft nullpointer als tak niet bestaat
    //Noot: pointers teruggegeven door geefTakdata worden ongeldig
    //door toevoegen van een tak.
    const Takdata* geefTakdata(int van,int naar) const;
          Takdata* geefTakdata(int van,int naar)      ;

};


