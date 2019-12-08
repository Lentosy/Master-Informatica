#include <string>
#include <iostream>

#include "patriciatrie.cpp"
int main(void) {
    std::string aandacht("aandacht");
    std::string ananas("ananas");
    std::string anabool("anabool");
    std::string xandro("xandro");
    std::string bert("bert");
    PatriciaTrie trie;
    
    //trie.voegToe(aandacht);
    trie.voegToe(ananas);
    trie.voegToe(xandro);
    trie.voegToe(bert);
    trie.voegToe(anabool);
    trie.teken("patriciatrie.dot");
    system("dot -Tpng patriciatrie.dot -o patriciatrie.jpg");


    return 0;
}