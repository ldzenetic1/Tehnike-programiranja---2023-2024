//TP 2023/2024: Zadaća 2, Zadatak 1
#include <iostream>
#include <cmath>
#include <stdexcept>
#include <vector>
#include <string>
#include <limits>

namespace Robot{
    enum class Pravci {Sjever, Sjeveroistok, Istok, Jugoistok, Jug, Jugozapad, Zapad, Sjeverozapad};
    enum class KodoviGresaka {PogresnaKomanda, NedostajeParametar, SuvisanParametar, NeispravanParametar};
    enum class Komande {Idi, Rotiraj, Sakrij, Otkrij, PrikaziTeren, Kraj};

    void PravacRobota(Pravci orijentacija);
    std::vector<std::vector<char>> teren(21, std::vector<char>(21));
    void KreirajTeren(int xmin, int xmax, int ymin, int ymax, int &x, int &o, Pravci &orijentacija);
    bool Idi(int &x, int &y, Pravci orijentacija, int korak);
    void Rotiraj(Pravci &orijentacija, int ugao);
    void Sakrij();
    void Otkrij();
    void IspisiPoziciju(int x, int y, Pravci orijentacija);
    void PrikaziTeren();
    void PrijaviGresku(KodoviGresaka kod_greske);
    bool IzvrsiKomandu(Komande komanda, int parametar, int &x, int &y, Pravci &orijentacija);
    bool UnosKomande(Komande &komanda, int &parametar, KodoviGresaka &kod_greske);
}

bool robot_aktivan = true;
int x_osa  = 0;
int y_osa = 0;
//std::vector<std::vector<char>> teren;

void Robot::KreirajTeren(int xmin, int xmax, int ymin, int ymax, int &x, int &o, Pravci &orijentacija){
    //std::vector<std::vector<char>> teren;
    if(xmin > xmax || ymin > ymax) throw std::range_error("Nelegalan opseg!");
    //int sirina = xmax - xmin + 1;
    //int visina = ymax - ymin + 1;
    x = (xmax + xmin) / 2;
    o = (ymax + ymin) / 2;
   
    orijentacija = Pravci::Sjever;
    /*teren.resize(visina, std::vector<char> (sirina, ' '));
    for(int i=0; i<visina; i++)
        for(int j=0; j<sirina; j++){
            if(i == 0 || i == visina -1 || j == 0 || j == sirina -1){
                teren.at(i).at(j) = '#';
            }
        }*/
}
bool Robot::Idi(int &x, int &y, Pravci orijentacija, int korak){
    int nova_x = x, nova_y = y;
    switch(orijentacija){
        case Pravci::Sjever: 
            nova_y -= korak;
            break;
        case Pravci::Jug:
            nova_y += korak;
            break;
        case Pravci::Istok:
            nova_x += korak;
            break;
        case Pravci::Zapad:
            nova_x -= korak;
            break;
        case Pravci::Sjeverozapad:
            nova_x -= korak;
            nova_y -= korak;
            break;
        case Pravci::Jugozapad:
            nova_x -= korak;
            nova_y += korak;
            break;
        case Pravci::Sjeveroistok:
            nova_x += korak;
            nova_y -= korak;
            break;
        case Pravci::Jugoistok:
            nova_x += korak;
            nova_y += korak;
            break;
    }
    if(nova_x <= 0 || nova_x > teren.at(0).size() || nova_y <= 0 || nova_y > teren.size()) 
        return false;
    x = nova_x;
    y = nova_y;
    return true;
}
void Robot::Rotiraj(Pravci &orijentacija, int ugao){
    if(ugao > 0){
        for(int i = 0; i < ugao; i++){
            switch(orijentacija){
                case Pravci::Sjever:
                    orijentacija = Pravci::Zapad;
                    break;
                case Pravci::Istok:
                    orijentacija = Pravci::Sjever;
                    break;
                case Pravci::Jug:
                    orijentacija = Pravci::Istok;
                    break;
                case Pravci::Zapad:
                    orijentacija = Pravci::Jug;
                    break;
                case Pravci::Sjeveroistok:
                    orijentacija = Pravci::Sjeverozapad;
                    break;
                case Pravci::Sjeverozapad:
                    orijentacija = Pravci::Jugozapad;
                    break;
                case Pravci::Jugoistok:
                    orijentacija = Pravci::Sjeveroistok;
                    break;
                case Pravci::Jugozapad:
                    orijentacija = Pravci::Jugoistok;
                    break;
            }
        }
    }
    else if(ugao < 0){
        for(int i = 0; i < -ugao; i++){
            switch(orijentacija){
                case Pravci::Sjever:
                    orijentacija = Pravci::Istok;
                    break;
                case Pravci::Istok:
                    orijentacija = Pravci::Jug;
                    break;
                case Pravci::Zapad:
                    orijentacija = Pravci::Sjever;
                    break;
                case Pravci::Jug:
                    orijentacija = Pravci::Zapad;
                    break;
                case Pravci::Sjeveroistok:
                    orijentacija = Pravci::Jugoistok;
                    break;
                case Pravci::Sjeverozapad:
                    orijentacija = Pravci::Sjeveroistok;
                    break;
                case Pravci::Jugoistok:
                    orijentacija = Pravci::Jugozapad;
                    break;
                case Pravci::Jugozapad:
                    orijentacija = Pravci::Sjeverozapad;
                    break;
            }
        }
    }
}
void Robot::Sakrij(){
    robot_aktivan= false;
}
void Robot::Otkrij(){
    robot_aktivan= true;
}
void Robot::PravacRobota(Pravci orijentacija){
    switch(orijentacija){
        case Pravci::Sjever:
            std::cout<<"sjever.\n";
            break;
        case Pravci::Jug:
            std::cout<<"jug.\n";
            break;
        case Pravci::Istok:
            std::cout<<"istok.\n";
            break;
        case Pravci::Zapad:
            std::cout<<"zapad.\n";
            break;
        case Pravci::Sjeveroistok:
            std::cout<<"sjeveroistok.\n";
            break;
        case Pravci::Sjeverozapad:
            std::cout<<"sjeverzapad.\n";
            break;
        case Pravci::Jugoistok:
            std::cout<<"jugoistok.\n";
            break;
        case Pravci::Jugozapad:
            std::cout<<"jugozapad.\n";
            break;
    }

}
void Robot::IspisiPoziciju(int x, int y, Pravci orijentacija){
    std::cout<<"Robot je ";
    if(robot_aktivan){
        std::cout<<"vidljiv, ";
    }
    else{
        std::cout<<"nevidljiv, ";
    }
    std::cout<<"nalazi se na poziciji ("<<x<<", "<<y<<") i gleda na ";
    PravacRobota(orijentacija);
}
void Robot::PrikaziTeren(){
    for(int i = 0; i < teren.size(); i++){
        for(int j = 0; j < teren.at(0).size(); j++){
            if(i == 0 || i  == (teren.size() - 1) || j == 0 || j == (teren.at(0).size() - 1))
                teren.at(i).at(j) = '#';
            if(i == x_osa && j == y_osa){
                if(robot_aktivan){
                    teren.at(i).at(j) ='o';
                }
                else{
                    teren.at(i).at(j) ='*';
                }
            }
            else{
                std::cout<<teren.at(i).at(j)<<" ";
            }
        }
        std::cout<<std::endl;
    }
}
void Robot::PrijaviGresku(KodoviGresaka kod_greske){
    switch(kod_greske){
        case KodoviGresaka::PogresnaKomanda:
            std::cout<<"\nNerazumljiva komanda!";
            break;
        case KodoviGresaka::NedostajeParametar:
            std::cout<<"\nKomanda trazi parametar koji nije naveden!";
            break;
        case KodoviGresaka::NeispravanParametar:
            std::cout<<"\nParametar komande nije ispravan!";
            break;
        case KodoviGresaka::SuvisanParametar:
            std::cout<<"\nZadan je suvisan parametar nakon komande!";
    }
}
bool Robot::UnosKomande(Komande &komanda, int &parametar, KodoviGresaka &kod_greske){
    std::string unos;
    std::getline(std::cin, unos);
    if(unos == "I"){
        komanda = Komande::Idi;
    }else if(unos == "R"){
        komanda = Komande::Rotiraj;
    }else if(unos == "S+"){
        komanda = Komande::Sakrij;
    }else if(unos == "S-"){
        komanda = Komande::Otkrij;
    }else if(unos == "K"){
        komanda = Komande::Kraj;
    }else if(unos == "T"){
        komanda = Komande::PrikaziTeren;
    }else{
        kod_greske = KodoviGresaka::PogresnaKomanda;
        PrijaviGresku(kod_greske);
        return false;
    }

    if(komanda == Komande::Idi || komanda == Komande::Rotiraj){
        if(std::cin.peek() != '\n'){
            std::cin>>parametar;
        }else{
            parametar = 0;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    return true;

}
bool Robot::IzvrsiKomandu(Komande komanda, int parametar, int &x, int &y, Pravci &orijentacija){
    if(komanda == Komande::Kraj){
        std::cout<<"Dovidjenja!";
        return 0;
    }
    switch(komanda){
        case Komande::Idi:
            Idi(x, y, orijentacija, parametar);
            IspisiPoziciju(x, y, orijentacija);
            break;
        case Komande::Otkrij:
            Otkrij();
            IspisiPoziciju(x, y, orijentacija);
            break;
        case Komande::PrikaziTeren:
            PrikaziTeren();
            break;
        case Komande::Sakrij:
            Sakrij();
            IspisiPoziciju(x, y, orijentacija);
            break;
        case Komande::Rotiraj:
            Rotiraj(orijentacija, parametar);
            IspisiPoziciju(x, y, orijentacija);
            break;
        case Komande::Kraj:
            std::cout<<"Dovidjenja!";
            break;
    }
    return true;
}

int main ()
{
    int xmax, xmin, ymin, ymax;
    std::cout<<"Unesite dimenzije terena (xmin, xmax, ymin, ymax): ";
    std::cin>>xmin>>xmax>>ymin>>ymax;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    int x, y;
    Robot::Pravci orijentacija;
    Robot::Komande komanda;
    int parametar;
    Robot::KodoviGresaka kod_greske;
    try{
        Robot::KreirajTeren(xmin, xmax, ymin, ymax, x, y, orijentacija);
    }
    catch(std::range_error &e){
        std::cout<<e.what();
    }
        Robot::IspisiPoziciju(x, y, orijentacija);
        do{
            std::cout<<"Unesite komandu:";
            Robot::UnosKomande(komanda, parametar, kod_greske);
            Robot::IzvrsiKomandu(komanda, parametar, x, y, orijentacija);
            if(komanda != Robot::Komande::Kraj){
                if(!Robot::IzvrsiKomandu(komanda, parametar, x, y, orijentacija)){
                    std::cout<<"Robot je pokusao napustiti teren!"<<std::endl;
                }
            }
        }while(komanda != Robot::Komande::Kraj);
   


	return 0;
}