#include "latice.h"
#include <iostream> // Add this line

Latice::Latice(int n, int frontera, std::string fichero) {
  //std::cout << "Latice constructor" << n <<std::endl; // Add this line
  numero_celulas_ = n;
  frontera_ = frontera;
  latice_ = new Celula[n];
  if (fichero == " ") {
    for ( int i = 0; i < n; i++) { 
      if (n/2 == i) {
        latice_[i] = Celula(Posicion(i), Estado(1));
      } else {
        latice_[i] = Celula(Posicion(i), Estado(0));
      }
    }
  } else {
    //std::cout << fichero << std::endl;
    std::ifstream file(fichero);
    int numero_celulas;
    file >> numero_celulas;
    //std::cout << numero_celulas << std::endl;
    for (int i = 0; i < numero_celulas;i++) {
      int estado;
      file >> estado;
      latice_[i] = Celula(Posicion(i), Estado(estado));
    }
  }
}

Latice::~Latice() {
  delete[] latice_;
}

void Latice::NextGeneration() {
  for( int i = 0; i < numero_celulas_; i++ ) {
    for (int i = 0; i < numero_celulas_; i++ ) {
      latice_[i].SetEstadoSiguiente(latice_[i].NextState(*this)); 
    }
    for (int i = 0; i < numero_celulas_; i++ ) {
      latice_[i].UpdateState();
    }
    PrintLatice();
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

int Latice::GetNumCelula() {
  return numero_celulas_;
}

int Latice::GetFrontera() {
  return frontera_;
} 

Celula& Latice::operator[](int i) {
  return latice_[i];
}

