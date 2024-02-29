#include "latice2d.h"

Latice2d::Latice2d(std::string tipo, const FactoryCelula& factory) {
  std::ifstream file(tipo);
  if (!file) {
    std::cerr << "No se pudo abrir el archivo " << tipo << std::endl;
    return;
  }
  int filas = 0;
  int columnas = 0;
  std::string cadena1;
  file >> filas;
  file >> columnas;
  getline(file,cadena1);
  latice_ = Matriz(filas, columnas, filas*columnas);
  for ( int i = 0; i < filas; i++) {
    std::string cadena;
      //std::cout << i << "-" <<cadena.size() << std::endl;
      //std::cout << i << "_" << cadena << std::endl;
    getline(file,cadena);
    //std::cout << i << "-" <<cadena.size() << std::endl;
    for (int j = 0; j < columnas; j++) {
      int estado = 0;
      if (cadena[j] == 'X') {
          //std::cout << "si" << i << " " << j << std::endl;
        estado = 1;
      }
      latice_[i][j] = factory.createCelula(PositionDim<2>(2,i,j),Estado(estado));
    }
  }
}

void latice2d_reflective::nextGeneration() {
  for (int i = 0; i < latice_.GetFilas(); i++) {
    for (int j = 0; j < latice_[i].size(); j++) {
      latice_[i][j]->SetEstado(latice_[i][j]->NextState(*this));
    }
  }
  for (int i = 0; i < latice_.GetFilas(); i++) {
    for (int j = 0; j < latice_[i].size(); j++) {
      latice_[i][j]->UpdateState();
    }
  }
}

std::size_t latice2d_reflective::Population() {
  int population = 0;
  for (int i = 0; i < latice_.GetFilas(); i++) {
    for (int j = 0; j < latice_[i].size(); j++) {
      population += latice_[i][j]->GetEstado().GetEstado();
    }
  }
  return population;
}

Celula& latice2d_reflective::operator[](const Position& pos) {
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

void latice2d_periodic::nextGeneration() {
  for (int i = 0; i < latice_.GetFilas(); i++) {
    for (int j = 0; j < latice_[i].size(); j++) {
      latice_[i][j]->SetEstado(latice_[i][j]->NextState(*this));
    }
  }
  for (int i = 0; i < latice_.GetFilas(); i++) {
    for (int j = 0; j < latice_[i].size(); j++) {
      latice_[i][j]->UpdateState();
    }
  }
}

std::size_t latice2d_periodic::Population() {
  int population = 0;
  for (int i = 0; i < latice_.GetFilas(); i++) {
    for (int j = 0; j < latice_[i].size(); j++) {
      population += latice_[i][j]->GetEstado().GetEstado();
    }
  }
  return population;
}

Celula& latice2d_periodic::operator[](const Position& pos) {
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

void latice2d_open0::nextGeneration() {
  for (int i = 1; i < latice_.GetFilas() - 1; i++) {
    for (int j = 1; j < latice_[i].size() - 1; j++) {
      latice_[i][j]->SetEstado(latice_[i][j]->NextState(*this));
    }
  }
  for (int i = 1; i < latice_.GetFilas() - 1 ; i++) {
    for (int j = 1; j < latice_[i].size() - 1; j++) {
      latice_[i][j]->UpdateState();
    }
  }
}

std::size_t latice2d_open0::Population() {
  int population = 0;
  for (int i = 0; i < latice_.GetFilas(); i++) {
    for (int j = 0; j < latice_[i].size(); j++) {
      population += latice_[i][j]->GetEstado().GetEstado();
    }
  }
  return population;
}

Celula& latice2d_open0::operator[](const Position& pos) {
  return *latice_[pos[0]][pos[1]];
}

void latice2d_open1::nextGeneration() {
  for (int i = 1; i < latice_.GetFilas() - 1; i++) {
    for (int j = 1; j < latice_[i].size() - 1; j++) {
      latice_[i][j]->SetEstado(latice_[i][j]->NextState(*this));
    }
  }
  for (int i = 1; i < latice_.GetFilas()- 1 ; i++) {
    for (int j = 1; j < latice_[i].size() - 1; j++) {
      latice_[i][j]->UpdateState();
    }
  }
}

std::size_t latice2d_open1::Population() {
  int population = 0;
  for (int i = 0; i < latice_.GetFilas(); i++) {
    for (int j = 0; j < latice_[i].size(); j++) {
      population += latice_[i][j]->GetEstado().GetEstado();
    }
  }
  return population;
}

Celula& latice2d_open1::operator[](const Position& pos) {
  return *latice_[pos[0]][pos[1]];
}

