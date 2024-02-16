
#include "myvector.h"
Myvector::Myvector(Celula* valor, int size, int indice_inicial) {
  for (int i = 0; i < size; i++) {
    myvector_.push_back(valor);
  }
  size_ = size;
  indice_inicial_ = indice_inicial;
}

void Myvector::SetCelula(int indice, Celula* valor) {
  myvector_[indice] = valor;
}

Celula* Myvector::GetCelula(int indice) {
  return myvector_[indice];
}

int Myvector::GetIndiceInicial() {
  return indice_inicial_;
}

void Myvector::SetIndiceInicial(int indice_inicial) {
  indice_inicial_ = indice_inicial;
}

Celula*& Myvector::operator[](int indice) {
  return myvector_[indice];
}

Myvector::Myvector(int size) {
  //std::cout << "j1" << std::endl;
  myvector_.resize(size);
  size_ = size;
  indice_inicial_ = 0;
}

void Myvector::push_back(Celula* valor) {
  myvector_.push_back(valor);
  size_++;
}

void Myvector::push_front(Celula* valor) {
  myvector_.insert(myvector_.begin(), valor);
  size_++;
  --indice_inicial_;
}

int Myvector::size() {
  return size_;
}

Myvector::Myvector() {
  size_ = 0;
  indice_inicial_ = 0;
}

