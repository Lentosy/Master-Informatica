#include <memory>
using std::unique_ptr;
using std::make_unique;
using std::move;
#include <string>
using std::string;

class PatriciaTrie;
class TrieKnoop;

class TrieKnoop {
public:
    virtual bool isBlad() = 0;
};


class TrieNietBlad : public TrieKnoop {
public:
    bool isBlad() { return false; }
    int testindex;
    unique_ptr<TrieKnoop> kinderen[26]; // enkel alfabetische kleine letters momenteel
};


class TrieBlad : public TrieKnoop{
public:
    TrieBlad(const std::string& s) : s{s} {}
    bool isBlad() { return true;}
    string s;
};



class PatriciaTrie : public unique_ptr<TrieKnoop>{
public:
    using unique_ptr<TrieKnoop>::unique_ptr;

    PatriciaTrie() {}

    PatriciaTrie(unique_ptr<TrieKnoop>&& o) : unique_ptr<TrieKnoop>(move(o)) {};
    PatriciaTrie& operator=(unique_ptr<TrieKnoop>&& o) {
        unique_ptr<TrieKnoop>::operator=(move(o));
        return *this;
    }

    unique_ptr<TrieKnoop>* zoek(const string& s) {
        unique_ptr<TrieKnoop>* huidig = this;
        int index = 0;
        while(*huidig && !(*huidig)->isBlad()) {
            TrieNietBlad* inwendigeKnoop = static_cast<TrieNietBlad*>(huidig->get());
            huidig = &(inwendigeKnoop->kinderen[s[index]]);
        }
        return huidig;
    }

    void voegToe(const string& s) {   
        unique_ptr<TrieKnoop>* plaats = zoek(s);
        if(!*plaats){
            *plaats = (unique_ptr<TrieKnoop>) make_unique<TrieBlad>(s);
        } else if((*plaats)->isBlad()) {
            
        }
    }

};






