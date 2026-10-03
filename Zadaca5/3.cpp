//TP 2023/2024: Zadaća 5, Zadatak 3
#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <algorithm>

class Spremnik{
protected:
    double tezina;
    std::string naziv;
public: 
    Spremnik(double tezina, const std::string &naziv) : tezina(tezina), naziv(naziv){}
    virtual ~Spremnik() {}
    double DajTezinu() const {return tezina;}
    virtual double DajUkupnuTezinu() const = 0;
    virtual Spremnik *DajKopiju() const = 0;
    virtual void Ispisi() const = 0;
};

class Sanduk : public Spremnik{
    std::vector<double> tezine_predmeta;
public:
    Sanduk(double tezina, const std::string &naziv, const std::vector<double> &tezine_predmeta) : Spremnik(tezina, naziv), tezine_predmeta(tezine_predmeta) {}
    double DajUkupnuTezinu() const override{
        double ukupna_tezina = tezina;
        for(double t : tezine_predmeta){
            ukupna_tezina += t;
        }
        return ukupna_tezina;
    }
    void Ispisi() const override{
        std::cout<<"Vrsta spremnika: Sanduk"<<std::endl;
        std::cout<<"Sadrzaj: "<<naziv<<std::endl;
        std::cout<<"Tezine predmeta: ";
        for(double t : tezine_predmeta)
            std::cout<<t<<" ";
        std::cout<<"(kg)"<<std::endl;
        std::cout<<"Vlastita tezina: "<<tezina<<" (kg)"<<std::endl;
        std::cout<<"Ukupna tezina: "<<DajUkupnuTezinu()<<" (kg)"<<std::endl;
    } 
    virtual Spremnik *DajKopiju() const override {return new Sanduk(*this);}
};

class Vreca : public Spremnik{
    double tezina_materije;
public:
    Vreca(double tezina, const std::string &naziv, double tezina_materije) : Spremnik(tezina, naziv), tezina_materije(tezina_materije) {}
    double DajUkupnuTezinu() const override{
    return tezina + tezina_materije;
    }
    void Ispisi()const override{
        std::cout<<"Vrsta spremnika: Vreca"<<std::endl;
        std::cout<<"Sadrzaj: "<<naziv<<std::endl;
        std::cout<<"Vlastita tezina: "<<tezina<<" (kg)"<<std::endl;
        std::cout<<"Tezina pohranjene materije: "<<tezina_materije<<" (kg)"<<std::endl;
        std::cout<<"Ukupna tezina: "<<DajUkupnuTezinu()<<" (kg)"<<std::endl; 
    }
    virtual Spremnik *DajKopiju() const override {return new Vreca(*this);}
};

class Bure : public Spremnik{
    double gustina, zapremina;
public:
    Bure(double tezina, const std::string &naziv, double gustina, double zapremina) : Spremnik(tezina, naziv), gustina(gustina), zapremina(zapremina) {}
    double DajUkupnuTezinu() const override{
        return tezina + gustina * zapremina * 0.001;
    }
    void Ispisi() const override{
        std::cout<<"Vrsta spremnika: Bure"<<std::endl;
        std::cout<<"Sadrzaj: "<<naziv<<std::endl;
        std::cout<<"Vlastita tezina: "<<tezina<<" (kg)"<<std::endl;
        std::cout<<"Specificna tezina tecnosti: "<<gustina<<" (kg/m^3)"<<std::endl;
        std::cout<<"Zapremina tecnosti: "<<zapremina<<" (l)"<<std::endl;
        std::cout<<"Ukupna tezina: "<<DajUkupnuTezinu()<<" (kg)"<<std::endl;
    }
    virtual Spremnik * DajKopiju() const override{return new Bure(*this);}
};
class Skladiste{
    std::vector<std::shared_ptr<Spremnik>> spremnici;
public:
    Skladiste() = default;
    Skladiste(const Skladiste &s){
        for(const auto &spremnik : s.spremnici){
            spremnici.push_back(std::shared_ptr<Spremnik>(spremnik->DajKopiju()));
        }
    }
    Skladiste &operator =(const Skladiste &s){
        if(this == &s) return *this;
        spremnici.clear();
        for(const auto &spremnik : s.spremnici){
            spremnici.push_back(std::shared_ptr<Spremnik>(spremnik->DajKopiju()));
        }
        return *this;
    }
    Spremnik *DodajSanduk(double tezina, const std::string &naziv, const std::vector<double> &tezine_predmeta){
        auto sanduk = std::make_shared<Sanduk>(tezina, naziv, tezine_predmeta);
        spremnici.push_back(sanduk);
        return sanduk.get();
    }
    Spremnik *DodajVrecu(double tezina, const std::string &naziv, double tezina_materije){
        auto vreca = std::make_shared<Vreca>(tezina, naziv, tezina_materije);
        spremnici.push_back(vreca);
        return vreca.get();
    }
    Spremnik *DodajBure(double tezina, const std::string &naziv, double gustina, double zapremina){
        auto bure = std::make_shared<Bure>(tezina, naziv, gustina, zapremina);
        spremnici.push_back(bure);
        return bure.get();
    }
    Spremnik *DodajSpremnik(Spremnik *spremnik, bool vlasnistvo){
        if(vlasnistvo){
            spremnici.push_back(std::shared_ptr<Spremnik>(spremnik));
            return spremnik;
        }
        else{
            Spremnik *kopija = spremnik->DajKopiju();
            spremnici.push_back(std::shared_ptr<Spremnik>(kopija));
            return kopija;
        }
    }
    void BrisiSpremnik(Spremnik *spremnik){
        auto it = std::find_if(spremnici.begin(), spremnici.end(), [spremnik](const std::shared_ptr<Spremnik> &ptr) {return ptr.get() == spremnik;});
        if(it != spremnici.end()){
            spremnici.erase(it);
        }
        else{
            std::cout<<"Spremnik nije pronadjen."<<std::endl;
        }
    }
    void Ispisi() const{
        for(const auto &spremnik : spremnici){
            spremnik->Ispisi();
        }
    }
    
    const Spremnik &DajNajtezi(){
        if(spremnici.empty()) throw std::range_error("Skladiste je prazno");
        auto it = std::max_element(spremnici.begin(), spremnici.end(), [](const std::shared_ptr<Spremnik> &a, const std::shared_ptr<Spremnik> &b){
            return a->DajTezinu() < b->DajTezinu();
        });
        return *(*it);
    }
    Spremnik &DajNajlaksi(){
        if(spremnici.empty()) throw std::range_error("Skladiste je prazno");
        auto it = std::min_element(spremnici.begin(), spremnici.end(), [](const std::shared_ptr<Spremnik> &a, const std::shared_ptr<Spremnik> &b){
            return a->DajTezinu() < b->DajTezinu();
        });
        return *(*it);
    }
    int BrojPreteskih(double mjerna_tezina) const{
        int brojac = 0;
        for(const auto &spremnik : spremnici){
            if(spremnik->DajUkupnuTezinu() >= mjerna_tezina) brojac++;
        }
        return brojac;
    }
    void IzlistajSkladiste() const{
        std::vector<std::shared_ptr<Spremnik>> temp = spremnici;
        std::sort(temp.begin(), temp.end(), [](const std::shared_ptr<Spremnik> &a, const std::shared_ptr<Spremnik> &b){
            return a->DajUkupnuTezinu() > b->DajUkupnuTezinu();
        });
        for(const auto &spremnik : temp){
            spremnik->Ispisi();
        }
    }
    void UcitajIzDatoteke(const std::string &naziv){
        std::ifstream file(naziv);
        if(!file) throw std::logic_error("Trazena datoteka ne postoji");
        spremnici.clear();
        std::string s;
        while(std::getline(file, s)){
            try{
                char c = s[0];
                std::string naziv = s.substr(2);
                if(c == 'S'){
                    double tezina;
                    int broj_predmeta;
                    file>>tezina>>broj_predmeta;
                    std::vector<double> tezine_predmeta(broj_predmeta);
                    for(int i = 0; i < broj_predmeta; i++)
                        file>>tezine_predmeta[i];
                    file.ignore(10000, '\n');
                    spremnici.push_back(std::make_shared<Sanduk>(tezina, naziv,  tezine_predmeta));
                }
                else if(c == 'V'){
                    double tezina, tezina_materije;
                    file>>tezina>>tezina_materije;
                    file.ignore(10000, '\n');
                    spremnici.push_back(std::make_shared<Vreca>(tezina, naziv, tezina_materije));
                }
                else if(c == 'B'){
                    double tezina, specificna, zapremina;
                    file>>tezina>>specificna>>zapremina;
                    file.ignore(10000, '\n');
                    spremnici.push_back(std::make_shared<Bure>(tezina, naziv, specificna, zapremina));
                }
                else{
                    throw std::logic_error("Datoteka sadrzi besmislene podatke");
                }
            }
            catch(const std::exception &e){
                throw std::logic_error("Datoteka sadrzi besmislene podatke");
            }
            if(file.fail() && !file.eof())
                throw std::logic_error("Datoteka sadrzi besmislene podatke");
        }
        
    }
};

int main(){

    try{
        Skladiste s;
        s.UcitajIzDatoteke("ROBA.TXT");
        s.IzlistajSkladiste();
    }
    catch(const std::exception &e){
        std::cout<<e.what()<<std::endl;
    }

    return 0;
}

