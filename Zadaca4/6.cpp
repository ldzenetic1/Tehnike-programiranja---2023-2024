//TP 2023/2024: Zadaća 4, Zadatak 6
#include<iostream>
#include<string>
#include<map>
#include<stdexcept>
#include<memory>

class Student{
    int index;
    std::string ak_god;
    std::string ime_i_prezime;
    std::string adresa;
    std::string br_tel;
    bool IspravnostIndeksa(int br_ind);
    bool IspravnostGodine(std::string ak_god);
    bool IspravnostBroja(std::string br_tel);
    std::string BrisiRazmake(std::string recenica);
public:
    Student(int br_ind,std::string ak_god, std::string ime, std::string adresa, std::string br_telefona ){
        Postavi(br_ind, ak_god, ime, adresa, br_telefona);}
    //Student ();
     void Postavi(int br_ind,std::string ak_god, std::string ime, std::string adresa, std::string br_telefona){
        if(!IspravnostIndeksa(br_ind) || !IspravnostGodine(ak_god) || !IspravnostBroja(br_telefona)) throw std::domain_error("Neispravni parametri");
        if(ak_god == "1") Student::ak_god = "1/B";
        else if(ak_god == "2") Student::ak_god = "2/B";
        else if(ak_god == "3") Student::ak_god = "3/B";
        else Student::ak_god = ak_god;
        Student::index = br_ind;
        Student::ime_i_prezime = BrisiRazmake(ime);
        Student::adresa = BrisiRazmake(adresa);
        Student::br_tel = br_telefona;
    }
    int DajIndeks() const {return index;}
    std::string DajGodinuStudija() const {return ak_god;}
    std::string DajImePrezime() const {return ime_i_prezime;}
    std::string DajAdresu() const {return adresa;}
    std::string DajTelefon() const {return br_tel;}
    void Ispisi() const;
    


};
bool Student::IspravnostIndeksa(int indeks){
    if(indeks > 9999 && indeks < 100000) return true;
    return false;
}
bool Student::IspravnostGodine(std::string a_god){
    return(a_god == "1" || a_god == "2" || a_god == "3" || a_god == "1/B" || a_god == "2/B" || a_god == "3/B" ||
    a_god == "1/M" || a_god == "2/M" || a_god == "3/M" || a_god == "1/D" || a_god == "2/D" || a_god == "3/D" );
}
void Student::Ispisi() const{
    std::cout<<"Broj indeksa: "<<DajIndeks()<<"\n";
    std::cout<<"Godina studija: "<<DajGodinuStudija()<<"\n";
    std::cout<<"Ime i prezime: "<<DajImePrezime()<<"\n";
    std::cout<<"Adresa: "<<DajAdresu()<<"\n";
    std::cout<<"Telefon: "<<DajTelefon()<<"\n";
}
bool Student::IspravnostBroja(std::string br_tel){
    auto pocetak = br_tel.begin();
    auto kraj = br_tel.end();
    if(!std::isdigit(*pocetak)) return false;
    while(std::isdigit(*pocetak)){ 
        if(pocetak == kraj) return false;
        pocetak ++;
    }
    if(*pocetak != '/') return false;
    pocetak++;
    while(std::isdigit(*pocetak)){ 
        if(pocetak == kraj) return false;
        pocetak ++;
    }
    if(*pocetak != '-') return false;
    pocetak++;
    while(std::isdigit(*pocetak)){
        ++pocetak;
        if(pocetak == kraj) return true;
    }
    return false;
}
std::string Student::BrisiRazmake(std::string recenica){
    std::string s;
    bool trenutno_rijec = false;
    bool prvi_karakter = false;
    for(auto it = recenica.begin(); it != recenica.end(); it++){
        if(*it != ' '){
            if(trenutno_rijec){
                s += (*it);
                if(!prvi_karakter) prvi_karakter = true;
            }
            else{
                if(prvi_karakter) s += ' ';
                s += (*it);
                trenutno_rijec = true;
                prvi_karakter = true;
            }
        }
        else if(trenutno_rijec) trenutno_rijec = false;
    }
    return s;
}

class Laptop{
    int ev_broj;
    std::string naziv;
    std::string karakteristike;
    Student *kod_koga_je{};
public:
    Laptop(int evid_br, std::string naziv_lap, std::string napomena): ev_broj(evid_br), naziv(naziv_lap), karakteristike(napomena){
        if(ev_broj < 0) throw std::domain_error("Neispravni parametri");
    }
    //Laptop();
    int DajEvidencijskiBroj()const {return ev_broj;}
    std::string DajNaziv() const {return naziv;}
    std::string DajKarakteristike() const {return karakteristike;}
    void Zaduzi(Student &student);
    void Razduzi() {
        if(kod_koga_je != nullptr)
            kod_koga_je = nullptr;
        }
    bool DaLiJeZaduzen() const {
        return kod_koga_je != nullptr;
    }
    Student &DajKodKogaJe()const;
    Student *DajPokKodKogaJe() const {return kod_koga_je;}
    void Ispisi() const{
        std::cout<<"Evidencijski broj: "<<DajEvidencijskiBroj()<<"\n";
        std::cout<<"Naziv: "<<DajNaziv()<<"\n";
        std::cout<<"Karakteristike: "<<DajKarakteristike()<<"\n";
    }
};
Student &Laptop::DajKodKogaJe() const{
    if(kod_koga_je == nullptr) throw std::domain_error("Laptop nije zaduzen");
    return *kod_koga_je;
}
void Laptop::Zaduzi(Student &student){
    if(kod_koga_je != nullptr) throw std::domain_error("Laptop vec zaduzen");
    kod_koga_je = &student;    

}
class Administracija{
        std::map<int, std::shared_ptr<Student>> student_mapa;
        std::map<int, std::shared_ptr<Laptop>> laptop_mapa;
public:
    Administracija()=default;
    Administracija(const Administracija &a);
    Administracija(Administracija &&a);
    ~Administracija() = default;
    Administracija &operator =(const Administracija &a);
    Administracija &operator =(Administracija &&a);
    void RegistrirajNovogStudenta(int index, std::string ak_god, std::string ime_i_prezime, std::string adresa, std::string br_tel);
    void RegistrirajNoviLaptop(int ev_broj, std::string naziv, std::string karakteristike);
    Student &NadjiStudenta(int index){
        if(!student_mapa.count(index)) throw std::domain_error("Student nije nadjen");
        return *student_mapa.at(index);
    }
    Student NadjiStudenta(int index) const{
        if(!student_mapa.count(index)) throw std::domain_error("Student nije nadjen");
        return *student_mapa.at(index);
    }
    Laptop &NadjiLaptop(int ev_broj){
        if(!laptop_mapa.count(ev_broj)) throw std::domain_error("Laptop nije nadjen");
        return *laptop_mapa.at(ev_broj);
    }
    Laptop NadjiLaptop(int ev_broj) const{
        if(!laptop_mapa.count(ev_broj)) throw std::domain_error("Laptop nije nadjen");
        return *laptop_mapa.at(ev_broj);
    }
    void IzlistajStudente()const{
        for(auto it = student_mapa.begin(); it != student_mapa.end(); it++){
            it->second->Ispisi();
            std::cout<<std::endl;
        }
    };
    void IzlistajLaptope()const{
        for(auto it = laptop_mapa.begin(); it != laptop_mapa.end(); it++){
            it->second->Ispisi();
            if(it->second->DaLiJeZaduzen()){
                std::cout<<"Zaduzio(la): "<<it->second->DajKodKogaJe().DajImePrezime()<<" ("<<it->second->DajKodKogaJe().DajIndeks()<<")"<<std::endl;
            }
            std::cout<<std::endl;
        }
    }
    void ZaduziLaptop(int index, int ev_broj);
    int NadjiSlobodniLaptop()const{
        for(auto it = laptop_mapa.begin(); it != laptop_mapa.end(); it++){
            if(!(it->second->DaLiJeZaduzen())) return it->first;
        }
        throw std::domain_error("Nema slobodnih laptopa");
    }
    void RazduziLaptop(int ev_broj);
    void PrikaziZaduzenja() const;
};
void Administracija::RegistrirajNovogStudenta(int index, std::string ak_god, std::string ime_i_prezime, std::string adresa, std::string br_tel){
    if(student_mapa.find(index) != student_mapa.end()) throw std::domain_error("Student s tim indeksom vec postoji");
    student_mapa[index] = std::make_shared<Student>(index, ak_god, ime_i_prezime, adresa, br_tel);
}
void Administracija::RegistrirajNoviLaptop(int ev_broj, std::string naziv, std::string karakteristike){
    if(laptop_mapa.find(ev_broj) != laptop_mapa.end()) throw std::domain_error("Laptop s tim evidencijskim brojem vec postoji");
    laptop_mapa[ev_broj] = std::make_shared<Laptop>(ev_broj, naziv, karakteristike);
}
void Administracija::ZaduziLaptop(int index, int ev_broj){
    if(!student_mapa.count(index)) throw std::domain_error("Student nije nadjen");
    if(!laptop_mapa.count(ev_broj)) throw std::domain_error("Laptop nije nadjen");
    if(laptop_mapa[ev_broj]->DaLiJeZaduzen()) throw std::domain_error("Laptop vec zaduzen");
    laptop_mapa[ev_broj] -> Zaduzi(*student_mapa[index]);
}
void Administracija::RazduziLaptop(int ev_broj){
    if(!laptop_mapa.count(ev_broj)) throw std::domain_error("Laptop nije nadjen");
    if(!laptop_mapa[ev_broj]->DaLiJeZaduzen()) throw std::domain_error("Laptop nije zaduzen");
    laptop_mapa[ev_broj]->Razduzi();
}
Administracija &Administracija::operator=(const Administracija &a) {
    if (this != &a) {
        student_mapa.clear();
        laptop_mapa.clear();
        for (const auto &student : a.student_mapa)
            student_mapa[student.first] = std::make_unique<Student>(*student.second);
        for (const auto &laptop : a.laptop_mapa)
            laptop_mapa[laptop.first] = std::make_unique<Laptop>(*laptop.second);
    }
    return *this;
}
Administracija &Administracija::operator =(Administracija &&a){
    if(&a != this) {
    student_mapa = std::move(a.student_mapa);
    laptop_mapa = std::move(a.laptop_mapa);
    }
    return *this;
}
Administracija::Administracija(const Administracija &a) {
    for (const auto &student : a.student_mapa)
        student_mapa[student.first] = std::make_unique<Student>(*student.second);
    for (const auto &laptop : a.laptop_mapa)
        laptop_mapa[laptop.first] = std::make_unique<Laptop>(*laptop.second);
}
Administracija::Administracija(Administracija &&a)  {
    student_mapa = std::move(a.student_mapa);
    laptop_mapa = std::move(a.laptop_mapa); 
}
void Administracija::PrikaziZaduzenja() const{
    bool ima_zaduzenja = false;
    for(auto it = laptop_mapa.begin(); it != laptop_mapa.end(); it++){
        if(it->second->DaLiJeZaduzen()){
            ima_zaduzenja = true;
            std::cout<<"Student "<<it->second->DajKodKogaJe().DajImePrezime()<<" ("<<it->second->DajKodKogaJe().DajIndeks()<<
            ") zaduzio/la laptop broj "<<it->first<<"\n";
        }
    }
    if(!ima_zaduzenja) 
        std::cout<<"Nema zaduzenja\n";
}
int main ()
{
    Administracija a;
    int izbor;
    do{
        std::cout<<"Odaberite jednu od sljedecih opcija: \n"
            <<"1 - RegistrirajNovogStudenta\n2 - RegistrirajNoviLaptop\n"
            <<"3 - IzlistajStudente\n4 - IzlistajLaptope\n5 - NadjiSlobodniLaptop\n"
            <<"6 - ZaduziLaptop\n7 - RazduziLaptop\n8 - PrikaziZaduzenja\nK - Kraj programa\n";
            std::cin>>izbor;
            if(!std::cin) break;
            try{
                if(izbor == 1){
                    int index;
                    std::cout<<"Unesite broj indeksa: \n";
                    std::cin>>index;
                    std::cin.ignore(10000, '\n');
                    std::cout<<"Unesite godinu studija (formata A/X, gdje je A godina studija, a X prima vrijednosti B,M,D, zavisno od studija): \n";
                    std::string ak_god;
                    std::getline(std::cin, ak_god);
                    std::cout<<"Unesite ime i prezime studenta: \n";
                    std::string ime_i_p;
                    std::getline(std::cin, ime_i_p);
                    std::cout<<"Unesite adresu studenta: \n";
                    std::string adresa;
                    std::getline(std::cin, adresa);
                    std::cout<<"Unesite broj telefona (formata x/x-x): \n";
                    std::string telefon;
                    std::getline(std::cin, telefon);
                    a.RegistrirajNovogStudenta(index, ak_god,  ime_i_p, adresa, telefon);
                }
                else if(izbor == 2){
                    std::cout<<"Unesite evidencijski broj laptopa\n";
                    int ev_broj;
                    std::cin>>ev_broj;
                    std::cin.ignore(10000, '\n');
                    std::cout<<"Unesite naziv laptopa\n";
                    std::string naziv;
                    std::getline(std::cin, naziv);
                    std::cout<<"Unesite karakteristike laptopa:\n";
                    std::string karakteristike;
                    std::getline(std::cin, karakteristike);
                    a.RegistrirajNoviLaptop(ev_broj, naziv, karakteristike);
                    std::cout<<"Laptop uspjesno registrovan!\n";
                }
                else if(izbor == 3){
                    a.IzlistajStudente();
                }
                else if(izbor == 4){
                    a.IzlistajLaptope();
                }
                else if(izbor == 5){
                    std::cout<<"Slobodni laptop: "<<a.NadjiSlobodniLaptop();
                }
                else if(izbor == 6){
                    std::cout<<"Unesite broj indeksa:\n";
                    int index;
                    std::cin>>index;
                    std::cout<<"Unesite evidencijski broj laptopa\n";
                    int ev_broj;
                    std::cin>>ev_broj;
                    a.ZaduziLaptop(index, ev_broj);
                }
                else if(izbor == 7){
                    std::cout<<"Unesite evidencijski broj laptopa:\n";
                    int ev_broj;
                    std::cin>>ev_broj;
                    a.RazduziLaptop(ev_broj);
                }
                else if(izbor == 8){
                    a.PrikaziZaduzenja();
                }
            }
            catch(std::exception &e){
                std::cout<<"Izuzetak: "<<e.what()<<"!"<<std::endl;
            }
    }while(true);


	return 0;
}

