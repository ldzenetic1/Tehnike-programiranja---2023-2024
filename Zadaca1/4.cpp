//TP 2023/2024: Zadaća 1, Zadatak 4
#include <iostream>
#include <cmath>
#include <string>
#include <stdexcept>
#include <cctype>

bool VelikoSlovo(char slovo){
    if(slovo >= 'A' && slovo <= 'Z') return true;
    return false;
}
bool IspravanKljuc(std::string s){
    if(s.length() == 0) return false;
    for(char c : s){
        if(!(c >= 'A' && c <='Z')) return false;
    }
    return true;
}
std::string ViginereSifriranje(std::string poruka, std::string kljuc){
    if(!IspravanKljuc(kljuc)) 
        throw std::domain_error("Neispravan kljuc");
    std::string sifrirana_poruka;
    int k_indeks = 0;
    for(char c : poruka){
        if(std::isalpha(c)){
            char slovo_kljuca = kljuc.at(k_indeks % kljuc.length());
            int slovo = VelikoSlovo(c) ? 'A' : 'a';
            char novo_slovo = slovo + ((c - slovo + (slovo_kljuca - 'A')) % 26);
            sifrirana_poruka += novo_slovo;
            k_indeks++;
        }
        else{
            sifrirana_poruka += c;
        }
    }
    return sifrirana_poruka;   
}
std::string ViginereDesifriranje(std::string poruka, std::string kljuc){
    if(!IspravanKljuc(kljuc)) 
        throw std::domain_error("Neispravan kljuc");
    std::string desifrirana_poruka;
    int k_indeks = 0;
    for(char c : poruka){
        if(std::isalpha(c)){
            char slovo_kljuca = kljuc.at(k_indeks % kljuc.length());
            int slovo = VelikoSlovo(c) ? 'A' : 'a';
            char novo_slovo = slovo + ((c-slovo - (slovo_kljuca - 'A') + 26) % 26);
            desifrirana_poruka += novo_slovo;
            k_indeks++;
        }
        else{
            desifrirana_poruka += c;
        }
    }
    return desifrirana_poruka;
}
int main ()
{
    std::string kljuc;
    do{
        std::cout<<"Unesite kljuc: ";
        std::getline(std::cin, kljuc);
        if(!IspravanKljuc(kljuc))
            std::cout<<"Neispravan kljuc, ponovite unos: \n";
        if(IspravanKljuc(kljuc))
            std::cout<<"Kljuc prihvacen. Unesite poruku: ";
        }while(!IspravanKljuc(kljuc));

        std::string poruka;
        std::getline(std::cin, poruka);
        auto sifrirano = ViginereSifriranje(poruka, kljuc);
        std::cout<<"Sifrirana poruka: "<<sifrirano<<std::endl;
        std::cout<<std::endl;
        std::string kljuc2;
        bool pogodjeno = false;
        do{        
            std::cout<<"Pokusajte pogoditi kljuc: ";
            std::getline(std::cin, kljuc2);
            try{ 
                if(!IspravanKljuc(kljuc2))
                    std::cout<<"Niste pogodili kljuc, probajte ponovo!\n";
                std::string desifrirano = ViginereDesifriranje(sifrirano, kljuc2);
                std::cout<<"Pokusaj desifriranja: "<<desifrirano<<std::endl;
                if(desifrirano == poruka){
                    std::cout<<"Bravo, pogodili ste kljuc!\n";
                    pogodjeno = true;
                }
                else{
                    std::cout<<"Niste pogodili kljuc, probajte ponovo!\n";
                }
            }
            catch(std::domain_error greska){
            }
        }while(!pogodjeno);
        
	return 0;  
}
