// TP 2023/2024: Zadaća 3, Zadatak 4
#include <cmath>
#include <iostream>
#include <list>
#include <stdexcept>
#include <vector>


std::vector<int> Razbrajanje(int N, int M) {
    std::list<int> lista;
    for (int i = 1; i <= N; i++)
        lista.push_back(i);
    std::vector<int> v;
    auto it = lista.begin();
    while (!lista.empty()) {
        v.push_back(*it);
        it = lista.erase(it);
        if(it == lista.end())
            it = lista.begin();
        for(int i = 0; i < M - 1; i++){
            if(std::next(it) == lista.end())
                it = lista.begin();
            else
                it++;
        }
    }
    return v;
}

int OdabirKoraka(int N, int K) {
    if(K > N || K <= 0 || N <= 0) throw std::domain_error("Broj blokova i redni broj bloka su pozitivni cijeli brojevi i redni broj bloka ne moze biti veci od broja blokova");
    for (int M = 1; M <= N; M++) {
        std::vector<int> v = Razbrajanje(N, M);
        if (v.at(v.size() - 1) == K)
        return M;
    }
    return 0;
}
int main() {
    int N;
    std::cout << "Unesite broj distrikta u gradu: ";
    std::cin >> N;
    int K;
    std::cout << "Unesite redni broj distrikta u kojem se nalazi restoran: ";
    std::cin >> K;
    try{
        int korak = OdabirKoraka(N, K);
        if (korak != 0)
            std::cout << "Trazeni korak: " << korak << std::endl;
        else
            std::cout << "Trazeni korak ne postoji" << std::endl;
    }
    catch(std::domain_error){
        std::cout<<"Broj blokova i redni broj bloka su pozitivni cijeli brojevi i redni broj bloka ne moze biti veci od broja blokova";
    }
    return 0;
}
