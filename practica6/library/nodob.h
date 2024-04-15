#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>
#include <fstream>
#include <utility>

template <class Key>
class NodoB {
 public:
  NodoB(Key&);
  NodoB<Key>* GetIzquierda() { return izquierda_;}
  NodoB<Key>* GetDerecha() { return derecha_;}
  Key GetDato() { return dato_;}
 
 private:
   NodoB<Key>* izquierda_;
   NodoB<Key>* derecha_;
   Key dato_;
};

template <class Key>
NodoB<Key>::NodoB(Key& dato) {
  izquierda_ = nullptr;
  derecha_ = nullptr;
  dato_ = dato;
}


