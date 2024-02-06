#include "latice.h"
#include <iostream> // Add this line

Latice::Latice(int n) {
  numero_celulas_ = n;
  latice_ = new Celula[n];
  for ( int i = 0; i < n; i++) { 
    if (n/2 == i) {
      latice_[i] = Celula(Posicion(i), Estado(1));
    } else {
      latice_[i] = Celula(Posicion(i), Estado(0));
    }
  }
}

Latice::~Latice() {
  delete[] latice_;
}

void Latice::NextGeneration() {
  std::cout << "Next" << std::endl;
}

void Latice::PrintLatice() {
  for (int i = 0; i < numero_celulas_; i++) {
    std::cout << latice_[i].GetEstado().GetEstado() << " ";
  }
  std::cout << std::endl;
}



