#include "latice2d.h"

Latice2d::Latice2d(std::string tipo, const FactoryCelula& factory) {}

latice2d_reflective::nextGeneration() {
  for (int i = 0; i < latice_.size(); i++) {
    for (int j = 0; j < latice_[i].size(); j++) {
      latice_[i][j]->SetEstado(latice_[i][j]->NextState(*this));
    }
  }
  for (int i = 0; i < latice_.size(); i++) {
    for (int j = 0; j < latice_[i].size(); j++) {
      latice_[i][j]->UpdateState();
    }
  }
}

latice2d_reflective::Population() const {
  int population = 0;
  for (int i = 0; i < latice_.size(); i++) {
    for (int j = 0; j < latice_[i].size(); j++) {
      population += latice_[i][j]->GetEstado().GetEstado();
    }
  }
  return population;
}

latice2d_reflective::operator[](const Position& pos) {
  int i = pos[0];
  int j = pos[1];
  if (i < 0 && j < 0) {
    return *latice_[latice_.GetFilas() - 1][latice_.GetColumnas() - 1];
  } else if (i < 0 && j >= latice_.GetColumnas()) {
    return *latice_ [latice_.GetFilas() - 1][0];
  }
    // Esquina inferior izquierda
  else if (i >= latice_.GetFilas()  && j < 0) {
    return *latice_[0][latice_.GetColumnas() - 1];
  }
    // Esquina inferior derecha
  else if (i >= latice_.GetFilas()  && j >= latice_.GetColumnas()) {
    return *latice_[0][0];
  }
    // Borde superior
  else if (i < 0) {
    return *latice_[latice_.GetFilas() - 1][j];
  }
    // Borde inferior
  else if (i >= latice_.GetFilas()) {
    return *latice_[0][j];
  }
    // Borde izquierdo
  else if (j < 0) {
    return *latice_[i][latice_.GetColumnas() - 1];
  }
    // Borde derecho
  else if (j >= latice_.GetColumnas()) {
    return *latice_[i][0];
  } else {
  return *latice_[i][j];
  }
}

latice2d_periodic::nextGeneration() {
  for (int i = 0; i < latice_.size(); i++) {
    for (int j = 0; j < latice_[i].size(); j++) {
      latice_[i][j]->SetEstado(latice_[i][j]->NextState(*this));
    }
  }
  for (int i = 0; i < latice_.size(); i++) {
    for (int j = 0; j < latice_[i].size(); j++) {
      latice_[i][j]->UpdateState();
    }
  }
}

latice2d_periodic::Population() const {
  int population = 0;
  for (int i = 0; i < latice_.size(); i++) {
    for (int j = 0; j < latice_[i].size(); j++) {
      population += latice_[i][j]->GetEstado().GetEstado();
    }
  }
  return population;
}

latice2d_periodic::operator[](const Position& pos) {
  int i = pos[0];
  int j = pos[1];
  if (i == -1 && j == - 1) {
    return *latice_[0][0];
  } 
    //Arriba derecha
  else if (i == -1 && j == latice_.GetColumnas()) {
    return *latice_ [0][j - 1];
  }
    // Esquina inferior izquierda
  else if (i == latice_.GetFilas() && j == -1) {
    return *latice_[i- 1][0];
  }
    // Esquina inferior derecha
  else if (i == latice_.GetFilas()  && j == latice_.GetColumnas()) {
    return *latice_[i - 1][j - 1];
  }
    // Borde superior
  else if (i == -1) {
    return *latice_[0][j];
  }
    // Borde inferior
  else if (i == latice_.GetFilas()) {
    return *latice_[i - 1][j];
  }
    // Borde izquierdo
  else if (j == -1) {
    return *latice_[i][0];
  }
    // Borde derecho
  else if (j == latice_.GetColumnas()) {
    return *latice_[i][j - 1];
  } else {
  return *latice_[i][j];
  }
}

latice2d_open0::nextGeneration() {
  for (int i = 1; i < latice_.size() - 1; i++) {
    for (int j = 1; j < latice_[i].size() - 1; j++) {
      latice_[i][j]->SetEstado(latice_[i][j]->NextState(*this));
    }
  }
  for (int i = 1; i < latice_.size()- 1 ; i++) {
    for (int j = 1; j < latice_[i].size() - 1; j++) {
      latice_[i][j]->UpdateState();
    }
  }
}

latice2d_open0::Population() const {
  int population = 0;
  for (int i = 0; i < latice_.size(); i++) {
    for (int j = 0; j < latice_[i].size(); j++) {
      population += latice_[i][j]->GetEstado().GetEstado();
    }
  }
  return population;
}

latice2d_open0::operator[](const Position& pos) {
  return *latice_[i][j];
}

latice2d_open1::nextGeneration() {
  for (int i = 1; i < latice_.size() - 1; i++) {
    for (int j = 1; j < latice_[i].size() - 1; j++) {
      latice_[i][j]->SetEstado(latice_[i][j]->NextState(*this));
    }
  }
  for (int i = 1; i < latice_.size()- 1 ; i++) {
    for (int j = 1; j < latice_[i].size() - 1; j++) {
      latice_[i][j]->UpdateState();
    }
  }
}

latice2d_open1::Population() const {
  int population = 0;
  for (int i = 0; i < latice_.size(); i++) {
    for (int j = 0; j < latice_[i].size(); j++) {
      population += latice_[i][j]->GetEstado().GetEstado();
    }
  }
  return population;
}

latice2d_open1::operator[](const Position& pos) {
  return *latice_[i][j];
}

