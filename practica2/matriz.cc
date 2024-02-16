#include "matriz.h"

Matriz::Matriz(int filas, int columnas, int size) {
  filas_ = filas;
  columnas_ = columnas;
  size_ = size;
  matriz_.resize(filas);
  for (int i = 0; i < filas; i++) {
    matriz_[i].SetIndiceInicial(i);
    matriz_[i].SetSize(columnas);
  }
}

Matriz::~Matriz() {
  for (int i = 0; i < filas_; i++) {
    matriz_[i].~Myvector();
  }
}

Myvector Matriz::operator[](int indice) {
  return matriz
}