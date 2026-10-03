//TP 2023/2024: Zadaća 4, Zadatak 1
#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <stdexcept>
#include <memory>

typedef std::pair<double, double> Tacka;
enum Pozicija {GoreLijevo, GoreDesno, DoljeLijevo, DoljeDesno};
enum Smjer {Nalijevo, Nadesno};
constexpr double EPSILON = 1e-9;
class Pravougaonik{
    Tacka t_1, t_2;
public:
    Pravougaonik(const Tacka &t1, const Tacka &t2){ Postavi(t1, t2); };
    void Postavi(const Tacka &t1, const Tacka &t2){
        this->t_1 = t1;
        this->t_2 = t2;
    };
    void Postavi(Pozicija p, const Tacka &t){
        switch(p){
            case GoreDesno:
                t_1 = t;
                break;
            case GoreLijevo:
                t_2.first = t.first;
                t_1.second = t.second;
                break;
            case DoljeLijevo:
                t_2 = t;
                break;
            case DoljeDesno:
                t_1.first = t.first;
                t_2.second = t.second;
                break;
        }
    };
    void Centriraj(const Tacka &t){
        Tacka centar = DajCentar();
        double dx = t.first - centar.first;
        double dy = t.second - centar.second;
        Transliraj(dx, dy);
    }
    Tacka DajTjeme(Pozicija p) const{
        switch(p){
            case GoreDesno:
                return {std::max(t_1.first, t_2.first), std::max(t_1.second, t_2.second)};
            case GoreLijevo:
                return {std::min(t_1.first, t_2.first), std::max(t_1.second, t_2.second)};
            case DoljeDesno:
                return {std::max(t_1.first, t_2.first), std::min(t_1.second, t_2.second)};
            case DoljeLijevo:
                return {std::min(t_1.first, t_2.first), std::min(t_1.second, t_2.second)};
        }
        return {0, 0};
    };
    Tacka DajCentar() const{
        return {(t_1.first + t_2.first) / 2,(t_1.second + t_2.second) / 2};
    };
    double DajHorizontalnu() const{
        return std::abs(t_1.first - t_2.first);
    };
    double DajVertikalnu() const{
        return std::abs(t_1.second - t_2.second);
    };
    double DajObim() const{
        return 2 * (DajHorizontalnu() + DajVertikalnu());
    };
    double DajPovrsinu() const{
        return DajHorizontalnu() * DajVertikalnu();
    };
    static Pravougaonik Presjek(const Pravougaonik &p1, const Pravougaonik &p2){
        double x1 = std::max(std::min(p1.t_1.first, p1.t_2.first), std::min(p2.t_1.first, p2.t_2.first));
        double x2 = std::min(std::max(p1.t_1.first, p1.t_2.first), std::max(p2.t_1.first, p2.t_2.first));
        double y1 = std::max(std::min(p1.t_1.second, p1.t_2.second), std::min(p2.t_1.second, p2.t_2.second));
        double y2 = std::min(std::max(p1.t_1.second, p1.t_2.second), std::max(p2.t_1.second, p2.t_2.second));
        if(x2 < x1 || y2 < y1) throw std::domain_error("Pravougaonici se ne presjecaju");
        return Pravougaonik(Tacka(x1, y2), Tacka(x2, y1));
    };

    void Transliraj(double delta_x, double delta_y){
        t_1.first += delta_x;
        t_1.second += delta_y;
        t_2.first += delta_x;
        t_2.second += delta_y;
    };
  void Rotiraj(const Tacka &t, Smjer s){
        double x = t.first;
        double y = t.second;
        Tacka t1 = t_1, t2 = t_2;

        if(s == Nalijevo){
            t_1.first = x + y - t1.second;
            t_1.second = y - x + t1.first;
            t_2.first = x + y - t2.second;
            t_2.second = y - x + t2.first;
        } else if(s == Nadesno){
            t_1.first = x - y + t1.second;
            t_1.second = y + x - t1.first;
            t_2.first = x - y + t2.second;
            t_2.second = y + x - t2.first;
        }
    } 
    void Ispisi() const{
        Tacka gl = DajTjeme(GoreLijevo);
        Tacka dd = DajTjeme(DoljeDesno);
        std::cout<<"{{"<<gl.first<<","<<gl.second<<"},{"<<dd.first<<","<<dd.second<<"}}";
    }
    friend bool DaLiSePoklapaju(const Pravougaonik &p1, const Pravougaonik &p2);
    friend bool DaLiSuPodudarni(const Pravougaonik &p1, const Pravougaonik &p2);
    friend bool DaLiSuSlicni(const Pravougaonik &p1, const Pravougaonik &p2);
};
bool DaLiSePoklapaju(const Pravougaonik &p1, const Pravougaonik &p2){
    if((p1.t_1 == p2.t_1 && p1.t_2 == p2.t_2) || (p1.t_1 == p2.t_2 && p1.t_2 == p2.t_1)) return true;
    else{
        std::vector<Tacka> tacka1 = {p1.DajTjeme(GoreLijevo), p1.DajTjeme(GoreDesno), p1.DajTjeme(DoljeLijevo), p1.DajTjeme(DoljeDesno)};
        std::vector<Tacka> tacka2 = {p2.DajTjeme(GoreLijevo), p2.DajTjeme(GoreDesno), p2.DajTjeme(DoljeLijevo), p2.DajTjeme(DoljeDesno)};
        std::sort(tacka1.begin(), tacka1.end());
        std::sort(tacka2.begin(), tacka2.end());
        return tacka1 == tacka2;
    } 
}
bool DaLiSuPodudarni(const Pravougaonik &p1, const Pravougaonik &p2){
        return (p1.DajHorizontalnu()==p2.DajHorizontalnu() && p1.DajVertikalnu()==p2.DajVertikalnu()) ||
        (p1.DajHorizontalnu()==p2.DajVertikalnu() && p1.DajVertikalnu()==p2.DajHorizontalnu());
    }

bool DaLiSuSlicni(const Pravougaonik &p1, const Pravougaonik &p2) {
    if ((std::abs(p1.DajHorizontalnu() * p2.DajVertikalnu() - p2.DajHorizontalnu() * p1.DajVertikalnu()) < EPSILON) ||
        (std::abs(p1.DajHorizontalnu() * p2.DajHorizontalnu() - p1.DajVertikalnu() * p2.DajVertikalnu()) < EPSILON)) {
        return true;
    }
    return false;
}
int main ()
{
    int n;
    std::cout<<"Unesite n: ";
    std::cin>>n;
    std::vector<Pravougaonik*> pravougaonici(n);
    for(int i = 0; i < n; i++){
        std::cout<<"Unesite 1. tjeme pravougaonika "<<i+1<<": ";
        double x1, y1;
        std::cin>>x1>>y1;
        std::cout<<"Unesite 2. tjeme pravougaonika "<<i+1<<": ";
        double x2, y2;
        std::cin>>x2>>y2;
        //pravougaonici[i] = new Pravougaonik(Tacka{x1, y1}, Tacka{x2, y2});
        try{
            pravougaonici[i] = new Pravougaonik(Tacka{x1, y1}, Tacka{x2, y2});
        }
        catch(std::exception &e){
            std::cout<<e.what()<<std::endl;
        }
    }
    std::cout<<"Unesite podatke za transliranje (dx dy): ";
    double dx, dy;
    std::cin>>dx>>dy;
    std::transform(pravougaonici.begin(), pravougaonici.end(), pravougaonici.begin(), [dx, dy](Pravougaonik *p){
        (*p).Transliraj(dx, dy);
        return p;
    });
    std::transform(pravougaonici.begin(), pravougaonici.end(), pravougaonici.begin(), [](Pravougaonik *p){
        (*p).Rotiraj(p->DajCentar(), Nadesno);
        return p;
    });
    std::cout<<"Pravougaonici, nakon transformacija:\n";
    std::for_each(pravougaonici.begin(), pravougaonici.end(),[](Pravougaonik *p){
        p->Ispisi();
        std::cout<<std::endl;
    });
    auto pmax = std::max_element(pravougaonici.begin(), pravougaonici.end(), [](const Pravougaonik *p1, const Pravougaonik *p2){
        return p1->DajPovrsinu() < p2->DajPovrsinu();
    });
    std::cout<<"Pravougaonik s najvecom povrsinom: ";
    if(pmax != pravougaonici.end()) {(*pmax)->Ispisi();}
    for(int i = 0; i < n; i++){
        delete pravougaonici[i];
    }

	return 0;
}
