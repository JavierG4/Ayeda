#include "latice1d.h"

Latice1d::Latice1d(std::string name, const FactoryCelula& factory){
  std::ifstream file(name);
  if (file.is_open()) {
    int n;
    file >> n;
    latice_.resize(n);
    std::string cadena;
    getline(file,cadena);
    getline(file,cadena);
    for (int i = 0; i < n; i++) {
      int estado = 0;
      if (cadena[i] == 'X') {
        estado = 1;
      }
      latice_[i] = factory.createCelula(PositionDim<1>(i, 0), Estado(estado));
    }
  }
}


void latice1d_open0::nextGeneration() {
  for (int i = 0; i < latice_.size(); i++) {
    latice_[i]->SetEstado(latice_[i]->NextState(*this));
  }
  for (int i = 0; i < latice_.size(); i++) {
    latice_[i]->UpdateState();
  }
}

std::size_t latice1d_open0::Population() {
  int population = 0;
  for (int i = 0; i < latice_.size(); i++) {
    population += latice_[i]->GetEstado().GetEstado();
  }
  return population;
}

Celula& latice1d_open0::operator[](int i) {
  if( i < 0 || i >= latice_.size()) {
    return *(new CelulaAce110(PositionDim<1>(1, 0), Estado(1)));
  } else {
    return *latice_[i];
  }
}

void latice1d_open1::nextGeneration() {
  for (int i = 0; i < latice_.size(); i++) {
    latice_[i]->SetEstado(latice_[i]->NextState(*this));
  }
  for (int i = 0; i < latice_.size(); i++) {
    latice_[i]->UpdateState();
  }
}

std::size_t latice1d_open1::Population() {
  int population = 0;
  for (int i = 0; i < latice_.size(); i++) {
    population += latice_[i]->GetEstado().GetEstado();
  }
  return population;
}

Celula& latice1d_open1::operator[](int i) {
  if( i < 0 || i >= latice_.size()) {
    return *(new CelulaAce110(PositionDim<1>(1, 0), Estado(1)));
  } else {
    return *latice_[i];
  }
}

void latice1d_periodic::nextGeneration() {
  for (int i = 0; i < latice_.size(); i++) {
    latice_[i]->SetEstado(latice_[i]->NextState(*this));
  }
  for (int i = 0; i < latice_.size(); i++) {
    latice_[i]->UpdateState();
  }
}

std::size_t latice1d_periodic::Population() {
  int population = 0;
  for (int i = 0; i < latice_.size(); i++) {
    population += latice_[i]->GetEstado().GetEstado();
  }
  return population;
}

Celula& latice1d_periodic::operator[](int i) {
  if(i < 0) {
    return *latice_[latice_.size()];
  } else if( i >= latice_.size()) {
    return *latice_[0];
  } else {
    return *latice_[i];
  }
}