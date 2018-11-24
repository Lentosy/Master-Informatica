



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


    BinaireBoom<Sleutel, Data>& geef_kind(bool linker);
    // geeft true indien de knoop een linkerkind is, anders false
    bool is_linker_kind() const;
    BinaireBoom<Sleutel, Data>& vind_boom_van_wortel(const )
}


template<class Sleutel, class Data>
class SplayBoom : public BinaireBoom<Sleutel, Data> : {
public:

    void splay(BinaireBoom<Sleutel, Data>* plaats){
        // GEVRAAGD
    }

}