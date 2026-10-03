// TP 2023/2024: Zadaća 3, Zadatak 3
#include <cmath>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <new>
#include <stdexcept>

enum class Smjer { Desno, Dolje, Dijagonalno };
using Funkcija = std::function<int(int)>;

template <typename TipElemenata> struct Matrica {
  char ime_matrice;
  int br_redova, br_kolona;
  TipElemenata **elementi = nullptr;
};
template <typename TipElemenata>
void UnistiMatricu(Matrica<TipElemenata> &mat) {
  if (!mat.elementi)
    return;
  for (int i = 0; i < mat.br_redova; i++)
    delete[] mat.elementi[i];
  delete[] mat.elementi;
  mat.elementi = nullptr;
}
template <typename TipElemenata>
Matrica<TipElemenata> StvoriMatricu(int br_redova, int br_kolona,
                                    char ime = 0) {
  Matrica<TipElemenata> mat;
  mat.br_redova = br_redova;
  mat.br_kolona = br_kolona;
  mat.ime_matrice = ime;
  mat.elementi = new TipElemenata *[br_redova] {};
  try {
    for (int i = 0; i < br_redova; i++)
      mat.elementi[i] = new TipElemenata[br_kolona];
  } catch (...) {
    UnistiMatricu(mat);
    throw;
  }
  return mat;
}
template <typename TipElemenata> void UnesiMatricu(Matrica<TipElemenata> &mat) {
  for (int i = 0; i < mat.br_redova; i++)
    for (int j = 0; j < mat.br_kolona; j++) {
      std::cout << mat.ime_matrice << "(" << i + 1 << "," << j + 1 << ") = \n";
      std::cin >> mat.elementi[i][j];
    }
}
template <typename TipElemenata>
void IspisiMatricu(Matrica<TipElemenata> &mat, int sirina = 4,
                   bool treba_brisati = false) {
  for (int i = 0; i < mat.br_redova; i++)
    for (int j = 0; j < mat.br_kolona; j++) {
      std::cout << std::setw(sirina) <<std::fixed<<std::setprecision(2)<< mat.elementi[i][j];
      std::cout << std::endl;
    }
  if (treba_brisati) {
    UnistiMatricu(mat);
    mat.elementi = nullptr;
  }
}
template <typename TipElemenata>
Matrica<TipElemenata> ZbirMatrica(const Matrica<TipElemenata> &m1,
                                  const Matrica<TipElemenata> &m2) {
  if (m1.br_redova != m2.br_redova || m1.br_kolona != m2.br_kolona)
    throw std::domain_error("Matrice nemaju jednake dimenzije!");
  auto m3 = StvoriMatricu<TipElemenata>(m1.br_redova, m1.br_kolona);
  for (int i = 0; i < m1.br_redova; i++)
    for (int j = 0; j < m1.br_kolona; j++)
      m3.elementi[i][j] = m1.elementi[i][j] + m2.elementi[i][j];
  return m3;
}
template<typename TipElemenata>
Matrica<TipElemenata> ProsiriPremaFunkcijama(const Matrica<TipElemenata> &matrica, const std::map<Smjer, Funkcija> &mapa, int n){
        if(n < 1) throw std::domain_error("Besmislen parametar");
        if( n == 1) return matrica;
        int br_red = matrica.br_redova;
        int br_kol = matrica.br_kolona;
        int novi_br_red = br_red;
        int novi_br_kol = br_kol;
        bool mat_desno = mapa.find(Smjer::Desno) != mapa.end();
        bool mat_dolje = mapa.find(Smjer::Dolje) != mapa.end();
        bool mat_dijagonalno = mapa.find(Smjer::Dijagonalno) != mapa.end();
        if(mat_desno) novi_br_kol += n * br_kol;
        if(mat_dolje) br_red += n * br_red;
        Matrica<TipElemenata> prosirena = StvoriMatricu<TipElemenata>(br_red, br_kol);
        for(int i = 0; i < br_red; i++){
            for(int j = 0; j < br_kol; j++){
                prosirena.elementi[i][j] = matrica.elementi[i][j];
                for(int k = 1; k <= n; k++){
                if(mat_desno) prosirena.elementi[i][j + k * br_kol] = mapa.at(Smjer::Desno)(prosirena.elementi[i][j + (k - 1) * br_kol]);
                if(mat_dolje) prosirena.elementi[i + k * br_red][j] = mapa.at(Smjer::Dolje)(prosirena.elementi[i + (k - 1) * br_red][j]);
                if(mat_dolje && mat_desno){
                    if(mat_dijagonalno){
                        prosirena.elementi[i + k * br_red][j + k * br_kol] = mapa.at(Smjer::Dijagonalno)(prosirena.elementi[i + (k - 1) * br_red][j + (k - 1) * br_kol]);
                    }
                    else{
                        prosirena.elementi[i + k * br_red][j + k * br_kol] = prosirena.elementi[i + (k - 1) * br_red][j + (k - 1) * br_kol];
                    }
                }
            }
        }
        /*if(it > 0) UnistiMatricu(nova);
        nova = prosirena;*/
    //}
    }
    return prosirena;
}
int main() {
  Matrica<int> a, b, c;
  int m, n;
  std::cout << "Unesite broj redova i kolona za matrice:\n";
  std::cin >> m >> n;
  int N;
  try {
    a = StvoriMatricu<int>(m, n, 'A');
    // b = StvoriMatricu<int>(m, n, 'B');
    std::cout << "Unesi matricu A:\n";
    UnesiMatricu(a);
    /*std::cout << "Unesi matricu B:\n";
    UnesiMatricu(b);*/
    std::map<Smjer, std::function<int(int)>> mapa{
        {Smjer::Desno, [](int x) { return x + 1; }},
        {Smjer::Dolje, [](int x) { return x + 2; }},
        {Smjer::Dijagonalno, [](int x) { return x + 3; }}};
    std::cout << "Unesite n: ";
    std::cin >> N;
    c = ProsiriPremaFunkcijama<int>(a, mapa, N);
    std::cout << "Rezultantna matrica:\n";
    IspisiMatricu(c, 5, true);
    // std::cout << "Zbir ove dvije matrice je:\n";
    // IspisiMatricu(c = ZbirMatrica(a, b), 7);
  } catch (std::domain_error) {
    std::cout << "Besmislen parametar";
  } catch (std::bad_alloc) {
    std::cout << "Nema dovoljno memorije!\n";
  }
  UnistiMatricu(a); /*UnistiMatricu(b);*/
  UnistiMatricu(c);
  return 0;
}
