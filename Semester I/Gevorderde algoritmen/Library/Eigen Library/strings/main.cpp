#include <string>
#include <iostream>

#include "patriciatrie.cpp"
int main(void) {
    
    std::string ananas("ananas");
    std::string anaconda("anaconda");
    PatriciaTrie trie;
    
    trie.voegToe(ananas);
    trie.voegToe(anaconda);
    trie.teken("patriciatrie.dot");
    return 0;
}