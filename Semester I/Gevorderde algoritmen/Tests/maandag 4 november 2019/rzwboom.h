enum RZWkleur { rood, zwart };

template <class Sleutel>
class RZWknoop;

template <class Sleutel>
class RZWboom : public unique_ptr<RZWknoop<Sleutel>> {
public:
	using unique_ptr<RZWknoop<Sleutel>>::unique_ptr;
	RZWboom(unique_ptr<RZWknoop<Sleutel>>&& a);
	RZWboom(const std::vector<Sleutel>& sleutels, const std::vector<Sleutel>& zwarteSleutels);

    Boom<Sleutel, Data>* geefBoomBovenKnoop(Knoop<Sleutel, Data>& knoop) {
        if (knoop.ouder == 0)
            return this;
        else
            if (knoop.ouder->links.get() == &knoop)
                return &(knoop.ouder->links);
            else
                return &(knoop.ouder->rechts);
    }


    void voegToe(const Sleutel& sleutel); // TE IMPLEMENTEREN

protected:
	//zoekfunctie zoekt sleutel en geeft de boom in waaronder de sleutel zit (eventueel een lege boom als de sleutel
	//ontbreekt) en de pointer naar de ouder (als die bestaat, anders nulpointer).
	//noot: alhoewel de functie niets verandert aan de boom is ze geen const functie,
	//      omdat ze een niet-const pointer naar het inwendige van de boom teruggeeft.
	void zoek(const Sleutel& sleutel, RZWknoop<Sleutel>*& ouder, RZWboom<Sleutel>*& plaats);
	

	RZWkleur geefKleur() const {
        if(this){
            return this->get()->kleur;
        } else {
            return zwart;
        }
    }
	void zetKleur(RZWkleur kl) {
        this->get()->kleur = kl;
    }
};

template <class Sleutel>
class RZWknoop {
	friend class RZWboom<Sleutel>;
public:
	RZWknoop() :ouder(0) {}
	RZWknoop(const Sleutel& sl) :sleutel{ sl }, ouder(0), kleur(rood){};
	RZWknoop(Sleutel&& sl) :sleutel{ move(sl) }, ouder(0), kleur(rood){};
	RZWboom<Sleutel>& geefKind(bool links);
	Sleutel sleutel;
	RZWknoop<Sleutel>* ouder;
	RZWboom<Sleutel> links, rechts;
	RZWkleur kleur;
};