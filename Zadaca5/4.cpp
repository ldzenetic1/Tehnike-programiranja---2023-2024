// TP 2023/2024: Zadaća 5, Zadatak 4
#include <algorithm>
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

class Spremnik {
protected:
  double tezina;
  std::string naziv;

public:
  Spremnik(double tezina, const std::string &naziv)
      : tezina(tezina), naziv(naziv) {}
  virtual ~Spremnik() {}
  double DajTezinu() const { return tezina; }
  virtual double DajUkupnuTezinu() const = 0;
  virtual Spremnik *DajKopiju() const = 0;
  virtual void Ispisi() const = 0;
};

class Sanduk : public Spremnik {
  std::vector<double> tezine_predmeta;

public:
  Sanduk(double tezina, const std::string &naziv,
         const std::vector<double> &tezine_predmeta)
      : Spremnik(tezina, naziv), tezine_predmeta(tezine_predmeta) {}
  double DajUkupnuTezinu() const override {
    double ukupna_tezina = tezina;
    for (double t : tezine_predmeta) {
      ukupna_tezina += t;
    }
    return ukupna_tezina;
  }
  void Ispisi() const override {
    std::cout << "Vrsta spremnika: Sanduk" << std::endl;
    std::cout << "Sadrzaj: " << naziv << std::endl;
    std::cout << "Tezine predmeta: ";
    for (double t : tezine_predmeta)
      std::cout << t << " ";
    std::cout << "(kg)" << std::endl;
    std::cout << "Vlastita tezina: " << tezina << " (kg)" << std::endl;
    std::cout << "Ukupna tezina: " << DajUkupnuTezinu() << " (kg)" << std::endl;
  }
  virtual Spremnik *DajKopiju() const override { return new Sanduk(*this); }
};

class Vreca : public Spremnik {
  double tezina_materije;

public:
  Vreca(double tezina, const std::string &naziv, double tezina_materije)
      : Spremnik(tezina, naziv), tezina_materije(tezina_materije) {}
  double DajUkupnuTezinu() const override { return tezina + tezina_materije; }
  void Ispisi() const override {
    std::cout << "Vrsta spremnika: Vreca" << std::endl;
    std::cout << "Sadrzaj: " << naziv << std::endl;
    std::cout << "Vlastita tezina: " << tezina << " (kg)" << std::endl;
    std::cout << "Tezina pohranjene materije: " << tezina_materije << " (kg)"
              << std::endl;
    std::cout << "Ukupna tezina: " << DajUkupnuTezinu() << " (kg)" << std::endl;
  }
  virtual Spremnik *DajKopiju() const override { return new Vreca(*this); }
};

class Bure : public Spremnik {
  double gustina, zapremina;

public:
  Bure(double tezina, const std::string &naziv, double gustina,
       double zapremina)
      : Spremnik(tezina, naziv), gustina(gustina), zapremina(zapremina) {}
  double DajUkupnuTezinu() const override {
    return tezina + gustina * zapremina * 0.001;
  }
  void Ispisi() const override {
    std::cout << "Vrsta spremnika: Bure" << std::endl;
    std::cout << "Sadrzaj: " << naziv << std::endl;
    std::cout << "Vlastita tezina: " << tezina << " (kg)" << std::endl;
    std::cout << "Specificna tezina tecnosti: " << gustina << " (kg/m^3)"
              << std::endl;
    std::cout << "Zapremina tecnosti: " << zapremina << " (l)" << std::endl;
    std::cout << "Ukupna tezina: " << DajUkupnuTezinu() << " (kg)" << std::endl;
  }
  virtual Spremnik *DajKopiju() const override { return new Bure(*this); }
};

class PolimorfniSpremnik {
  Spremnik *spremnik;

public:
  PolimorfniSpremnik() : spremnik(nullptr) {}
  PolimorfniSpremnik(const Spremnik &vrsta) : spremnik(vrsta.DajKopiju()) {}
    PolimorfniSpremnik(const PolimorfniSpremnik &s) : spremnik(s.spremnik ? s.spremnik->DajKopiju() : nullptr) {}
    PolimorfniSpremnik(PolimorfniSpremnik &&s) noexcept : spremnik(s.spremnik) {s.spremnik = nullptr;}

  ~PolimorfniSpremnik() {
    delete spremnik;
    spremnik = nullptr;
  }
  PolimorfniSpremnik &operator =(const PolimorfniSpremnik &s){
      if(this != &s){
          Spremnik *temp = s.spremnik ? s.spremnik->DajKopiju() : nullptr;
          delete spremnik;
          spremnik = temp;
      }
      return *this;
  }
  PolimorfniSpremnik &operator =(PolimorfniSpremnik &&s) noexcept{
      if(this != &s){
          delete spremnik;
          spremnik = s.spremnik;
          s.spremnik = nullptr;
      }
      return *this;
  }
  double DajTezinu() const {
    if (!spremnik) {
      throw std::logic_error("Nespecificiran spremnik");
    }
    return spremnik->DajTezinu();
  }
  double DajUkupnuTezinu() const {
    if (!spremnik) {
      throw std::logic_error("Nespecificiran spremnik");
    }
    return spremnik->DajUkupnuTezinu();
  }
  void Ispisi() const {
    if (!spremnik) {
      throw std::logic_error("Nespecificiran spremnik");
    }
    spremnik->Ispisi();
  }
};
int main() { 
    
    
    return 0; 
}
