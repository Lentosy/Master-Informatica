#ifndef RABINKARP_HPP
#define RABINKARP_HPP

#include <string>
using std::string;
#include <queue>
using std::queue;

class RabinKarp {
    public: RabinKarp(int p, int a) : prime{p}, alphabet_size{a} {}
    int hash(const string& str, int m) {
        int h = 0;
        for(int i=0;i<m;i++) {
            h = (alphabet_size * h + str[i]) % prime;
        }
        return h;
    }

    bool check_equality(const string& str, int pos, const string& pattern, int m) {
        // Because of the hashing trick and the bounding by prime, collisions may occur
        // this leaves you with two options 
        // 1. Monte Carlo strategy
        //    we always return true even, so it's possible to have a faulty outcome
        // return true;
        // 2. Las Vegas strategy (resource gamble)
        //    we do check, making the result always correct, but we do a full string compare O(n)
        for(int i=0;i<m;i++){
            if(str[pos+i]!=pattern[i]){
                return false;
            }
        }
        return true;
    }

    void search(const string& text, int n, const string& pattern, int m) {
        queue<int> empty;
        match_locations.swap(empty);
        int pattern_hash = hash(pattern,m);
        int text_hash = hash(text,m);

        // an immediate match?
        if(text_hash == pattern_hash && check_equality(text,0,pattern,m)){
            match_locations.push(0);
        }

        // we will need alphabet_size^(pattern_size-1) to calculate subsequent hash values
        int dm = 1;
        for(int i=0;i<m-1;i++){
            dm = (dm * alphabet_size) % prime;
        }

        // we did not find an immediate match, do sliding window
        for(int i=m;i<n;i++) {
            // + prime to avoid a negative text hash
            // the first character gets removed from the hash
            text_hash = (text_hash + prime - (dm * text[i-m]) %prime ) %prime;
            // the current character of the text gets properly added to the text_hash
            text_hash = (text_hash * alphabet_size + text[i]) % prime;
            
            // if the hashes match, we check the equality and store the location of the match start
            if(text_hash == pattern_hash && check_equality(text,i-m+1,pattern,m)) {
                match_locations.push(i-m+1);
            }
        }
    }

    public:
    queue<int> match_locations;
    private:
    int prime;
    int alphabet_size;
};

#endif