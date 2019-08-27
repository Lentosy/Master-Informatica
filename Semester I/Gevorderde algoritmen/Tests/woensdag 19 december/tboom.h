

class Tknoop;

class Tboom : public unique_ptr<Tknoop> {
    using unique_ptr<Tknoop>::unique_ptr;
    voed voegtoe(const std::string&) {
        Tboom* huidig = this;
        
    }
    static char afsluitkarakter;
}

class Tknoop {
    friend class Tboom;
    char c;
    Tknoop kind [3];
}