#include <string>
#include <iostream>
#include <bitset>
int main(void) {
    
    std::string s("epic");
    for(int i = 0; i < s.size(); i++){
        std::cout << std::bitset<CHAR_BIT>(s[i]) << " ";
    }

    return 0;
}