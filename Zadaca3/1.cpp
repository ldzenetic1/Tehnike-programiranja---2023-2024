//TP 2023/2024: Zadaća 3, Zadatak 1
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <functional>
const double EPSILON = 0.00001;
bool ProvjeraBroja(char karakter){
    if((karakter >= '0' && karakter <= '9') || karakter == '.') return true;
    return false;
}

std::function<double(double)> KubnaInterpolacija(const std::vector<std::pair<double, double>> &cvorovi){
    int vel = cvorovi.size();
    if(vel < 4) throw std::domain_error("Nedovoljan broj cvorova");
    double min = cvorovi[0].first, max = cvorovi[0].first;
    for(int i = 0; i < vel; i++){
        for(int j = i + 1; j < vel; j++){
        if(std::fabs(cvorovi[i].first - cvorovi[j].first) < EPSILON) throw std::domain_error("Neispravni cvorovi");
    }
    if(cvorovi[i].first < min) min = cvorovi[i].first;
    if(cvorovi[i].first > max) max = cvorovi[i].first;
}
    return [=] (double x){
        if(x < min || x > max) throw std::range_error("Argument izvan opsega");
        if(x == max) return cvorovi[vel - 1].second;
        int i = 0;
        for(int k = 1; vel; k++){
            if(x < cvorovi[k].first){
                i = k - 1;
                break;
            }
        }
        if(i < 1) i = 1;
        if(i > vel - 3) i = vel - 3;
        double y = 0;
        for(int k = i - 1; k <= i + 2; k++){
            double l = 1;
            for(int j = i - 1; j <= i + 2; j++){
                if(k != j){
                    l *= (x - cvorovi[j].first)/(cvorovi[k].first - cvorovi[j].first);
                }
            }
            y += l * cvorovi[k].second;
        }
        return y;
   };
}

std::function<double(double)> KubnaInterpolacija(std::function<double(double)> funkcija, double pocetak, double kraj, double delta){
    if(delta <= 0 || kraj < pocetak) throw std::domain_error("Nekorektni parametri");
    std::vector<std::pair<double, double>> cvorovi;
    int n = ((kraj - pocetak) / delta) + 1;
    for(int i = 0; i < n; i++){
        double x = pocetak + i * delta;
        cvorovi.push_back(std::make_pair(x, funkcija(x)));
    }
    int vel = cvorovi.size();
    return [=] (double x){
            if(x < pocetak || x > kraj) throw std::range_error("Argument izvan opsega");
            if(x == kraj) return cvorovi[vel - 1].second;
            int i = 0;
            for(int k = 1; vel; k++){
                if(x < cvorovi[k].first){
                    i = k - 1;
                    break;
                }
            }
            if(i < 1) i = 1;
            if(i > vel - 3) i = vel - 3;
            double y = 0;
            for(int k = i - 1; k <= i + 2; k++){
                double l = 1;
                for(int j = i - 1; j <= i + 2; j++){
                    if(k != j){
                        l *= (x - cvorovi[j].first)/(cvorovi[k].first - cvorovi[j].first);
                    }
                }
                y += l * cvorovi[k].second;
            }
            return y;
        };
    }
int main ()
{
    try{
        int izbor;
        std::vector<std::pair<double, double>> cvorovi;
        std::function<double(double)> fun = [](double x){return x * x + std::sin(x) + std::log(x + 1);};
        std::function<double(double)> interpolacija;
        std::cout<<"Odaberite opciju (1 - unos cvorova, 2 - aproksimacija): \n";
        std::cin>>izbor;
        if(izbor == 1){
            int n;
            std::cout<<"Unesite broj cvorova: \n";
            std::cin>>n;
            std::cout<<"Unesite cvorove kao parove x y: \n";
            for(int i = 0; i < n; i++){
                double x, y;
                std::cin>>x>>y;
                cvorovi.push_back(std::make_pair(x,y));
            }
            std::string arg;
            try{
                interpolacija = KubnaInterpolacija(cvorovi);
                while(true){
                    std::cout<<"Unesite argument (ili \"kraj\" za kraj): \n";
                    std::cin>>arg;
                    if(arg == "kraj") break;
                    bool provjera = true;
                    for(auto x : arg){
                        if(!ProvjeraBroja(x)){
                            provjera = false;
                            break;
                        }
                    }
                    if(!provjera) break;
                    double argument = std::stod(arg);
                    double rezultat = 0;
                    try{
                        rezultat = interpolacija(argument);
                    }
                    catch(const std::range_error &e){
                        std::cout<<e.what()<<"!"<<std::endl;
                        continue;
                    }
                    std::cout<<"f("<<argument<<") = "<<rezultat<<std::endl;
                    }
                }
                catch(const std::domain_error &e){
                    std::cout<<e.what()<<std::endl;
                    return 1;
            }
        }
        else if(izbor == 2){
            double pocetak, kraj, d;
            std::cout<<"Unesite krajeve intervala i korak: \n";
            std::cin>>pocetak>>kraj>>d;
            std::string arg;
            try{
                interpolacija = KubnaInterpolacija(fun, pocetak, kraj, d);
                while(true){
                    std::cout<<"Unesite argument (ili \"kraj\" za kraj): \n";
                    std::cin>>arg;
                    if(arg == "kraj") break;
                    bool provjera = true;
                    for(auto x : arg){
                        if(!ProvjeraBroja(x)){
                            provjera = false;
                            break;
                        }
                    }
                    if(!provjera) break;
                    double argument = std::stod(arg);
                    double rezultat = 0;
                        try{
                            rezultat = interpolacija(argument);
                        }
                        catch(const std::range_error &e){
                            std::cout<<e.what()<<"!"<<std::endl;
                            continue;
                        }
                        std::cout<<"f("<<argument<<") = "<<fun(argument)<<" fapprox("<<argument<<") = "<<rezultat<<std::endl;
                        //std::cout<<"Unesite argument (ili \"kraj\" za kraj): \n";
                    }
            }
            catch(const std::domain_error &e){
                std::cout<<e.what()<<std::endl;
                return 1;
            }
        }
    }
    catch(const std::domain_error &e){
        std::cout<<e.what()<<std::endl;
    }
	return 0;
}
