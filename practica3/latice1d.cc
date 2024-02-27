#include "latice1d.h"

Latice1d::Latice1d(std::string name, const FactoryCelula& factory) : Latice(name, factory) {}


latice1d_open0::nextGeneration() {
  for (int i = 0; i < latice_.size(); i++) {
    latice_[i]->SetEstado(latice_[i]->NextState(*this));
  }
  for (int i = 0; i < latice_.size(); i++) {
    latice_[i]->UpdateState();
  }
}

latice1d_open0::Population() const {
  int population = 0;
  for (int i = 0; i < latice_.size(); i++) {
    population += latice_[i]->GetEstado().GetEstado();
  }
  return population;
}

latice1d_open0::operator[](int i) {
  if(int i < 0 || int i >= latice_.size()) {
    return new Celula(Position(0, 0), Estado(0));
  } else {
    return *latice_[i];
  }
}

latice1d_open1::nextGeneration() {
  for (int i = 0; i < latice_.size(); i++) {
    latice_[i]->SetEstado(latice_[i]->NextState(*this));
  }
  for (int i = 0; i < latice_.size(); i++) {
    latice_[i]->UpdateState();
  }
}

latice1d_open1::Population() const {
  int population = 0;
  for (int i = 0; i < latice_.size(); i++) {
    population += latice_[i]->GetEstado().GetEstado();
  }
  return population;
}

latice1d_open1::operator[](int i) {
  if(int i < 0 || int i >= latice_.size()) {
    return new Celula(Position(0, 0), Estado(1));
  } else {
    return *latice_[i];
  }
}

latice1d_periodic::nextGeneration() {
  for (int i = 0; i < latice_.size(); i++) {
    latice_[i]->SetEstado(latice_[i]->NextState(*this));
  }
  for (int i = 0; i < latice_.size(); i++) {
    latice_[i]->UpdateState();
  }
}

latice1d_periodic::Population() const {
  int population = 0;
  for (int i = 0; i < latice_.size(); i++) {
    population += latice_[i]->GetEstado().GetEstado();
  }
  return population;
}

latice1d_periodic::operator[](int i) {
  if(int i < 0) {
    return *latice_[latice_.size()];
  } else if(int i >= latice_.size()) {
    return *latice_[0];
  } else {
    return *latice_[i];
  }
}