#ifndef GALESHAPLEY_HPP
#define GALESHAPLEY_HPP
#include <vector>
using std::vector;
#include <map>
using std::map;

typedef vector<vector<int>> Preflist;

class GaleShapley {
    public: GaleShapley(const Preflist& m, const Preflist& f) : m_pref{m}, f_pref{f} {
        matches.clear();
        vector<int> free_men(m.size(),true);
        int bachelors = m.size();        
        // the free man selection could be improved with a stack, but I don't have the time right now
        while(bachelors > 0){
        int freeman=0;
        bool found = false;
        while(freeman<free_men.size() && !found){
            if(free_men[freeman] == true) {
                found = true;
            }
            else {
                freeman++;
            }
        }
        for(int i=0;i<m_pref.size() && free_men[freeman]; i++){
            int w = m_pref[freeman][i];
            if(matches.find(w) == matches.end()){
                matches.insert({w,freeman});
                free_men[freeman] = false;
                bachelors--;
            }
            else{
                int current_man = matches[w];
                if(!PprefersXoverY(f_pref,w,current_man,freeman)){
                    matches[w] = freeman;
                    free_men[freeman] = false;
                    free_men[current_man] = true;
                }
            }
        }
        }

    }

    private: 
    bool PprefersXoverY(const Preflist& pref,int P, int X, int Y) {
        for(const auto& i: pref[P]) {
            if(i == X) return true;
            if(i == Y) return false;
        }
        return false;
    }

    public:
    Preflist m_pref;
    Preflist f_pref;
    map<int,int> matches;
};

#endif