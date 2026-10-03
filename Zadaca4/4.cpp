//TP 2023/2024: Zadaća 4, Zadatak 4
#include <algorithm>
#include <cmath>
#include <initializer_list>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>
#include <tuple>
#include <utility>
#include <vector>
#include <memory>

class Datum {
  int dan, mjesec, godina;

public:
  Datum() : dan(1), mjesec(1), godina(2023) {}
  Datum(int d, int m, int g) { Postavi(d, m, g); };
  void Postavi(int d, int m, int g) {
    int broj_dana[12]{31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (g % 4 == 0 && g % 100 != 0 || g % 400 == 0)
      broj_dana[1]++;
    if (g < 1 || d < 1 || m < 1 || m > 12 || d > broj_dana[m - 1])
      throw std::domain_error("Neispravan datum");
    dan = d;
    mjesec = m;
    godina = g;
  }
  std::tuple<int, int, int> Ocitaj() const {
    return std::make_tuple(dan, mjesec, godina);
  }
  void Ispisi() const { std::cout << dan << "/" << mjesec << "/" << godina; }
  void PomjeriDanNaprijed() {
    int broj_dana[12]{31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (godina % 4 == 0 && godina % 100 != 0 || godina % 400 == 0)
      broj_dana[1]++;
    dan++;
    if (dan > broj_dana[mjesec - 1]) {
      dan = 1;
      mjesec++;
      if (mjesec > 12) {
        mjesec = 1;
        godina++;
      }
    }
  }
  void PomjeriDanNazad() {
    int broj_dana[12]{31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (godina % 4 == 0 && godina % 100 != 0 || godina % 400 == 0)
      broj_dana[1]++;
    dan--;
    if (dan < 1) {
      mjesec--;
      if (mjesec < 1) {
        mjesec = 12;
        godina--;
      }
      dan = broj_dana[mjesec - 1];
    }
  }
  friend bool DatumPrije(const Datum &d1, const Datum &d2) {
    if ((d1.godina < d2.godina) || (d1.godina == d2.godina && d1.mjesec < d2.mjesec) 
    || (d1.godina == d2.godina && d1.mjesec == d2.mjesec && d1.dan < d2.dan ) )
      return true;
    return false;
  }
  friend bool JednakiDatumi(const Datum &d1, const Datum &d2) {
    return (d1.dan == d2.dan && d1.mjesec == d2.mjesec &&
            d1.godina == d2.godina);
  }
};

class Vrijeme {
  int sati, minute;

public:
  Vrijeme() { sati = minute = 0; }
  Vrijeme(int h, int min) { Postavi(h, min); }
  void Postavi(int h, int min) {
    if (h < 0 || h > 23 || min < 0 || min > 59)
      throw std::domain_error("Neispravno vrijeme");
    sati = h;
    minute = min;
  }
  void Ispisi() const {
    if (sati < 10)
      std::cout << "0";
    std::cout << sati << ":";
    if (minute < 10)
      std::cout << "0";
    std::cout << minute;
  }
  std::pair<int, int> Ocitaj() const { return std::make_pair(sati, minute); }
  friend bool VrijemePrije(const Vrijeme &v1, const Vrijeme &v2) {
    if (v1.sati < v2.sati || (v1.sati == v2.sati && v1.minute < v2.minute))
      return true;
    return false;
  }
};

class Pregled {
  std::string ime;
  Datum dat_pregleda;
  Vrijeme vrijeme_pregleda;

public:
  Pregled(std::string ime, Datum dat, Vrijeme vrijeme)
      : ime(ime), dat_pregleda(dat), vrijeme_pregleda(vrijeme) {}
  Pregled(std::string ime, int d, int m, int g, int h, int min)
      : ime(ime), dat_pregleda(Datum(d, m, g)),
        vrijeme_pregleda(Vrijeme(h, min)) {}
    Pregled() : ime(""), dat_pregleda(), vrijeme_pregleda() {}
  std::string DajImePacijenta() const { return ime; }
  Pregled &PromijeniPacijenta(const std::string &novo_ime) {
    ime = novo_ime;
    return *this;
  }
  Pregled &PromijeniDatum(const Datum &novi_datum) {
    dat_pregleda = novi_datum;
    return *this;
  }
  Pregled &PromijeniVrijeme(const Vrijeme &novo_vrijeme) {
    vrijeme_pregleda = novo_vrijeme;
    return *this;
  }
  void PomjeriDanUnaprijed() { dat_pregleda.PomjeriDanNaprijed(); }
  void PomjeriDanUnazad() { dat_pregleda.PomjeriDanNazad(); }
  Datum DajDatumPregleda() const { return dat_pregleda; }
  Vrijeme DajVrijemePregleda() const { return vrijeme_pregleda; }
  static bool DolaziPrije(const std::shared_ptr<Pregled> &p1, const std::shared_ptr<Pregled> &p2) {
    Datum d1 = p1->DajDatumPregleda();
    Datum d2 = p2->DajDatumPregleda();
    Vrijeme v1 = p1->DajVrijemePregleda();
    Vrijeme v2 = p2->DajVrijemePregleda();
    if (DatumPrije(d1, d2) || (JednakiDatumi(d1, d2) && VrijemePrije(v1, v2)))
      return true;
    return false;
  }
  void Ispisi() const {
    std::cout << std::left << std::setw(30) << ime << std::right;
    dat_pregleda.Ispisi();
    std::cout << " ";
    vrijeme_pregleda.Ispisi();
    std::cout << std::endl;
  }
};
class Pregledi{
    std::vector<std::shared_ptr<Pregled>> pregledi;
public:
    Pregledi() = default;
    Pregledi(std::initializer_list<Pregled> lista_pregleda);
    Pregledi(const Pregledi &p);
    Pregledi(Pregledi &&p) = default;
    Pregledi &operator =(const Pregledi &p);
    Pregledi &operator =(Pregledi &&p) = default;
    void RegistrirajPregled(const std::string &ime, const Datum &datum, const Vrijeme &vrijeme);
    void RegistrirajPregled(const std::string &ime, int dan, int mjesec, int godina, int sati, int minute);
    void RegistrirajPregled(std::shared_ptr<Pregled> p);
    int DajBrojPregleda() const{ return pregledi.size();};
    int DajBrojPregledaNaDatum(const Datum &d) const;
    Pregled &DajNajranijiPregled() ;
    Pregled DajNajranijiPregled() const ;
    void IsprazniKolekciju() { pregledi.clear();}
    void ObrisiNajranijiPregled();
    void ObrisiPregledePacijenta(const std::string &ime);
    void IspisiPregledeNaDatum(const Datum &d) const;
    void IspisiSvePreglede() const;

};
Pregledi::Pregledi(std::initializer_list<Pregled> lista_pregleda) : pregledi(lista_pregleda.size()){
    for(int i = 0; i < lista_pregleda.size(); i++)
        pregledi[i] = std::make_shared<Pregled>(lista_pregleda.begin()[i]);
}
Pregledi::Pregledi(const Pregledi &p) : pregledi(p.pregledi.size()){
    for(int i = 0; i < pregledi.size(); i++){
        pregledi[i] = std::make_shared<Pregled>(*p.pregledi[i]);
    }
}
Pregledi &Pregledi::operator =(const Pregledi &p){
    int stara_vel = pregledi.size();
    pregledi.resize(p.pregledi.size());
    if(pregledi.size() > stara_vel){
        for(int i = stara_vel; i < pregledi.size(); i++)
            pregledi[i] = std::make_shared<Pregled>(*p.pregledi[i]);
        for(int i = 0; i < stara_vel; i++) *pregledi[i] = *p.pregledi[i];
    }
    else{
        for(int i = 0; i < pregledi.size(); i++) *pregledi[i] = *p.pregledi[i];
    }
    return *this;
}
void Pregledi::RegistrirajPregled(const std::string &ime, const Datum &datum, const Vrijeme &vrijeme){
    pregledi.push_back(std::make_shared<Pregled>(ime, datum, vrijeme));
}
void Pregledi::RegistrirajPregled(const std::string &ime, int dan, int mjesec, int godina, int sati, int minute){
    pregledi.push_back(std::make_shared<Pregled>(ime, dan, mjesec, godina, sati, minute));
}
void Pregledi::RegistrirajPregled(std::shared_ptr<Pregled> p){
    pregledi.push_back(p);
}
int Pregledi::DajBrojPregledaNaDatum(const Datum &d) const{
    int broj_pregleda = 0;
    for(const auto &pregled : pregledi){
        if(JednakiDatumi(pregled->DajDatumPregleda() ,d))
            broj_pregleda++;
    }
    return broj_pregleda;
}
Pregled &Pregledi::DajNajranijiPregled() {
    if(pregledi.size() == 0) throw std::domain_error("Nema registriranih pregleda");
    return **std::min_element(pregledi.begin(), pregledi.end(), [](const std::shared_ptr<Pregled> &a, const std::shared_ptr<Pregled> &b){
        return Pregled::DolaziPrije(a, b);
    });
}
Pregled Pregledi::DajNajranijiPregled() const {
    if(pregledi.size() == 0) throw std::domain_error("Nema registriranih pregleda");
    return **std::min_element(pregledi.begin(), pregledi.end(), [](const std::shared_ptr<Pregled> &a, const std::shared_ptr<Pregled> &b){
        return Pregled::DolaziPrije(a, b);
    });
}
void Pregledi::ObrisiNajranijiPregled(){
    if(pregledi.size() == 0) throw std::range_error("Prazna kolekcija");
    auto najraniji = std::min_element(pregledi.begin(), pregledi.end(), [](const std::shared_ptr<Pregled> &a, const std::shared_ptr<Pregled> &b){
        return Pregled::DolaziPrije(a, b);});
    pregledi.erase(najraniji);
}
void Pregledi::ObrisiPregledePacijenta(const std::string &ime){
    if(pregledi.size() == 0) throw std::range_error("Prazna kolekcija");
    pregledi.erase(std::remove_if(pregledi.begin(), pregledi.end(), [&ime](const std::shared_ptr<Pregled> &pregled){
        return pregled->DajImePacijenta() == ime;}), pregledi.end());
}
void Pregledi::IspisiPregledeNaDatum(const Datum &d) const{
    std::for_each(pregledi.begin(), pregledi.end(), [&d](const std::shared_ptr<Pregled> &pregled){
        if(JednakiDatumi(pregled->DajDatumPregleda(), d))
            pregled->Ispisi();
    });
}
void Pregledi::IspisiSvePreglede() const{
    std::vector<std::shared_ptr<Pregled>> sortirano = pregledi;
    std::sort(sortirano.begin(), sortirano.end(), [](const std::shared_ptr<Pregled> &p1, const std::shared_ptr<Pregled> &p2){
        return Pregled::DolaziPrije(p1, p2);
    });
    std::for_each(sortirano.begin(), sortirano.end(), [](const std::shared_ptr<Pregled> &pregled){
        pregled->Ispisi();
    });
}
int main ()
{
    Pregledi pregledi;
    int izbor;
  do {
    std::cout << "1. Registriraj Pregled\n"
              << "2. Daj Broj Pregleda\n"
              << "3. Daj Broj Pregleda Na Datum\n"
              << "4. Daj Najraniji Pregled\n"
              << "5. Obrisi Najraniji Pregled\n"
              << "6. Obrisi Preglede Pacijenta\n"
              << "7. Ispisi Preglede Na Datum\n"
              << "8. Ispisi Sve Preglede\n"
              << "9. Isprazni Kolekciju\n"
              << "10. Izlaz\n";
    std::cout << "Unesite izbor: ";
    std::cin >> izbor;
    if(izbor < 1 || izbor > 10){
        std::cout<<"Greska";
        return 0;
    }
    if (izbor == 10) {
      std::cout << "Kraj programa.";
      return 0;
    }
    if (izbor == 1) {
      std::string ime;
      int d, m, g, h, min;
      std::cin.ignore(10000, '\n');
      std::cout << "Unesite ime pacijenta: ";
      std::getline(std::cin, ime);
      std::cout << "Unesite datum i vrijeme pregleda (dan mjesec godina sati "
                   "minute): ";
      std::cin >> d >> m >> g >> h >> min;
      try {
        pregledi.RegistrirajPregled(ime, d, m, g, h, min);
      } catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
      }
    } else if (izbor == 2) {
      std::cout << "Ukupan broj pregleda: " << pregledi.DajBrojPregleda()
                << std::endl;
    } else if (izbor == 3) {
      int d, m, g;
      std::cout << "Unesite datum (dan mjesec godina): ";
      std::cin >> d >> m >> g;
      Datum datum(d, m, g);
      try {
        int broj_pregleda_na_dan = pregledi.DajBrojPregledaNaDatum(datum);
        std::cout << "Broj pregleda na datum: "<< broj_pregleda_na_dan << std::endl;
      } catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
      }
    } else if (izbor == 4) {
      try {
        std::cout << "Najraniji pregled: ";
        pregledi.DajNajranijiPregled().Ispisi();
        std::cout << std::endl;
      } catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
      }
    } else if (izbor == 5) {
      try {
        pregledi.ObrisiNajranijiPregled();
        std::cout << "Najraniji pregled je obrisan.\n";
      } catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
      }
    } else if (izbor == 6) {
      std::string ime;
      std::cin.ignore(10000, '\n');
      std::cout << "Unesite ime pacijenta: ";
      std::getline(std::cin, ime);
      try {
        pregledi.ObrisiPregledePacijenta(ime);
        std::cout << "Pregledi za pacijenta " << ime << " su obrisani.\n";
      } catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
      }
    } else if (izbor == 7) {
      int d, m, g;
      std::cout << "Unesite datum: ";
      std::cin >> d >> m >> g;
      Datum datum(d, m, g);
      try {
        pregledi.IspisiPregledeNaDatum(datum);
      } catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
      }
    } else if (izbor == 8) {
      try {
        std::cout << "Svi pregledi: \n";
        pregledi.IspisiSvePreglede();
      } catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
      }
    } else if (izbor == 9) {
      try {
        pregledi.IsprazniKolekciju();
        std::cout << "Kolekcija ispraznjena.\n";
      } catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
      }
    }
  } while (izbor != 10);

	return 0;
}
