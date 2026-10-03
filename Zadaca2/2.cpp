//TP 2023/2024: Zadaća 2, Zadatak 2
#include <iostream>
#include <cmath>
#include <vector>
#include <stdexcept>
#include <deque>
#include <iomanip>

template<typename Tip1, typename Tip2>
    auto fun(const Tip1 &x, const Tip2 &y)->decltype(x*y){
        return (x * y);
    }
double fun(double x, double y){
    return x*y;
}
template<typename TipMatrice1, typename TipMatrice2, typename Fun>
    auto GeneraliziraniKroneckerovProizvod(const TipMatrice1 &mat1, const TipMatrice2 &mat2, Fun f){
        if(mat1.empty() || mat2.empty()) throw std::domain_error("Parametri nemaju formu matrice");
        int BrojRedova1 = mat1.size();
        int BrojRedova2 = mat2.size();
        int BrojKolona1 = mat1.at(0).size();
        int BrojKolona2 = mat2.at(0).size();
        for(const auto &red : mat1){
            if(BrojRedova1 == 0 || red.size() != BrojKolona1) throw std::domain_error("Prvi parametar nema formu matrice");
        }
        for(const auto &red : mat2){
            if(BrojRedova2 == 0 || red.size() != BrojKolona2) throw std::domain_error("Drugi parametar nema formu matrice");
        }
        std::vector<std::vector<decltype(f(mat1.at(0).at(0), mat2.at(0).at(0)))>> proizvod;
        for(const auto &red1 : mat1){
            for(const auto &red2 : mat2){
                std::vector<decltype(f(red1.at(0), red2.at(0)))> RedProizvod;
                for(const auto &e1 : red1){
                    for(const auto &e2 : red2){
                        RedProizvod.push_back(f(e1, e2));
                    }
                }
                proizvod.push_back(RedProizvod);
            }
        }
    return proizvod;
}
int BrojCifara(int n){
    int brojac = n<=0;;
    while(n > 0){
        brojac++;
        n /= 10;
    }
    return brojac;
}
int main ()
{
    int m, n;
    std::cout<<"Unesite dimenzije prve matrice: ";
    std::cin>>m>>n;
    std::cout<<"\nUnesite elemente prve matrice: ";
    std::vector<std::deque<double>> mat1(m, std::deque<double>(n));
    for(int i=0; i<m; i++)
        for(int j=0; j<n; j++){
            double x;
            std::cin>>x;
            mat1.at(i).at(j) = x;
        }
    int p, q;
    std::cout<<"\nUnesite dimenzije druge matrice: ";
    std::cin>>p>>q;
    std::deque<std::vector<double>> mat2(p, std::vector<double>(q));
    std::cout<<"\nUnesite elemente druge matrice: ";
    for(int i=0; i<p; i++)
        for(int j=0; j<q; j++){
            double x;
            std::cin>>x;
            mat2.at(i).at(j) = x;
        }
    try{
        auto matrica = GeneraliziraniKroneckerovProizvod(mat1, mat2, fun<double, double>);
        int SirinaKolone = 0;
        for(int i=0; i<m*p; i++){
            for(int j=0; j<n*q; j++){
                if(BrojCifara(matrica.at(i).at(j) > SirinaKolone)){
                    SirinaKolone = BrojCifara(matrica.at(i).at(j)) +1;
                }
            }
        }
        
        std::cout<<"\nNjihov Kroneckerov proizvod glasi:\n"<<std::endl;
        for(int i=0; i<m; i++){
            for(int k=0; k<p; k++){
                for(int j=0; j<n; j++){
                    for(int l=0; l<q; l++){
                        std::cout<<std::setw(SirinaKolone + 1)<<matrica.at(i*p + k).at(j*q +l);
                    }
                    std::cout<<" ";
                }
                std::cout<<std::endl;
            }
        }
    }
    catch(std::domain_error &e){
        std::cout<<e.what();
    }
    catch(std::runtime_error &r){
        std::cout<<r.what();
    }

	return 0;
}
