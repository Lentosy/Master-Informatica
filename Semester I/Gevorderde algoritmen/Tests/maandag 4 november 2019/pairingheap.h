template <class Sleutel>
class PairingHeap : unique_ptr<Knoop<Sleutel>> {
public:
    using unique_ptr<Knoop<Sleutel>>::unique_ptr;
    PairingHeap(PairingHeap&& a);
    PairingHeap(const PairingHeap& a);
    PairingHeap& operator=(PairingHeap&& a);
    PairingHeap& operator=(const PairingHeap& a);
    

    void voegSamen(PairingHeap<Sleutel>&& ander);
    void verwijderWortel(); // TE IMPLEMENTEREN
};


template <class Sleutel>
class Knoop {
public:
    Knoop() {}
    Knoop(const Sleutel& s) : sleutel{sleutel} {}
    Sleutel sleutel;
    PairingHeap<Sleutel> linkerkind;
    PairingHeap<Sleutel> rechterbroer;
};