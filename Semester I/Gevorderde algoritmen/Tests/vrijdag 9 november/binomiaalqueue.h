
template <class Sleutel, class Data>
class BinomiaalBoom;
template <class Sleutel, class Data>
class BinomiaalBos;


template <class Sleutel, class Data>
class BinomiaalKnoop {
    friend class BinomiaalBoom<Sleutel, Data>;
    friend class BinomiaalKnoop<Sleutel, Data>;
public:
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


        for(int i = 0; i < ander.size(); i++){
            if(andere[i]){ // operator [i] geeft i-de binomiaalboom terug
                Boom& carry = andere[i];
            }
            int j = i;
            while(j < this->size() && (*this)[j]){
                carry += (*this)[j++];
            }
            if(j < this->size()){
                (*this)[j] = move(carry);
            } else {
                this->emplace_back(move(carry));
            }
        }

        ander.resize(0);

    }

    Boom& operator+=(Boom&& andere){
        if((*this)->sleutel > andere->sleutel){
            swap(*this, andere);
        }
        ander->broer = move((*this)->linkerkind);
        (*this)->linkerkind = move(andere);
        return *this;
    } 

}