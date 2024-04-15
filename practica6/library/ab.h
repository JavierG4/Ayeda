#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>
#include <fstream>
#include <utility>
#include "nodob.h"

template <class Key>
class AB {
 public:
   virtual bool Buscar(const Key&) = 0;
   virtual bool Insertar(const Key&) = 0;
   void Inorden() const;
   std::ofstream& operator<<(std::ofstream&);

};

template <class Key>
class ABE : public AB<Key> {
 public:
   ABE();
   ABE(int);
   ABE(int, std::string);
   bool Buscar(const Key&);
   bool Insertar(const Key&);
   void Inorden() const;
   std::ofstream& operator<<(std::ofstream&);
   const int TamRama(NodoB<Key>*);
   bool InsertaEquilRama(const int dato, NodoB<Key>* nodo);

 private:
   NodoB<Key>* raiz_;
};

template <class Key>
class ABB : public AB<Key>{
 public:
   ABB();
   ABB(int);
   ABB(int, std::string);
   bool Buscar(const Key&);
   bool Insertar(const Key&);
   void Inorden() const;
   std::ofstream& operator<<(std::ofstream&);
   const int TamRama(NodoB<Key>*);

 private:
   NodoB<Key>* raiz_;
};

template <class Key>
const int ABE<Key>::TamRama(NodoB<Key>* nodo) {
  if ( nodo == NULL ) {
    return 0;
  }
  return (1 + TamRama(nodo->GetIzquierdo()) + TamRama(nodo->GetDerecho()) );
}


template <class Key>
ABE<Key>::ABE() {
  raiz_ = nullptr;
}

template <class Key>
ABE<Key>::ABE(int num) {
  raiz_ = nullptr;
  for (int i = 0; i < num; i++) {
    Key dato;
    NodoB<Key>* nodo = new NodoB<Key>(dato, raiz_);
    Insertar(nodo);
  }
}

template <class Key>
ABE<Key>::ABE(int num, std::string file) {
  raiz_ = nullptr;
  std::ifstream f(file);
  if (f.is_open()) {
    Key dato;
    while (f >> dato) {
      NodoB<Key>* nodo = new NodoB<Key>(dato, raiz_);
      Insertar(nodo);
    }
    f.close();
  }
}

template <class Key>
bool ABE<Key>::Buscar(const Key& dato) {

}


template <class Key>
bool ABE<Key>::Insertar(const Key& dato) {
  if (raiz_ == NULL) { 
    raiz_ = new NodoB(dato);
    return true;
  }
  else {
    return InsertaEquilRama(dato, raiz_); 
  }
}

template <class Key>
bool ABE<Key>::InsertaEquilRama(const int dato, NodoB<Key>* nodo) {
  if (TamRama(nodo->GetIzquierda()) <= TamRama(nodo->GetDerecha())) {
    if (nodo->GetIzquierda() != NULL)
      InsertaEquilRama(dato, nodo->GetIzquierda());
    else
      nodo->GetIzquierda() = new NodoB(dato);
  }
  else {
    if (nodo->GetDerecha() != NULL) 
      InsertaEquilRama(dato, nodo->GetDerecha());
    else
      nodo->GetDerecha() = new NodoB(dato);
  }
}



//ABB

template <class Key>
const int ABB<Key>::TamRama(NodoB<Key>* nodo) {
  if ( nodo == NULL ) {
    return 0;
  }
  return (1 + TamRama(nodo->GetIzquierda()) + TamRama(nodo->GetDerecha()) );
}

