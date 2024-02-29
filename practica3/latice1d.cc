#include "latice1d.h"

Latice1d::Latice1d(std::string name, FactoryCelula& factory){
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
      PositionDim<1> pos(1, i);
      latice_[i] = factory.createCelula(pos, Estado(estado));
      //std::cout << "Created cell at position " << (*latice_[i]->GetPosition())[0] << std::endl;
    }
  }
}


void latice1d_open0::nextGeneration() {
  std::cout << "i" << std::endl;
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

Celula& latice1d_open0::operator[](const Position& pos ) {
  int i = pos[0];
  if( i < 0 || i >= latice_.size()) {
    PositionDim<1> pos(1, 0);
    return *(new CelulaAce110(pos, Estado(1)));
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

Celula& latice1d_open1::operator[](const Position& pos ) {
  int i = pos[0];
  if( i < 0 || i >= latice_.size()) {
    PositionDim<1> pos(1, 0);
    return *(new CelulaAce110(pos, Estado(1)));
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

Celula& latice1d_periodic::operator[](const Position& pos) {
  int i = pos[0];
  if(i < 0) {
    return *latice_[latice_.size()];
  } else if( i >= latice_.size()) {
    return *latice_[0];
  } else {
    return *latice_[i];
  }
}