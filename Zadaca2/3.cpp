//TP 2023/2024: Zadaća 2, Zadatak 3
#include <iostream>
#include <cmath>
#include <deque>
#include <iterator>
#include <vector>
#include <unordered_set>
#include <list>

template<typename IterTip1, typename IterTip2, typename IterTip3>
    IterTip3 UnijaBlokova(IterTip1 p1, IterTip1 p2, IterTip2 p3, IterTip2 p4, IterTip3 p5){
        std::unordered_set<typename std::common_type<typename std::iterator_traits<IterTip1>::value_type, typename std::iterator_traits<IterTip2>::value_type>::type> BezDuplikata;
        for(auto it1 = p1; it1 != p2; it1++){
            if(BezDuplikata.find(*it1) == BezDuplikata.end()){
                *p5 = *it1;
                p5++;
                BezDuplikata.insert(*it1);
            }
        }
        for(auto it2 = p3; it2 != p4; it2++){
            if(BezDuplikata.find(*it2) == BezDuplikata.end()){
                *p5 = *it2;
                p5++;
                BezDuplikata.insert(*it2);
            }
        }
        return p5;
    }


int main ()
{
    int n;
    std::cout<<"Unesite broj elemenata niza (max. 100): ";
    std::cin>>n;
    double niz[100];
    std::cout<<"Unesite elemente niza: ";
    for(int i=0; i<n; i++){
        std::cin>>niz[i];
    }
    int m;
    std::cout<<"Unesite broj elemenata deka: ";
    std::cin>>m;
    std::deque<double> d;
    std::cout<<"Unesite elemente deka: ";
    for(int i=0; i<m; i++){
        double element;
        std::cin>>element;
        d.push_back(element);
    }
    auto p1 = niz, p2=niz + n;
    auto p3=d.begin(), p4=d.end();
    std::vector<double> v;
    auto rezultat = UnijaBlokova(p1, p2, p3, p4, std::inserter(v, v.begin()));
    std::cout<<"Njihova unija glasi: ";
    for(auto x : v){
        std::cout<<x<<" ";
    }
	return 0;
}
