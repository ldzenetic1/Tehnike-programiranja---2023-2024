//TP 2023/2024: Zadaća 2, Zadatak 5
#include <iostream>
#include <cmath>
#include <stdexcept>
#include <vector>
#include <deque>
#include <iterator>

template<typename KontejnerskiTip1, typename KontejnerskiTip2>
    auto KreirajTablicuMnozenja(const KontejnerskiTip1 &sekvenca1, const KontejnerskiTip2 &sekvenca2){
        int vel1 = std::distance(std::begin(sekvenca1), std::end(sekvenca1));
        int vel2 = std::distance(std::begin(sekvenca2), std::end(sekvenca2));
        if(vel1 != vel2) throw std::range_error("Kontejneri nisu iste duzine");
        if(vel1 == 0 || vel2 == 0){
            std::cout<<"Kontejneri su prazni";
        }
        auto it1 = std::begin(sekvenca1);
        auto it2 = std::begin(sekvenca2);
        for(; it1 != std::end(sekvenca1) && it2 != std::end(sekvenca2); it1++, it2++){
            if(*it1 * *it2 != *it2 * *it1){
                throw std::logic_error("Nije ispunjena pretpostavka o komutativnosti");
            }
        }
        using Tip = decltype(*std::begin(sekvenca1) * *std::begin(sekvenca2));
        Tip ** matrica = nullptr;
        try{
            matrica = new Tip*[vel1];
            for(int i = 0; i < vel1; i++){
                matrica[i] = nullptr;
            }
            matrica[0] = new Tip [vel1*(vel1+1)/2];
            for(int i = 1; i < vel1; i++){
                matrica[i] = matrica[i - 1] + i;
            }
            auto it1 = std::begin(sekvenca1);
            try{
                for(int i=0; i<vel1; i++){
                    auto it2 = std::begin(sekvenca2);
                    for(int j = 0; j <= i; j++){
                        matrica[i][j] = *it1 * *it2;
                        if(matrica[i][j] != *it2 * *it1){
                           throw std::logic_error("Nije ispunjena pretpostavka o komutativnosti");
                        }
                        it2++;
                    }
                    it1++;
                }
            }catch(std::logic_error e){
                throw std::range_error("Nije ispunjena pretpostavka o komutativnosti");
            }
        }
        catch(...){
            if(matrica != nullptr){
                for(int i = 0; i < vel1; i++){
                    delete[] matrica[i];
                }
                delete[] matrica;
            }
            throw std::range_error("Nema dovoljno memorije");
        }
        return matrica;
    }
int main ()
{
    int n;
    std::cout<<"\nDuzina sekvenci:";
    std::cin>>n;
    std::vector<double> v(n);
    std::cout<<"\nElementi prve sekvence:";
    for(int i = 0; i < n; i++) std::cin>>v.at(i);
    std::deque<double> d(n);
    std::cout<<"\nElementi druge sekvence:";
    for(int i = 0; i < n; i++) std::cin>>d.at(i);
    try{
        auto mat = KreirajTablicuMnozenja(v, d);
        std::cout<<"\nTablica mnozenja:\n";
        auto it = std::begin(v);
        for(int i = 0; it != std::end(v); i++, it++){
            auto it2 = std::begin(d);
            for(int j = 0; it2 != std::end(d) && j <= i; j++, it2++){
                std::cout<<mat[i][j]<<" ";
            }
            std::cout<<std::endl;
        }
        for(int i = 0; i < n; i++){
            delete[] mat[i];
        }
        delete[] mat;
    }
    catch(std::range_error &e){
        std::cout<<"Nije ispunjena pretpostavka o komutativnosti";
    }
    catch(...){
        std::cout<<"Nepoznata greska";
    }

	return 0;
}
