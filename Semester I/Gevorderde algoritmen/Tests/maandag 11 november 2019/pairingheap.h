template<class Sleutel>;
class Knoop<Sleutel>;

template<class Sleutel>
class PairingHeap : public unique_ptr<Knoop<Sleutel>> {
public:
    using unique_ptr<Knoop<Sleutel>>::unique_ptr;
    PairingHeap(PairingHeap<Sleutel>& andere);
    PairingHeap(PairingHeap<Sleutel>&& andere);
    operator=(PairingHeap<Sleutel>& andere);
    operator=(PairingHeap<Sleutel>&& andere);

    void voegSamen(PairingHeap<Sleutel>&& andere);
    void verwijderWortel(); // TE IMPLEMENTEREN
};



template<class Sleutel>
class Knoop<Sleutel> {
public:
    Knoop() {}
    Knoop(const Sleutel& sleutel) : sleutel{sleutel} {}
    Sleutel sleutel;
    PairingHeap<Sleutel> linkerkind;
    PairingHeap<Sleutel> rechterbroer;
};