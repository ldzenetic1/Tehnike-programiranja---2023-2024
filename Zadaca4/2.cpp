//TP 2023/2024: Zadaća 4, Zadatak 2
#include <iostream>
#include <cmath>
#include <string>
#include <type_traits>
#include <algorithm>
#include <iomanip>

class GradjaninBiH {
public:
    enum Pol{Musko, Zensko};
private:
    std::string ime_prezime;
    long long int JMBG;
    int dan, mjesec, godina, sifra, kod, k_cifra;
    Pol pol;
    static GradjaninBiH *posljednji;
    GradjaninBiH *prethodni;

    static bool IspravnostDatuma(int d, int m, int g){
        int dani[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        if((g % 4 == 0 && g % 100 != 0) || g % 400 == 0) dani[1]++;
        return g > 0 && m > 0 && m <=12 && d > 0 && d <=dani[m - 1];
    }
    void ValidanJMBG(long long int jmbg){
        int c[13];
        long long int temp = jmbg;
        for(int i = 12; i >= 0; --i){
            c[i] = temp % 10;
            temp  /= 10;
        }
        dan = c[0] * 10 + c[1];
        mjesec = c[2] * 10 + c[3];
        godina = c[4] * 10 + c[5] + 1000;
        if(godina < 2000) godina += 1000;
        else godina += 1900;
        sifra = c[7] * 10 + c[8];
        kod = c[9] * 100 + c[10] * 10 + c[11];
        k_cifra = c[12];
        if(!IspravnostDatuma(dan, mjesec, godina - 1000)) throw std::logic_error("JMBG nije validan");
        int k = 11 - (7 * (c[0] + c[6]) + 6 * (c[1] + c[7]) + 5 * (c[2] + c[8]) + 4 * (c[3] + c[9]) + 3 * (c[4] + c[10]) + 2 * (c[5] + c[11])) % 11;
        if(k == 11) k = 0;
        if(k == 10 || k != k_cifra) throw std::logic_error("JMBG nije validan");
    }
    static bool PostojiLiVec(long long int jmbg){
        for(GradjaninBiH *it = posljednji; it != nullptr; it = it->prethodni){
            if(it->JMBG == jmbg) return true;
        }
        return false;
    }
public:
    GradjaninBiH(std::string ime_prezime, long long int jmbg) : ime_prezime(ime_prezime), JMBG(jmbg){
        if(ime_prezime == "") throw std::logic_error("Ime ne moze biti prazno!");
        ValidanJMBG(jmbg);
        if(PostojiLiVec(jmbg)) throw std::logic_error("Vec postoji gradjanin sa istim JMBG");
        prethodni = posljednji;
        posljednji = this;
    }
    GradjaninBiH(std::string ime_prezime, int dan, int mjesec, int godina, int sifra, Pol pol) : ime_prezime(ime_prezime), dan(dan), mjesec(mjesec), godina(godina), sifra(sifra), pol(pol){
        if(ime_prezime == "") throw std::logic_error("Ime ne moze biti prazno!");
        if(!IspravnostDatuma(dan, mjesec, godina)) throw std::logic_error("Neispravni podaci");
        godina %= 1000;
        JMBG = dan * 1000000000000LL + mjesec * 10000000000LL + godina * 100000000LL + sifra * 1000000LL;
        kod = 0;
        for(int i = (pol == Musko ? 0 : 500); i < (pol == Musko ? 500 : 1000); i++){
            JMBG += i * 1000;
            int c[12];
            long long int temp = JMBG;
            for(int j = 11; j >= 0; --j){
                c[j] = temp % 10;
                temp *= 10;
            }
            int k = 11 - (7 * (c[0] + c[6]) + 6 * (c[1] + c[7]) + 5 * (c[2] + c[8]) + 4 * (c[3] + c[9]) + 3 * (c[4] + c[10]) + 2 * (c[5] + c[11])) % 11;
            if(k == 11) k = 0;
            if(k != 10){
                JMBG = JMBG * 10 + k;
                if(PostojiLiVec(JMBG)){
                    k_cifra = k;
                    break;
                }
            }
            JMBG /= 1000;
        }
        if(PostojiLiVec(JMBG)) throw std::logic_error("Nije moguce kreirati jedinstveni JMBG");
        prethodni = posljednji;
        posljednji = this;
    }
    ~GradjaninBiH(){
        if(this == posljednji) posljednji = prethodni;
        else{
            for(GradjaninBiH *it = posljednji; it != nullptr; it = it->prethodni){
                if(it->prethodni == this){
                    it->prethodni = prethodni;
                    break;
                }
            }
        }
    }
    GradjaninBiH(const GradjaninBiH &) = delete;
    GradjaninBiH &operator =(const GradjaninBiH &) = delete;
    std::string DajImeIPrezime() const {return ime_prezime;}
    long long int DajJMBG() const {return JMBG;}
    int DajDanRodjenja() const {return dan;}
    int DajMjesecRodjenja() const {return mjesec;}
    int DajGodinuRodjenja() const {return godina;}
    int DajSifruRegije() const {return sifra;}
    Pol DajPol() const {return pol;}
    void PromijeniImeIPrezime(std::string novo_ime){ 
        if(ime_prezime == "") throw std::logic_error("Ime ne moze biti prazno!");
        ime_prezime = novo_ime;}
};
GradjaninBiH *GradjaninBiH::posljednji = nullptr;

bool PorediDatume(const GradjaninBiH *g1, const GradjaninBiH *g2){
    if(g1->DajGodinuRodjenja() != g2->DajGodinuRodjenja())
        return g1->DajGodinuRodjenja() < g2->DajGodinuRodjenja();
    if(g1->DajGodinuRodjenja() == g2->DajGodinuRodjenja())
        return g1->DajMjesecRodjenja() < g2->DajMjesecRodjenja();
    return g1->DajDanRodjenja() < g2->DajDanRodjenja();
}
void UnesiPodatke(int n, GradjaninBiH **gradjani){
    std::string ime_i_prezime;
    int dan, mjesec, godina, sifra;
    for(int i = 0; i < n; i++){
        std::cout<<"Unesite podatke za "<<i+1<<". gradjanina:\n";
        std::string ime_i_p;
        std::cin.ignore(10000, '\n');
        std::cout<<"Ime i prezime: ";
        std::getline(std::cin, ime_i_p);
        std::cout<<"Datum rodjenja: ";
        std::cin>>dan>>mjesec>>godina;
        std::cout<<"Sifra regije: ";
        std::cin>>sifra;
        std::cout<<"Pol ( 1-Musko, 2-Zensko ): ";
        GradjaninBiH::Pol pol;
        int izbor;
        std::cin>>izbor;
        if(izbor == 1) pol = GradjaninBiH::Pol::Musko;
        else pol = GradjaninBiH::Pol::Zensko;
        try{
            gradjani[i] = new GradjaninBiH(ime_i_prezime, dan, mjesec, godina, sifra, pol);
            break;
        }catch(const std::logic_error &e){
            std::cout<<e.what()<<" Molimo ponovite unos.\n";
            i--;
        }
    }
}
void IspisiGradjane(GradjaninBiH **gradjani, int n){
    std::cout<<"Gradjani sortirani po starosti:\n";
    for(int i = 0; i < n; i++){
        std::cout<<gradjani[i]->DajImeIPrezime()<<" "<<gradjani[i]->DajDanRodjenja()<<"."<<
        gradjani[i]->DajMjesecRodjenja()<<"."<<gradjani[i]->DajGodinuRodjenja()<<" "<<"JMBG: "<<gradjani[i]->DajJMBG()<<"\n";
    }
}
int main()
{
    int n;
    std::cout<<"Unesite broj gradjana:\n";
    std::cin>>n;
    GradjaninBiH ** gradjani{};
    try{
        gradjani = new GradjaninBiH*[n]{};
        UnesiPodatke(n, gradjani);
        std::sort(gradjani, gradjani + n, PorediDatume);
        IspisiGradjane(gradjani, n);
    }
    catch(std::exception &e){
        std::cout<<"Izuzetak: "<<e.what()<<std::endl;
    }
    for(int i = 0; i < n; i++){
        delete gradjani[i];
    }
    delete [] gradjani;

    return 0;
}
