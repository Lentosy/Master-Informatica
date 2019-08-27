#ifndef __GRAAF_H
#define __GRAAF_H

class GGraaf {
    typedef map<int, int> Burenlijst;

    public:
        // Construeert een graaf met een aantal knopen (default 0), zonder verbindingen.
        Graaf(int n=0);

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
        // Opgelet: performantie is O(log(v)) waarbij v aantal verbindingen vanuit 'van' is.
        int verbindingsnummer(int van, int naar) const; 

        // Verwijdert alle knopen en verbindingen en herstart de verbindingsnummer
        virtual void wis();

        // Toegang tot de knopen:
        const Knoop &operator[](int i) const { return knopen[i]; }
              Knoop &operator[](int i)       { return knopen[i]; }  // deze kan als lvalue gebruikt worden


        void controleerKnoopnummer(int k) const;   // throw indien k ongeldig
    private:
        vector<Burenlijst> burenlijsten;
        int hoogsteVerbindingsnummer;
        stack<int> vrijgekomenVerbindingsnummers;
}

#endif