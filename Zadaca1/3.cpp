// TP 2023/2024: Zadaća 1, Zadatak 3
#include <cctype>
#include <climits>
#include <cmath>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>
#include <vector>

bool Cifra(char karakter) {
    if ((karakter >= '0' && karakter <= '9'))
        return true;
    return false;
}

long long int Konverzija(const std::string &s) {
    if (s.length() == 0)
        return 0;
    long long int pretvoreni = 0;
    int predznak = 1;
    int i = 0;
    while (i < s.length() && (s.at(i) == ' ' || s.at(i) == '\n' || s.at(i) == '\t'))
        i++;
    if (i < s.length() && s.at(i) == '-') {
        predznak = -1;
        i++;
    }
    while (i < s.length() && ((s.at(i) >= '0' && s.at(i) <= '9'))) {
        if (pretvoreni > (std::numeric_limits<long long int>::max() - (s.at(i) - '0')) / 10) {
            throw std::range_error("Prevelik broj");
        }
        if (pretvoreni < LLONG_MIN){
            throw std::range_error("Premali broj");
        }
        pretvoreni = pretvoreni * 10 + (s.at(i++) - '0');
    }
    return pretvoreni * predznak;
}
std::vector<long long int> BrojeviUStringu(std::string s) {
    std::vector<long long int> v;
    std::string trenutni;
    bool broj = false;
    for (int i = 0; i < s.length(); i++) {
        if (Cifra(s.at(i)) || (s.at(i) == '-' && !broj)) {
            trenutni += s.at(i);
            broj = true;
        }
        else if(s.at(i) == '-' && broj && i+1<s.length() && s.at(i+1) ==' '){
            v.push_back(Konverzija(trenutni));
            trenutni = "";
            broj = false;
        }
        else if (s.at(i) == '-' && broj) {
            v.push_back(Konverzija(trenutni));
            trenutni = "-";
        }else if(s.at(i) == '-' && s.at(i+1) ==' '){
            trenutni="";
            broj = false;
        }
        else {
            if (broj) {
                if (std::isalpha(s.at(i))) {
                    trenutni = "";
                    broj = false;
                }
                else {
                    v.push_back(Konverzija(trenutni));
                    trenutni = "";
                    broj = false;
                }
            }
        }
    }
    if (broj) {
        v.push_back(Konverzija(trenutni));
    }
    return v;
}
void IspisiVektor(std::vector<long long int> v) {
    for (auto &x : v)
        std::cout << x << " ";
}
int main() {
    try {
        std::string s;
        std::cout << "Unesite string: ";
        std::getline(std::cin, s);
        auto v = BrojeviUStringu(s);
        if (v.size() == 0) {
            std::cout << "Uneseni string ne sadrzi nijedan broj!";
        }
        else {
            std::cout << "Brojevi unutar stringa: ";
            IspisiVektor(v);
        }
    }
    catch (std::range_error greska) {
        std::cout << "PROBLEM: Uneseni string sadrzi prevelik broj!!!";
    }

    return 0;
}
