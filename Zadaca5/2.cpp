//TP 2023/2024: Zadaća 5, Zadatak 2
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <functional>
#include <iomanip>

class Berza{
    std::vector<int> cijene;
    int min_cijena;
    int max_cijena;
    
public:
    bool IspravnostCijene(){
        return std::all_of(cijene.begin(), cijene.end(), [this](int cijena){
            return cijena >= min_cijena && cijena <= max_cijena;
        });
    }
    Berza(int min, int max) : min_cijena(min), max_cijena(max){
        if(min < 0 || max < 0 || min > max) throw std::range_error("Ilegalne granicne cijene");
    }
    explicit Berza(int max) : max_cijena(max), min_cijena(0) {
        if(max < 0) throw std::range_error("Ilegalne granicne cijene");
    }
    void RegistrirajCijenu(int cijena){
        if(cijena < min_cijena || cijena > max_cijena) throw std::range_error("Ilegalna cijena");
        cijene.push_back(cijena);
    }
    int DajBrojRegistriranihCijena() const { return cijene.size();}
    void BrisiSve() {cijene.clear();};
    int DajMinimalnuCijenu() const {
        if(cijene.size() == 0) throw std::range_error("Nema registriranih cijena");
        return *std::min_element(cijene.begin(), cijene.end());
    }
    int DajMaksimalnuCijenu() const {
        if(cijene.size() == 0) throw std::range_error("Nema registriranih cijena");
        return *std::max_element(cijene.begin(), cijene.end());
    }
    bool operator !(){
        return cijene.empty();
    }
    int DajBrojVecihOd(int vrijednost);
    void Ispisi() const;
    int operator [](int indeks) const{
        if(indeks < 1 || indeks > cijene.size()) throw std::range_error("Neispravan indeks");
        return cijene[indeks - 1];
    }
    Berza &operator ++(){
        std::for_each(cijene.begin(), cijene.end(), [this](int &cijena){
            if(cijena + 100 > max_cijena) throw std::range_error("Prekoracen dozvoljeni opseg cijena");
            cijena += 100;});
        return *this;
    }
    Berza operator ++(int){
        Berza temp = *this;
        ++(*this);
        return temp;
    }
    Berza &operator --(){
        std::for_each(cijene.begin(), cijene.end(), [this](int &cijena){ 
            if(cijena - 100 < min_cijena) throw std::range_error("Prekoracen dozvoljeni opseg cijena");
            cijena -= 100;});
        return *this;
    }
    Berza operator --(int){
        Berza temp = *this;
        --(*this);
        return temp;
    }
    Berza operator -()const;
    Berza operator +(int y) const;
    Berza operator -(int y) const;
    Berza operator -(const Berza &b) const;
    Berza operator +(const Berza &b) ;
    Berza &operator +=(int y);
    Berza &operator -=(int y);
    Berza &operator +=(const Berza &b);
    Berza &operator -=(const Berza &b);

    friend Berza operator +(int y, const Berza &b);
    friend Berza operator -(int y, const Berza &b);
    friend bool operator ==(const Berza &b1, const Berza &b2);
    friend bool operator !=(const Berza &b1, const Berza &b2);
};
Berza Berza::operator +(const Berza &b){
    if(cijene.size() != b.cijene.size() || min_cijena != b.min_cijena || max_cijena != b.max_cijena)
        throw std::domain_error("Nesaglasni operandi");
    Berza temp = *this;
    std::transform(temp.cijene.begin(), temp.cijene.end(), b.cijene.begin(), temp.cijene.begin(), std::plus<int>());
    if(!temp.IspravnostCijene()) throw std::domain_error("Prekoracen dozvoljeni opseg cijena");
    return temp;
     

    
}
bool operator ==(const Berza &b1, const Berza &b2){
    return b1.cijene.size() == b2.cijene.size() && std::equal(b1.cijene.begin(), b1.cijene.end(), b2.cijene.begin());
}
bool operator !=(const Berza &b1, const Berza &b2){
    return !(b1 == b2);
}
Berza &Berza::operator +=(const Berza &b){
    if(cijene.size() != b.cijene.size() || min_cijena != b.min_cijena || max_cijena != b.max_cijena)
        throw std::domain_error("Nesaglasni operandi");
    std::transform(cijene.begin(), cijene.end(), b.cijene.begin(), cijene.begin(), std::plus<int>());
    if(!IspravnostCijene())
        throw std::domain_error("Prekoracen dozvoljeni opseg cijena");
    return *this;
}
Berza &Berza::operator -=(const Berza &b){
    if(cijene.size() != b.cijene.size() || min_cijena != b.min_cijena || max_cijena != b.max_cijena)
        throw std::domain_error("Nesaglasni operandi");
    std::transform(cijene.begin(), cijene.end(), b.cijene.begin(), cijene.begin(), std::minus<int>());
    if(!IspravnostCijene())
        throw std::domain_error("Prekoracen dozvoljeni opseg cijena");
    return *this;
}
Berza &Berza::operator -=(int x){
        std::for_each(cijene.begin(), cijene.end(), [=](int &cijena){
            if(cijena - x < min_cijena) throw std::domain_error("Prekoracen dozvoljeni opseg cijena");
            cijena -= x;
        });
        return *this;
    }
Berza &Berza::operator +=(int x){
        std::for_each(cijene.begin(), cijene.end(), [=](int &cijena){
            if(cijena + x > max_cijena) throw std::domain_error("Prekoracen dozvoljeni opseg cijena");
            cijena += x;
        });
        return *this;
    }
Berza Berza::operator -(const Berza &b) const{
    if(cijene.size() != b.cijene.size() || min_cijena != b.min_cijena || max_cijena != b.max_cijena)
        throw std::domain_error("Nesaglasni operandi");
    Berza temp = *this;
    std::transform(temp.cijene.begin(), temp.cijene.end(), b.cijene.begin(), temp.cijene.begin(), std::minus<int>());
    if(!temp.IspravnostCijene()){
        throw std::domain_error("Prekoracen dozvoljeni opseg cijena");
    }
    return temp;
}
Berza operator -(int y, const Berza &b){
    Berza temp = b;
    std::transform(temp.cijene.begin(), temp.cijene.end(), temp.cijene.begin(), std::bind(std::minus<int>(), y, std::placeholders::_1));
    if(!temp.IspravnostCijene()){
        throw std::domain_error("Prekoracen dozvoljeni opseg cijena");
    }
    return temp;
}
Berza operator +(int y, const Berza &b){
    return b + y;
}
Berza Berza::operator +(int y) const{
    Berza temp = *this;
    std::for_each(temp.cijene.begin(), temp.cijene.end(), [=](int &cijena){cijena += y;});
    if(!temp.IspravnostCijene()){
        throw std::domain_error("Prekoracen dozvoljeni opseg cijena");
    }
    return temp;
}
Berza Berza::operator -(int y) const{
    Berza temp = *this;
    std::for_each(temp.cijene.begin(), temp.cijene.end(), [=](int &cijena){cijena -= y;});
    if(!temp.IspravnostCijene()){
        throw std::domain_error("Prekoracen dozvoljeni opseg cijena");
    }
    return temp;
}
Berza Berza::operator -()const{
    Berza temp = *this;
    int suma = min_cijena + max_cijena;
    std::transform(temp.cijene.begin(), temp.cijene.end(), temp.cijene.begin(), std::bind(std::minus<int>(), suma, std::placeholders::_1));
    return temp;
}
int Berza::DajBrojVecihOd(int vrijednost){
        if(cijene.size() == 0) throw std::range_error("Nema registriranih cijena");
        return std::count_if(cijene.begin(), cijene.end(), std::bind(std::greater<int>(), std::placeholders::_1, vrijednost));
    }
void Berza::Ispisi() const{
    if(cijene.size() == 0) return;
    std::vector<int> pomocni = cijene;
    std::sort(pomocni.begin(), pomocni.end(), std::greater<int>());
    std::for_each(pomocni.begin(), pomocni.end(), [](int cijena){
        std::cout<<std::fixed<<std::setprecision(2)<<cijena / 100.0<<std::endl;
    });
}
int main ()
{
    try{
        Berza b(0, 2000);
        b.RegistrirajCijenu(1550);
        b.RegistrirajCijenu(10);
        b.RegistrirajCijenu(1233);
        std::cout<<"Broj registriranih cijena: "<<b.DajBrojRegistriranihCijena()<<std::endl;
        std::cout<<"Minimalna cijena je: "<<b.DajMinimalnuCijenu()<<"\n";
        std::cout<<"Maksimalna cijena je: "<<b.DajMaksimalnuCijenu()<<"\n";
        std::cout<<"Cijene:\n";
        b.Ispisi();
        ++b;
        std::cout<<"Test prefiksnog operatora ++: ";
        b.Ispisi();
        b++;
        std::cout<<"Test postfiksnog operatora ++: ";
        b.Ispisi();
        --b;
        std::cout<<"Test prefiksnog operatora --: ";
        b.Ispisi();
        b--;
        std::cout<<"Test postfiksnog opeartora --:";
        b.Ispisi();
        Berza b2 = -b;
        std::cout<<"test unarni :";
        b2.Ispisi();
        Berza b3 = b + 300;
        b3.Ispisi();
    }
    catch(std::exception &e){
        std::cout<<"Izuzetak: "<<e.what()<<std::endl;
    }


	return 0;
}
