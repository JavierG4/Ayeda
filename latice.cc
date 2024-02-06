#pragma once
#include "latice.h"

Latice::Latice(int n) {
  numero_celulas_ = n;
  for ( int i = 0; i < n; i++) { 
    if ( n/2 == i ) {
      Estado estado(1)
    } else { 
      Estado estado();
      latice_ = new Celula(Posicion(i),estado)[n];
    }
  }
}

Latice::~Latice() {
  delete[] latice_;
}

void Latice::NextGeneration() {
  std::cout << "Next" << std::endl;
}



