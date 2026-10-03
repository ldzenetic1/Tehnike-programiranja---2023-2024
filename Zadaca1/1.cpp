//TP 2023/2024: Zadaća 1, Zadatak 1
#include <cstdint>
#include <iostream>
#include <cmath>
#include <stdexcept>
#include <array>
#include <vector>
#include <limits>

enum class TretmanNegativnih {IgnorirajZnak, Odbaci, TretirajKao0, PrijaviGresku};

int BrojKvadrata(int n){
    if(n < 0) throw std::domain_error("Broj mora biti nenegativan");
    if(n == 0) return 0;
    int max_int = std::numeric_limits<int>::max();
    std::vector<int> broj_kvadrata(n + 1 , max_int);
    broj_kvadrata.at(0) = 0;
    broj_kvadrata.at(1) = 1;
    for(int i=2; i<=n; i++){
        int korijen = std::sqrt(i);
        for(int j=1; j<=korijen; j++){
            int kvadrat = broj_kvadrata.at(i-j*j) + 1;
            if(kvadrat < broj_kvadrata.at(i)){
                broj_kvadrata.at(i) = kvadrat;
            }
        }
    }
    int k = broj_kvadrata.at(n);
    return k;
}
std::array<std::vector<int>, 5> RazvrstajPoBrojuKvadrata(std::vector<int> v, TretmanNegativnih nacin){
    std::array<std::vector<int>, 5> niz;
    for(auto x : v){
        try{
            int broj_kvadrata;
            if(x < 0){
                if(nacin == TretmanNegativnih::IgnorirajZnak){
                    broj_kvadrata = BrojKvadrata(std::abs(x));
                    niz.at(broj_kvadrata).push_back(x);
                }
                else if(nacin == TretmanNegativnih::Odbaci)
                    continue;
                else if(nacin == TretmanNegativnih::TretirajKao0){
                    broj_kvadrata = 0;
                    niz.at(0).push_back(x);
                }
                else if(nacin == TretmanNegativnih::PrijaviGresku)
                    throw std::domain_error("Nije predvidjeno razvrstavanje negativnih brojeva");
            }
            broj_kvadrata = BrojKvadrata(x);
            niz.at(broj_kvadrata).push_back(x);
        }
        catch(std::domain_error izuzetak){
            if(nacin == TretmanNegativnih::PrijaviGresku){
                throw izuzetak;
            }
        }

    }
    return niz;
}
void IspisiNiz(std::array<std::vector<int>, 5> niz){
    for(int i=0; i<niz.size(); i++){
        if(niz.at(i).size() != 0){
        std::cout<<i<<": ";
        for(int j=0; j<niz.at(i).size(); j++){
            std::cout<<niz.at(i).at(j)<<" ";
        }
        std::cout<<std::endl;
        }
    }
}
int main ()
{
    std::vector<int> v;
    std::cout<<"Unesite brojeve (bilo koji ne-broj oznacava kraj):\n ";
    int i;
    do{
        std::cin>>i;
        if(std::cin)
            v.push_back(i);
    }while(std::cin);
    try{
        auto niz = RazvrstajPoBrojuKvadrata(v, TretmanNegativnih::PrijaviGresku);
        std::cout<<std::endl;
        std::cout<<"Rezultati razvrstavanja po broju kvadrata: \n";
        IspisiNiz(niz);
    }
    catch(std::domain_error izuzetak){
        std::cout<<"Nije podrzano razvrstavanje negativnih brojeva!";
    }
	return 0;
}
