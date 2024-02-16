#ifndef myvector_cc
#define myvector_cc

#include "myvector.h"

template <typename T> Myvector<T>::Myvector(T valor, int size, int indice_inicial) {
  for (int i = 0; i < size; i++) {
    myvector_.push_back(valor);
  }
  size_ = size;
  indice_inicial_ = indice_inicial;
}

template <typename T> void Myvector<T>::SetCelula(int indice, T* valor) {
  myvector_[indice] = *valor;
}

template <typename T> T* Myvector<T>::GetCelula(int indice) {
  return &myvector_[indice];
}

template <typename T> int Myvector<T>::GetIndiceInicial() {
  return indice_inicial_;
}

template <typename T> void Myvector<T>::SetIndiceInicial(int indice_inicial) {
  indice_inicial_ = indice_inicial;
}

template <typename T> T& Myvector<T>::operator[](int indice) {
  return myvector_[indice];
}

template <typename T> Myvector<T>::Myvector() {
  size_ = 0;
  indice_inicial_ = 0;
}

template <typename T> void Myvector<T>::push_back(T valor) {
  myvector_.push_back(valor);
  size_++;
}

template <typename T> void Myvector<T>::push_front(T valor) {
  myvector_.insert(myvector_.begin(), valor);
  size_++;
}

template <typename T> int Myvector<T>::size() {
  return size_;
}

#endif