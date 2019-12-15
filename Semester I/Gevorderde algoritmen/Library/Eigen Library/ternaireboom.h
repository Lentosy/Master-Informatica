
#include <memory>
#include <string>

class TKnoop;

class TBoom : public std::unique_ptr<TKnoop> {
public:
    static char afsluitkarakter;

    using unique_ptr<TKnoop>::unique_ptr;
    void voegToe(const std::string& s);
};



class TKnoop {
public:
    friend class TBoom;
    char c;
    std::unique_ptr<TKnoop> kind[3];
};