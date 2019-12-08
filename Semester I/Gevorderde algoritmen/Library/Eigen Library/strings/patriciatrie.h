#pragma once
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
    TrieNietBlad(int testindex) : testindex{testindex} {}

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

    PatriciaTrie();
    PatriciaTrie(unique_ptr<TrieKnoop>&& o);
    PatriciaTrie& operator=(unique_ptr<TrieKnoop>&& o);

    void teken(const char* bestandsnaam) const;

    unique_ptr<TrieKnoop>* zoek(const string& s);
    void voegToe(const string& s);

};






