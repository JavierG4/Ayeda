#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>
#include <fstream>
#include <utility>

template <class Key>
class NodoB {
 public:
  NodoB(const Key&);
  NodoB<Key>*& GetIzquierda() { return izquierda_;}
  NodoB<Key>*& GetDerecha() { return derecha_;}
  bool Buscar (const Key& dato);
  Key GetDato() { return dato_;}
 
 private:
   NodoB<Key>* izquierda_;
   NodoB<Key>* derecha_;
   Key dato_;
};

template <class Key>
NodoB<Key>::NodoB(const Key& dato) {
  izquierda_ = nullptr;
  derecha_ = nullptr;
  dato_ = dato;
}

template <class Key>
bool NodoB<Key>::Buscar( const Key& dato ) {
  if (dato == GetDato()) {
    return true;
  } else {
    if (GetIzquierda() != nullptr && GetIzquierda()->Buscar(dato)) {
      return true;
    }
    if (GetDerecha() != nullptr && GetDerecha()->Buscar(dato)) {
      return true;
    }
    return false;
  }
}
/*
template <class Key>
int NodoB<Key>::CalcularHijos() {
  int total = 0;
  if ( izquierda_ != nullptr ) {
    total += izquierda_->CalcularHijos();
  } 
  if ( derecha_ != nullptr ) {
    total += izquierda_->CalcularHijos();
  }
  if (izquierda_ == nullptr ) {
    total += 1;
  }
  if (derecha_ == nullptr) {
    total += 1;
  }
  return total;
}
*/