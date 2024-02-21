#include "matriz.h"

Matriz::Matriz(int filas, int columnas, int size) {
  filas_ = filas;
  columnas_ = columnas;
  size_ = size;
  indice_inicial_ = 0;
  //std::cout << "j2" ;
  matriz_.resize(filas);
  for (int i = 0; i < filas; i++) {
    //std::cout << i;
    matriz_[i] = Myvector(columnas);
  }
}

void Matriz::resize(int filas) {
  matriz_.resize(filas);
  filas_ = filas;
}

Myvector& Matriz::operator[](int indice) {
  return matriz_[indice - indice_inicial_];
}

int Matriz::GetFilas() {
  return filas_;
}

int Matriz::GetColumnas() {
  return matriz_[0].size();
}

Matriz::Matriz() {
  filas_ = 0;
  columnas_ = 0;
  size_ = 0;
}

void Matriz::Push_back(Myvector myvector) {
  filas_++;
  size_++;
  //matriz_.resize(filas_);
  matriz_.push_back(myvector);
}

void Matriz::Push_front(Myvector myvector) {
  filas_++;
  size_++;
  --indice_inicial_;
  //matriz_.resize(filas_);
  matriz_.insert(matriz_.begin(), myvector);
}

int Matriz::GetIndiceInicial() {
  return indice_inicial_;
}