//TP 2023/2024: Zadaća 2, Zadatak 4
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

template<typename Tip>
    bool Kriterij(const std::vector<Tip> &v1, const std::vector<Tip> &v2){
        auto v1_max = *std::max_element(v1.begin(), v1.end());
        auto v2_max = *std::max_element(v2.begin(), v2.end());
        if(v1_max != v2_max){
            return v1_max > v2_max;
        }else{
            return v1 > v2;
        }
}

template<typename UporediviTip>
    void SortirajPoDobrotiRedova(std::vector<std::vector<UporediviTip>> &mat){
        std::sort(mat.begin(), mat.end(), Kriterij<UporediviTip>);
    }


int main ()
{
    std::vector<std::vector<int>> matrica;
    std::cout<<"Unesite elemente (* za kraj reda, * na pocetku reda za kraj unosa):";
    while(true){
        std::vector<int> v;
        int x;
        while(std::cin>>x){
            v.push_back(x);
        }
        std::cin.clear();
        std::cin.ignore(100000, '\n');
        if(v.size() != 0) matrica.push_back(v);
        else{
            break;
        }
    }
    SortirajPoDobrotiRedova(matrica);
    std::cout<<"\nMatrica nakon sortiranja:\n";
    for(const auto &red : matrica){
        for(int element : red){
            std::cout<<element<<" ";
        }
        std::cout<<std::endl;
    }
    std::cout<<"\nUnesite elemente sekvence koja se trazi (* za kraj reda): ";
    int broj;
    std::vector<int> sekvenca;
    while(std::cin>>broj){
        sekvenca.push_back(broj);
    }
    auto it = std::lower_bound(matrica.begin(), matrica.end(), sekvenca, Kriterij<int>);
    if(it != matrica.end() && *it == sekvenca){
        std::cout<<"\nTrazena sekvenca se nalazi u "<<std::distance(matrica.begin(), it) + 1<<". redu (nakon sortiranja)"<<std::endl;
    }
    else{
        std::cout<<"\nTrazena sekvenca se ne nalazi u matrici"<<std::endl;
    }
	return 0;
}
