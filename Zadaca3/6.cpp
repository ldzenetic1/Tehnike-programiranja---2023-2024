// TP 2023/2024: Zadaća 3, Zadatak 6
#include <cmath>
#include <iostream>
#include <memory>
#include <vector>

struct Distrikt {
  int broj_distrikta;
  std::shared_ptr<Distrikt> sljedeci;
};
std::vector<int> Razbrajanje(int N, int M) {
  std::shared_ptr<Distrikt> pocetak = nullptr, prethodni = nullptr;
  for (int i = 1; i <= N; i++) {
    auto novi = std::make_shared<Distrikt>();
    novi->broj_distrikta = i;
    novi->sljedeci = nullptr;
    if (!pocetak)
      pocetak = novi;
    else {
      prethodni->sljedeci = novi;
    }
    prethodni = novi;
  }
  prethodni->sljedeci = pocetak;
  std::shared_ptr<Distrikt> p = pocetak;
  std::vector<int> v;
  v.push_back(p->broj_distrikta);
  prethodni->sljedeci = p->sljedeci;
  p = p->sljedeci;
  while (p->sljedeci != p) {
    for (int i = 1; i < M; i++) {
      prethodni = p;
      p = p->sljedeci;
    }
    v.push_back(p->broj_distrikta);
    prethodni->sljedeci = p->sljedeci;
    p = p->sljedeci;
  }
  v.push_back(p->broj_distrikta);
  p->sljedeci = nullptr;
  return v;
}

int OdabirKoraka(int N, int K) {
  if (K > N || K <= 0 || N <= 0)
    throw std::domain_error(
        "Broj blokova i redni broj bloka su pozitivni cijeli brojevi i redni "
        "broj bloka ne moze biti veci od broja blokova");
  for (int M = 1; M <= N; M++) {
    std::vector<int> v = Razbrajanje(N, M);
    if (v.at(v.size() - 1) == K)
      return M;
  }
  return 0;
}
int main() {
  int N;
  std::cout << "Unesite broj distrikta u gradu: ";
  std::cin >> N;
  int K;
  std::cout << "Unesite redni broj distrikta u kojem se nalazi restoran: ";
  std::cin >> K;
  try {
    int korak = OdabirKoraka(N, K);
    if (korak != 0)
      std::cout << "Trazeni korak: " << korak << std::endl;
    else
      std::cout << "Trazeni korak ne postoji" << std::endl;
  } catch (std::domain_error) {
    std::cout << "Broj blokova i redni broj bloka su pozitivni cijeli brojevi "
                 "i redni broj bloka ne moze biti veci od broja blokova";
  }
  return 0;
}