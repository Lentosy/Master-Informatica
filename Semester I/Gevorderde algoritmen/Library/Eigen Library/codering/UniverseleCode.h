#include <vector>
#include <string>
#include <cmath>
#include <iostream>
#include <iomanip>
using std::string;

class UniverseleCode {
public:
    static string eliasgamma(int n);
    static string eliasdelta(int n);
    static string fibonacci(int n);
};


string UniverseleCode::eliasgamma(int n) {
    string code;

    // bit representatie
    // zoek grootste i zodat 2^i <= n
    int aantalBits = 0;
    while(std::pow(2, aantalBits) <= n)
        aantalBits++;
     
    for(int i = 0; i < aantalBits - 1; i++)
        code += '0';

    int i = aantalBits - 1;
    do {
        if(std::pow(2, i) <= n){
            code += '1';
            n -= std::pow(2, i);
        } else code += '0';
        i--;
    } while(i >= 0);
    
    return code;
}

string UniverseleCode::eliasdelta(int n){
    string code;

    // bit representatie
    // zoek grootste i zodat 2^i <= n
    int aantalBits = 0;
    while(std::pow(2, aantalBits) <= n)
        aantalBits++;
     
    code += eliasgamma(aantalBits);

    n -= std::pow(2, aantalBits - 1);
    int i = aantalBits - 2;
    do {
        if(std::pow(2, i) <= n){
            code += '1';
            n -= std::pow(2, i);
        } else code += '0';
        i--;
    } while(i >= 0);
    
    return code;
}

string UniverseleCode::fibonacci(int n) {
    string code;
    
    std::vector<int> fibonaccireeks = {1, 2};
    int F1 = fibonaccireeks[0];
    int F2 = fibonaccireeks[1];
    while(F1 + F2 < n) {
        fibonaccireeks.push_back(F1 + F2);
        F1 = F2;
        F2 = fibonaccireeks[fibonaccireeks.size() - 1];
    }
    
    std::vector<bool> gebruikteFibonacciGetallen(fibonaccireeks.size(), false);
    int i = fibonaccireeks.size();
    while(i >= 0 && n > 0) {
        int fibonaccigetal = fibonaccireeks[i];
        if(fibonaccigetal <= n){
            gebruikteFibonacciGetallen[i] = true;
            n -= fibonaccigetal;
            i--;
        }
        i--;
    }

    for(int i = 0; i < gebruikteFibonacciGetallen.size(); i++){
        if(gebruikteFibonacciGetallen[i]) code += '1';
        else code += '0';
        
    }

    code += '1'; // afsluitkarakter
    return code;
}