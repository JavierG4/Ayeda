#include "latice.h"
#include <iostream> // Add this line

Latice::Latice(int n, int frontera, std::string fichero) {
  //std::cout << "Latice constructor" << n <<std::endl; // Add this line
  frontera_ = frontera;
  if (fichero == " ") {
    if (frontera == 0 || frontera == 1) { 
      numero_celulas_ = n + 2;
      latice_ = new Celula[n + 2];
      for ( int i = 1; i < n + 1; i++) { 
        if (n/2 == i) {
          latice_[i] = Celula(Posicion(i), Estado(1));
        } else {
          latice_[i] = Celula(Posicion(i), Estado(0));
        }
      }
      if (frontera == 0) {
        latice_[0] = Celula(Posicion(0), Estado(0));
        latice_[n + 1] = Celula(Posicion(n + 1), Estado(0));
      } else {
        latice_[0] = Celula(Posicion(0), Estado(1));
        latice_[n + 1] = Celula(Posicion(n + 1), Estado(1));
      }
    } else {
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

  } else {
    //std::cout << fichero << std::endl;
    std::ifstream file(fichero);
    //std::cout << numero_celulas << std::endl;
    if (frontera == 0) {
      numero_celulas_ = n + 2;
      latice_ = new Celula[n + 2];
      latice_[0] = Celula(Posicion(0), Estado(0));
      latice_[n + 1] = Celula(Posicion(n + 1), Estado(0));
      for (int i = 0; i < n;i++) {
        int estado;
        file >> estado;
        latice_[i] = Celula(Posicion(i), Estado(estado));
      }
    } else if ( frontera == 1) {
      numero_celulas_ = n + 2;
      latice_ = new Celula[n + 2];
      latice_[0] = Celula(Posicion(0), Estado(1));
      latice_[n + 1] = Celula(Posicion(n + 1), Estado(1));
      for (int i = 1; i < n + 1;i++) {
        int estado;
        file >> estado;
        latice_[i] = Celula(Posicion(i), Estado(estado));
      }
    } else {
      numero_celulas_ = n;
      latice_ = new Celula[n];
      for (int i = 0; i < n;i++) {
        int estado;
        file >> estado;
        latice_[i] = Celula(Posicion(i), Estado(estado));
      }
    }
  }
}

Latice::~Latice() {
  delete[] latice_;
}

void Latice::NextGeneration() {
  if ( frontera_ == 0 || frontera_ == 1) {
    for( int  j= 0; j < numero_celulas_; j++ ) {
      for (int i = 1; i < numero_celulas_ - 1; i++ ) {
        latice_[i].SetEstadoSiguiente(latice_[i].NextState(*this)); 
      }
      for (int e = 1; e < numero_celulas_ - 1; e++ ) {
        latice_[e].UpdateState();
      }
      PrintLatice();
    }
  } else { // periodica
    for( int  j= 0; j < numero_celulas_; j++ ) {
      for (int i = 0; i < numero_celulas_; i++ ) {
        latice_[i].SetEstadoSiguiente(latice_[i].NextState(*this)); 
      }
      for (int e = 0; e < numero_celulas_; e++ ) {
        latice_[e].UpdateState();
      }
      PrintLatice();
    }
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

