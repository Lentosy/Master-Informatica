



template<class Sleutel, class Data>
class BinaireBoom : public std::unique_ptr<Knoop<Sleutel, Data>> {
public:
    // alle default, copy, move constructors en assignment operators zijn geschreven
    // die hoef je dus niet zelf te implementeren
    
    void roteer(bool naarlinks) 
    
}

template<class Sleutel, class Data>
class Knoop {
    // alle default, copy, move constructors en assignment operators zijn geschreven
    // die hoef je dus niet zelf te implementeren

    friend class BinaireBoom<Sleutel, Data>
    friend class SplayBoom<Sleutel, Data>
public:
    Sleutel sleutel;
    Data data;

    Knoop<Sleutel, Data>* geef_ouder();
    BinaireBoom<Sleutel, Data>& geef_kind(bool linker);
    // geeft true indien de knoop een linkerkind is, anders false
    bool is_linker_kind() const;
    BinaireBoom<Sleutel, Data>& vind_boom_van_wortel(Knoop<Sleutel, Data>& knoop);
}


template<class Sleutel, class Data>
class SplayBoom : public BinaireBoom<Sleutel, Data> : {
public:

    void splay(BinaireBoom<Sleutel, Data>*& plaats){
        // dit is de oplossing
        if(!plaats){
            throw "Er is geen knoop";
            // of gewoon 'return;'
        }

        while(plaats != this){
            SplayBoom<Sleutel, Data>& huidige_boom = *plaats;
            SplayBoom<Sleutel, Data>& ouder_boom = vind_boom_van_wortel(*(huidige_boom->geef_ouder()));
            if(ouder_boom == (*this)){
                this->roteer(!huidige_boom->is_linker_kind());
                plaats = &ouder_boom;
            }else {
                SplayBoom<Sleutel, Data>& grootouder_boom = vind_boom_van_wortel(*(ouder_boom->geef_ouder()));
                if(huidige_boom->is_linker_kind() == o_b->is_linker_kind()){
                    grootouder_boom.roteer(!ouder_boom->is_linker_kind());
                    grootouder_boom.roteer(!huidige_boom->is_linker_kind());
                } else {
                    ouder_boom.roteer(!huidige_boom->is_linker_kind());
                    grootouder_boom.roteer(!ouder_boom->is_linker_kind());
                }

                plaats = &grootouder_boom;
            }
        }
    }

}