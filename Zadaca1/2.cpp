//TP 2023/2024: Zadaća 1, Zadatak 2
#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>
#include <stdexcept>

void ZamijeniElemente(double &a, double &b){
    double temp = a;
    a = b;
    b = temp;
}
void PoredajPoVelicini (std::vector<double> &v){
    int vel = v.size();
    for(int i = 0; i < vel; i++)
        for(int j = i + 1; j < vel; j++)
            if(v.at(i) > v.at(j))
                ZamijeniElemente(v.at(i), v.at(j));
}
double Medijan (std::vector<double> &v){
    PoredajPoVelicini(v);
    int n = v.size();
    double medijan;
    if(n % 2 == 0) 
        medijan = (v.at(n / 2 - 1) + v.at(n / 2)) / 2.0 ;
    else 
        medijan =  v.at(n / 2);
    return medijan;
}

std::vector<std::vector<double>> MedijanskiFilter(std::vector<std::vector<double>> &mat, int N){
    if(N < 0) throw std::domain_error("Neispravan red filtriranja");
    int m = mat.size();
    std::vector<std::vector<double>> nova_matrica (m, std::vector<double>());
    for(int i = 0; i < m; i++){
        int n = mat.at(i).size();
        std::vector<double> red;
        for(int j = 0; j < n; j++){
            std::vector<double> v;
            for(int a = i-N; a <= i+N; a++){
                if(a < 0 || a >= m)
                    continue;
                int red_vel = mat.at(a).size();

                for(int b = j-N; b <= j+N; b++){
                    if(b < 0 || b>= red_vel)
                         continue;
                    v.push_back(mat.at(a).at(b));
                }
            }
            red.push_back(Medijan(v)); 
        }
        nova_matrica.at(i) = red;
    }
    return nova_matrica;
}
void UnesiMatricu(std::vector<std::vector<double>> &matrica){
    for(int i = 0; i < matrica.size(); i++)
        for(int j = 0; j < matrica.at(0).size(); j++)
            std::cin>>matrica.at(i).at(j);
}
void IspisiMatricu(std::vector<std::vector<double>> &matrica){
    for(int i=0; i<matrica.size(); i++){
        for(int j=0; j<matrica.at(0).size(); j++){
            std::cout<<std::setw(7)<<std::fixed<<std::setprecision(2)<<matrica.at(i).at(j);
        }
        std::cout<<std::endl;
    }
}
int main ()
{
    try{
        int m, n;
        std::cout<<"Unesite broj redova i kolona matrice: ";
        std::cin>>m>>n;
        std::cin.ignore(10000, '\n');
        std::vector<std::vector<double>> matrica(m, std::vector<double>(n));
        std::cout<<"Unesite elemente matrice: ";
        UnesiMatricu(matrica);
        int N;
        std::cout<<"Unesite red filtriranja: ";
        std::cin>>N;
        while(!std::cin){
            std::cout<<"Niste unijeli broj, pokusajte ponovo: ";
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cin>>N;
        }
        std::cout<<std::endl;
        std::vector<std::vector<double>> nova_matrica = MedijanskiFilter(matrica, N);
        std::cout<<"Matrica nakon filtriranja: \n";
        IspisiMatricu(nova_matrica);
    }
    catch(std::domain_error greska){
        std::cout<<"GRESKA: Neispravan red filtriranja!"<<std::endl;
    }
    /*try{
        std::vector<std::vector<double>> mat = {{2,2,1}, {0,2,0,2}, {1}, {16,6}};
        int N = 2;
        auto nova_matrica= MedijanskiFilter(mat, N);
        std::cout<<"Nakon filtriranja: \n";
        for(auto &red : nova_matrica){
            for(double e : red){
                std::cout<<e<<" ";
            }
            std::cout<<std::endl;
        }
    } catch(std::domain_error e){
    }*/
	return 0;
}
