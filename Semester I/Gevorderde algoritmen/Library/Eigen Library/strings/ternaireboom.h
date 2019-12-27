
#include <memory>
#include <algorithm>
#include <string>

class TKnoop;

class TBoom : public std::unique_ptr<TKnoop> {
public:
    static char afsluitkarakter;

    using unique_ptr<TKnoop>::unique_ptr;

    TBoom(std::unique_ptr<TKnoop>&& o) : std::unique_ptr<TKnoop>(std::move(o)) {}
    TBoom& operator=(std::unique_ptr<TKnoop>&& o){
        std::unique_ptr<TKnoop>::operator=(std::move(o));
        return *this;
    };

    void voegToe(const std::string& s);
};



class TKnoop {
public:
    friend class TBoom;
    char c;
    std::unique_ptr<TKnoop> kind[3];
};



void TBoom::voegToe(const std::string& s) {
    std::string woord = s + afsluitkarakter;
    std::unique_ptr<TKnoop>* plaats = this;

    int index = 0;
    while(plaats && index < s.size()) {
        if(s[index] == (*plaats)->c) {
           plaats = &(*plaats)->kind[1];
           index++;
        } else if (s[index] < (*plaats)->c) {
            plaats = &(*plaats)->kind[0];
        } else {
            plaats = &(*plaats)->kind[2];
        }
    }

    for(int i = index; i < s.size(); i++){
        char karakter = s[index];
        *plaats = std::make_unique<TKnoop>();
        (*plaats)->c = karakter;
        plaats = &(*plaats)->kind[1];
    }

}


