// TP 2023/2024: Zadaća 4, Zadatak 3
#include <algorithm>
#include <cmath>
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
  static bool DolaziPrije(const Pregled &p1, const Pregled &p2) {
    Datum d1 = p1.DajDatumPregleda();
    Datum d2 = p2.DajDatumPregleda();
    Vrijeme v1 = p1.DajVrijemePregleda();
    Vrijeme v2 = p2.DajVrijemePregleda();
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
class Pregledi {
  int broj_pregleda = 0;
  const int max_br_pregleda;
  Pregled **pregledi{};
  void Dealociraj();

public:
  explicit Pregledi(int max_pregled)
      : broj_pregleda(0), max_br_pregleda(max_pregled),
        pregledi(new Pregled *[max_pregled] {}) {}
  Pregledi(std::initializer_list<Pregled> lista_pregleda);
  Pregledi() : broj_pregleda(0), max_br_pregleda(100), pregledi(new Pregled*[100]{}) {}
  ~Pregledi() { Dealociraj(); }
  Pregledi(const Pregledi &p);
  Pregledi(Pregledi &&p) noexcept;
  Pregledi &operator=(const Pregledi &p);
  Pregledi &operator=(Pregledi &&p) noexcept;
  void RegistrirajPregled(const std::string &ime, const Datum &datum,
                          const Vrijeme &vrijeme);
  void RegistrirajPregled(const std::string &ime, int dan, int mjesec,
                          int godina, int sati, int minute);
  void RegistrirajPregled(Pregled *pregled);
  int DajBrojPregleda() const { return broj_pregleda; }
  int DajBrojPregledaNaDatum(const Datum &d) const{
    return std::count_if(pregledi, pregledi + broj_pregleda,
                         [&d](Pregled *pregled) {
                           return JednakiDatumi(pregled->DajDatumPregleda(), d);
                         });
  }
  Pregled &DajNajranijiPregled() {
    if (broj_pregleda == 0)
      throw std::domain_error("Nema registriranih pregleda");
    return **std::min_element(pregledi, pregledi + broj_pregleda,
                              [](Pregled *p1, Pregled *p2) {
                                return Pregled::DolaziPrije(*p1, *p2);
                              });
  }
  Pregled DajNajranijiPregled() const {
    if (broj_pregleda == 0)
      throw std::domain_error("Nema registriranih pregleda");
    return **std::min_element(pregledi, pregledi + broj_pregleda,
                              [](Pregled *p1, Pregled *p2) {
                                return Pregled::DolaziPrije(*p1, *p2);
                              });
  }
  void IsprazniKolekciju() {
    for (int i = 0; i < broj_pregleda; i++) {
      delete pregledi[i];
    }
    broj_pregleda = 0;
  }
  void ObrisiNajranijiPregled();
  void ObrisiPregledePacijenta(const std::string &ime);
  void IspisiPregledeNaDatum(const Datum &d) const;
  void IspisiSvePreglede() const;
};
void Pregledi::ObrisiNajranijiPregled() {
  if (broj_pregleda == 0)
    throw std::range_error("Prazna kolekcija");
  int prvi_indeks = 0;
  for (int i = 1; i < broj_pregleda; i++) {
    if (Pregled::DolaziPrije(*pregledi[i], *pregledi[prvi_indeks])) {
      prvi_indeks = i;
    }
  }
  delete pregledi[prvi_indeks];
  for (int i = prvi_indeks + 1; i < broj_pregleda; i++)
    pregledi[i - 1] = pregledi[i];
  broj_pregleda--;
}
void Pregledi::ObrisiPregledePacijenta(const std::string &ime) {
  for (int i = 0; i < broj_pregleda;) {
    if (pregledi[i]->DajImePacijenta() == ime) {
      delete pregledi[i];
      for (int j = i; j < broj_pregleda - 1; j++)
        pregledi[j] = pregledi[j + 1];
      broj_pregleda--;
      pregledi[broj_pregleda] = nullptr;
    } else {
      i++;
    }
  }
}
Pregledi::Pregledi(std::initializer_list<Pregled> lista_pregleda)
    : broj_pregleda(lista_pregleda.size()),
      max_br_pregleda(lista_pregleda.size()),
      pregledi(new Pregled *[lista_pregleda.size()] {}) {
  try {
    int i = 0;
    for (const Pregled &pregled : lista_pregleda)
      pregledi[i++] = new Pregled(pregled);
  } catch (...) {
    Dealociraj();
    throw;
  }
}
void Pregledi::Dealociraj() {
  for (int i = 0; i < broj_pregleda; i++)
    delete pregledi[i];
  delete[] pregledi;
  pregledi = {};
  broj_pregleda = 0;
}
Pregledi::Pregledi(const Pregledi &p)
    : broj_pregleda(p.broj_pregleda), max_br_pregleda(p.max_br_pregleda),
      pregledi(new Pregled *[p.max_br_pregleda] {}) {
  try {
    for (int i = 0; i < broj_pregleda; i++)
      pregledi[i] = new Pregled(*p.pregledi[i]);
  } catch (...) {
    Dealociraj();
    throw;
  }
}
Pregledi::Pregledi(Pregledi &&p) noexcept
    : broj_pregleda(p.broj_pregleda), max_br_pregleda(p.max_br_pregleda),
      pregledi(p.pregledi) {
  p.broj_pregleda = 0;
  p.pregledi = nullptr;
}
Pregledi &Pregledi::operator=(const Pregledi &p) {
  if (p.max_br_pregleda != max_br_pregleda)
    throw std::logic_error("Nesaglasan kapacitet");
  if (p.broj_pregleda > broj_pregleda) {
    try {
      for (int i = broj_pregleda; i < p.broj_pregleda; i++)
        pregledi[i] = new Pregled(*p.pregledi[i]);
      for (int i = 0; i < broj_pregleda; i++)
        *pregledi[i] = *p.pregledi[i];
    } catch (...) {
      for (int i = broj_pregleda; i < p.broj_pregleda; i++) {
        delete pregledi[i];
        pregledi[i] = nullptr;
      }
      throw;
    }
  } else {
    for (int i = p.broj_pregleda; i < broj_pregleda; i++) {
      delete pregledi[i];
      pregledi[i] = nullptr;
    }
    for (int i = 0; i < p.broj_pregleda; i++)
      *pregledi[i] = *p.pregledi[i];
  }
  broj_pregleda = p.broj_pregleda;
  return *this;
}
Pregledi &Pregledi::operator=(Pregledi &&p) noexcept {
  std::swap(broj_pregleda, p.broj_pregleda);
  std::swap(pregledi, p.pregledi);
  return *this;
}
void Pregledi::RegistrirajPregled(const std::string &ime, const Datum &datum,
                                  const Vrijeme &vrijeme) {
  if (broj_pregleda >= max_br_pregleda)
    throw std::range_error("Dostignut maksimalni broj pregleda");
  pregledi[broj_pregleda++] = new Pregled(ime, datum, vrijeme);
}
void Pregledi::RegistrirajPregled(const std::string &ime, int dan, int mjesec,
                                  int godina, int sati, int minute) {
  if (broj_pregleda >= max_br_pregleda)
    throw std::range_error("Dostignut maksimalni broj pregleda");
  pregledi[broj_pregleda++] =
      new Pregled(ime, dan, mjesec, godina, sati, minute);
}
void Pregledi::RegistrirajPregled(Pregled *pregled) {
  if (broj_pregleda >= max_br_pregleda)
    throw std::range_error("Dostignut maksimalni broj pregleda");
  pregledi[broj_pregleda++] = pregled;
}
void Pregledi::IspisiPregledeNaDatum(const Datum &d) const {
  std::vector<Pregled *> pregledi_na_datum;
  std::copy_if(
      pregledi, pregledi + broj_pregleda, std::back_inserter(pregledi_na_datum),
      [&d](Pregled *p1) { return JednakiDatumi(p1->DajDatumPregleda(), d); });
  std::sort(pregledi_na_datum.begin(), pregledi_na_datum.end(),
            [](Pregled *p1, Pregled *p2) {
              return VrijemePrije(p1->DajVrijemePregleda(),
                                  p2->DajVrijemePregleda());
            });
  for (const auto &pregled : pregledi_na_datum)
    pregled->Ispisi();
}
void Pregledi::IspisiSvePreglede() const {
  std::vector<Pregled *> svi_pregledi(pregledi, pregledi + broj_pregleda);
  std::sort(
      svi_pregledi.begin(), svi_pregledi.end(),
      [](Pregled *p1, Pregled *p2) { return Pregled::DolaziPrije(*p1, *p2); });
  for (const auto &pregled : svi_pregledi)
    pregled->Ispisi();
}

int main() {
  int n;
  std::cout << "Unesite maksimalni broj pregleda: ";
  std::cin >> n;
  Pregledi pregledi(n);
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
