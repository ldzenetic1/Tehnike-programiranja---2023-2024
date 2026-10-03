//TP 2023/2024: Zadaća 5, Zadatak 1
#include <iostream>
#include <cmath>
#include <limits>
#include <string>
#include <sstream>

class Razlomak{
    long long int brojnik;
    long long int nazivnik;
    static long long int NZD(long long int a, long long int b){
        while(b != 0){
            long long int temp = b;
            b = a % b;
            a = temp;
        }
        return a;
    }
    void Krati(){
        long long int temp = NZD(brojnik, nazivnik);
        brojnik /= temp;
        nazivnik /= temp;
        if(nazivnik < 0){
            brojnik = -brojnik;
            nazivnik = -nazivnik;
        }
    }
    static bool PrekoracenoSabiranje(long long int a, long long int b){
        if(b > 0) return a > std::numeric_limits<long long int>::max() - b;
        else return a < std::numeric_limits<long long int>::min() - b;
    }
    static bool PrekoracenoOduzimanje(long long int a, long long int b){
        if(b > 0) return a < std::numeric_limits<long long int>::min() + b;
        else return a > std::numeric_limits<long long int>::max() + b;
    }
    static bool PrekoracenoMnozenje(long long int a, long long int b){
        if(a == 0 || b == 0) return false;
        if(b > 0) return a > std::numeric_limits<long long int>::max() / b || a < std::numeric_limits<long long int>::min() / b;
        else return a > std::numeric_limits<long long int>::max() / b  || a < std::numeric_limits<long long int>::min() / b;
    }
public:
    Razlomak(long long int brojnik = 0, long long int nazivnik = 1){
        if(nazivnik == 0) throw std::logic_error("Nekorektan razlomak");
        this->brojnik = brojnik;
        this->nazivnik = nazivnik;
        Krati();
    }
    long long int DajBrojnik() const {return brojnik;}
    long long int DajNazivnik() const {return nazivnik;}
    void PostaviNazivnik(long long int n) {nazivnik = n;}
    void PostaviBrojnik(long long int b) {brojnik = b;}
    Razlomak &operator +=(const Razlomak &a);
    Razlomak &operator -=(const Razlomak &a);
    Razlomak &operator /=(const Razlomak &a);
    Razlomak &operator *=(const Razlomak &a);
    Razlomak &operator ++(){
        *this += 1;
        return *this;
    }
    Razlomak &operator --(){
        *this -= 1;
        return *this;
    }
    Razlomak operator ++(int){
        Razlomak temp = *this;
        ++(*this);
        return temp;
    }
    Razlomak operator --(int){
        Razlomak temp = *this;
        --(*this);
        return temp;
    }
    long double dec() const{
        return static_cast<long double>(brojnik) / static_cast<long double>(nazivnik);
    }
    friend Razlomak operator +(const Razlomak &a, const Razlomak &b);
    friend Razlomak operator -(const Razlomak &a, const Razlomak &b);
    friend Razlomak operator *(const Razlomak &a, const Razlomak &b);
    friend Razlomak operator /(const Razlomak &a, const Razlomak &b);
    bool operator <(const Razlomak &a) const{
        return dec() < a.dec();
    }
    bool operator >(const Razlomak &a) const{
        return dec() > a.dec();
    }
    bool operator <=(const Razlomak &a) const{
        return dec() <= a.dec();
    }
    bool operator >=(const Razlomak &a) const{
        return dec() >= a.dec();
    }
    bool operator ==(const Razlomak &a) const{
        return dec() == a.dec();
    }
    bool operator !=(const Razlomak &a) const{
        return dec() != a.dec();
    }
    friend std::ostream &operator <<(std::ostream &tok, const Razlomak &r);
    friend std::istream &operator >>(std::ostream &tok, Razlomak &r);
    operator long double()const {
        return static_cast<long double>(brojnik) / static_cast<long double>(nazivnik);
    }
};
std::ostream &operator <<(std::ostream &tok, const Razlomak &r){
    if(r.nazivnik == 1) tok<<r.brojnik;
    else tok<<r.brojnik<<"/"<<r.nazivnik;
    return tok;
}
std::istream &operator >>(std::istream &tok, Razlomak &r){
    char granica;
    long long int b, n;
    tok>>b;
    tok>>granica;
    if(granica =='/'){
        tok>>n;
    }
    else{
        n = 1;
        tok.putback(granica);
    }
    r.PostaviBrojnik(b);
    r.PostaviNazivnik(n);
    return tok;
}
Razlomak &Razlomak::operator +=(const Razlomak &a) {
    *this = *this + a;
    return *this;
}
Razlomak &Razlomak::operator -=(const Razlomak &a) {
    *this = *this - a;
    return *this;
}
Razlomak &Razlomak::operator /=(const Razlomak &a) {
    *this = *this /a;
    return *this;
}
Razlomak &Razlomak::operator *=(const Razlomak &a) {
    *this = *this * a;
    return *this;
}
Razlomak operator /(const Razlomak &a, const Razlomak &b){
    if(b.brojnik == 0) throw std::logic_error("Dijeljenje sa nulom");
    long long int br, naz;
    if(Razlomak::PrekoracenoMnozenje(a.brojnik, b.nazivnik) || Razlomak::PrekoracenoMnozenje(a.nazivnik, b.brojnik))
        throw std::overflow_error("Nemoguce dobiti tacan rezultat");
    br = a.brojnik * b.nazivnik;
    naz = a.nazivnik * b.brojnik;
    return Razlomak(br, naz);
}
Razlomak operator *(const Razlomak &a, const Razlomak &b){
    long long int br, naz;
    if(Razlomak::PrekoracenoMnozenje(a.brojnik, b.brojnik) || Razlomak::PrekoracenoMnozenje(a.nazivnik, b.nazivnik))
        throw std::overflow_error("Nemoguce dobiti tacan rezultat");
    br = a.brojnik * b.brojnik;
    naz = a.nazivnik * b.nazivnik;
    return Razlomak(br, naz);
}
Razlomak operator +(const Razlomak &a, const Razlomak &b){
    long long int nzs, a_brojnik, b_brojnik;

    if(Razlomak::PrekoracenoMnozenje(a.nazivnik, b.nazivnik) || Razlomak::PrekoracenoMnozenje(a.brojnik, b.nazivnik) ||
    Razlomak::PrekoracenoMnozenje(b.brojnik, a.nazivnik) || Razlomak::PrekoracenoMnozenje(a.brojnik * b.nazivnik, b.brojnik * a.nazivnik))
        throw std::overflow_error("Nemoguce dobiti tacan rezultat");
    nzs = a.nazivnik * b.nazivnik;
    a_brojnik = a.brojnik * b.nazivnik;
    b_brojnik = a.nazivnik * b.brojnik;
    return Razlomak(a_brojnik + b_brojnik, nzs);
}
Razlomak operator -(const Razlomak &a, const Razlomak &b){
    long long int nzs, a_brojnik, b_brojnik;

    if(Razlomak::PrekoracenoMnozenje(a.nazivnik, b.nazivnik) || Razlomak::PrekoracenoMnozenje(a.brojnik, b.nazivnik) ||
    Razlomak::PrekoracenoMnozenje(b.brojnik, a.nazivnik) || Razlomak::PrekoracenoMnozenje(a.brojnik * b.nazivnik, b.brojnik * a.nazivnik))
        throw std::overflow_error("Nemoguce dobiti tacan rezultat");
    nzs = a.nazivnik * b.nazivnik;
    a_brojnik = a.brojnik * b.nazivnik;
    b_brojnik = a.nazivnik * b.brojnik;
    return Razlomak(a_brojnik - b_brojnik, nzs);
}

int main ()
{
    try{
        Razlomak a(3, 4);
        Razlomak b(2, 5);
        std::cout<<"Prvi razlomak: "<<a<<"\nDrugi razlomak: "<<b<<std::endl;
        Razlomak c = a + b;
        std::cout<<"A + B = "<<c<<"\n";
        Razlomak d = a - b;
        std::cout<<"A - B = "<<d<<"\n";
        Razlomak e = a * b;
        Razlomak f = a / b;
        std::cout<<"A * B = "<<e<<"\nA / B = "<<f;
        Razlomak g;
        std::cout<<"\nUnesite razlomak u formatu brojnik/nazivnik: ";
        std::cin>>g;
        std::cout<<g;
    }
    catch(const std::domain_error &e){
        std::cout<<"Izuzetak: "<<e.what()<<std::endl;
    }
    catch(const std::overflow_error &e){
        std::cout<<"Izuzetak: "<<e.what()<<std::endl;
    }
    catch(const std::logic_error &e){
        std::cout<<"Izuzetak: "<<e.what()<<std::endl;
    }


	return 0;
}
