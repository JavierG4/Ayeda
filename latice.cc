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
  for (int i = 0; i < numero_celulas_; i++ ) {
    latice_[i].SetEstadoSiguiente(latice_[i].NextState(*this)); 
  }
  for (int i = 0; i < numero_celulas_; i++ ) {
    latice_[i].UpdateState();
  }
}

void Latice::PrintLatice() {
  for (int i = 0; i < numero_celulas_; i++) {
    if (latice_[i].GetEstado().GetEstado() == 1) { 
      std::cout << "X";
    } else {
      std::cout << " ";
    }

  }
  std::cout << std::endl;
}

int Latice::GetNumCelulas(int i) {
  return numero_celulas_;
}

int Latice::GetFrontera() {
  return frontera_;
} 


