//TP 2023/2024: Zadaća 3, Zadatak 2
#include <iostream>
#include <cmath>
#include <map>
#include <vector> 
#include <string>
#include <set>
#include <tuple>
#include <algorithm>

typedef std::map<std::string, std::vector<std::string>> Knjiga;
typedef std::map<std::string, std::set<std::tuple<std::string, int, int>>> IndeksPojmova;

bool InterpunkcijskiZnak(char znak){
    const std::string s = ".,;:!?";
    for(char c : s){
        if(znak == c) return true;
    }
    return false;
}
std::string Rijec(const std::string &rijec){
    std::string nova_rijec;
    bool tren_rijec = false;
    for(char c : rijec){
        if(std::isalpha(c) || std::isdigit(c)){
            nova_rijec += std::toupper(c);
            tren_rijec = true;
        }else if(tren_rijec){
            nova_rijec += ' ';
            tren_rijec = false;
        }
    }
    return nova_rijec;
}
/*IndeksPojmova KreirajIndeksPojmova (const Knjiga &k){
    IndeksPojmova indeks_pojmova;
    for(const auto &p : k){
        const std::string &poglavlje = p.first;
        const std::vector<std::string> &stranice = p.second;
        for(int i = 0; i< stranice.size(); i++){
            auto pocetak = stranice[i].begin();
            auto kraj = stranice[i].end();
            while(pocetak != kraj){
                pocetak = std::find_if_not(pocetak, kraj, [](char c){return std::isspace(c);});
                auto kraj_rijeci = std::find_if(pocetak, kraj, [](char c){return std::isspace(c);});
                if(pocetak != kraj){
                    std::string rijec(pocetak, kraj_rijeci);
                    rijec = Rijec(rijec);
                    if(!rijec.empty())
                    indeks_pojmova[rijec].insert(std::make_tuple(poglavlje, i+1,(pocetak - stranice[i].begin()+1)));
                }
                pocetak = kraj_rijeci;
            }
        }
    }
    return indeks_pojmova;
}*/
IndeksPojmova KreirajIndeksPojmova(const Knjiga &k){
    IndeksPojmova indeks_pojmova;
    for(const auto &p : k){
        const std::string &poglavlje = p.first;
        const std::vector<std::string> &stranice = p.second;
        for(int i = 0; i < stranice.size(); i++){
            const std::string &s = stranice[i];
            for(int j = 0; j < s.length(); j++){
                if(std::isalnum(s[j]) && (j == 0 || !std::isalnum(s[j - 1]))){
                    std::string rijec;
                    int pocetak = j;
                    while(i < s.length() && std::isalnum(s[j])) rijec += std::toupper(s[j++]);
                    indeks_pojmova[rijec].insert(std::make_tuple(poglavlje, i+1, pocetak + 1));
                }
            }
        }
    }
    return indeks_pojmova;
}
bool IspravnostRijeci(const std::string  &rijec){
   return std::all_of(rijec.begin(), rijec.end(), [](char c){return std::isalpha(c) || std::isdigit(c);});
}
std::set<std::tuple<std::string, int, int>> PretraziIndeksPojmova(const std::string &rijec, const IndeksPojmova &indeks_pojmova){
    if(!IspravnostRijeci(rijec)) throw std::domain_error("Neispravna rijec");
    std::string nova_rijec = Rijec(rijec);
    auto it = indeks_pojmova.find(nova_rijec);
    if( it != indeks_pojmova.end()){
        return it->second;
    }
    /*else {
        std::cout<<"Rijec nije nadjena!";
        return {};
    }*/
    throw std::logic_error("Rijec nije nadjena!");
}
void IspisiIndeksPojmova(const IndeksPojmova &indeks_pojmova){
    for(const auto &par : indeks_pojmova){
        std::cout<<par.first<<": ";
        for(auto it = par.second.begin(); it != par.second.end();){
            std::cout<<std::get<0>(*it)<<"/"<<std::get<1>(*it)<<"/"<<std::get<2>(*it);
            if(++it != par.second.end()) std::cout<<", ";
        }
        std::cout<<std::endl;
    }
    //std::cout<<std::endl;
}
int main ()
{
    Knjiga knjiga;
    std::string poglavlje, stranica;
    int vel = knjiga.size();
    do{
        std::cout<<"Unesite naziv poglavlja: \n";
        std::getline(std::cin, poglavlje);
        if(poglavlje.length() == 0) break;
        do{
            std::cout<<"Unesite sadrzaj stranice "<<knjiga[poglavlje].size() + 1<<": \n";
            std::getline(std::cin, stranica);
            if(stranica.length() == 0) break;
            knjiga[poglavlje].push_back(stranica);
        }while(stranica.length() != 0);      
    }while(poglavlje.length() != 0);

    IndeksPojmova indeks_pojmova = KreirajIndeksPojmova(knjiga);
    std::cout<<"\nKreirani indeks pojmova:\n";
    IspisiIndeksPojmova(indeks_pojmova);
    std::cout<<std::endl;
    std::string rijec;
    do{
        std::cout<<"Unesite rijec: \n";
        std::getline(std::cin, rijec);
        if(rijec.length() == 0) break;
        try{
            auto pozicije = PretraziIndeksPojmova(rijec, indeks_pojmova);
            if(!pozicije.empty()){
                std::cout<<"Rijec nadjena na pozicijama: ";
                for(const auto &p : pozicije){
                    std::cout<<std::get<0>(p)<<"/"<<std::get<1>(p)<<"/"<<std::get<2>(p)<<" ";
                }
            }
            std::cout<<std::endl;
        }
        catch(const std::domain_error &e){
            std::cout<<"Neispravna rijec!\n";
        }
        catch(const std::logic_error &e){
            std::cout<<"Rijec nije nadjena!\n";
        }
    }while(true);
    std::cout<<"Dovidjenja!\n"<<std::endl;
	return 0;
}
