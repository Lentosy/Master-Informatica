
template <class Sleutel, class Data>
class BinomiaalBoom;
template <class Sleutel, class Data>
class BinomiaalBos;


template <class Sleutel, class Data>
class BinomiaalKnoop {
    friend class BinomiaalBoom<Sleutel, Data>;
    friend class BinomiaalKnoop<Sleutel, Data>;
    BinomiaalKnoop(const Sleutel& s, const Data& d) : sleutel{s}, data{d} {}
    BinomiaalKnoop(const Sleutel&& s, const Data&& d) : sleutel{std::move(s)}, data{std::move(d)} {}
    Sleutel sleutel;
    Data data;
    BinomiaalBoom<Sleutel, Data> linkerkind, broer;
}

template <class Sleutel, class Data>
class BinomiaalBoom : public std::unique_ptr<BinomiaalKnoop<Sleutel, Data>>{
    using std::unique_ptr<BinomiaalKnoop<Sleutel, Data>>::unique_ptr;
}


template <class Sleutel, class Data>
class BinomiaalBos : public std::vector<BinomiaalBoom<Sleutel, Data>> {
public:
    void voegsamen(BinomiaalBos<Sleutel, Data>&& andere){
        // GEVRAAGD
    }
}