#pragma once

#include <queue>
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
   virtual void Inorden() const = 0;
   virtual void Print() const = 0;
   virtual std::ostream& operator<<(std::ostream&)  = 0;

 protected:
   int comparaciones;
};

template <class Key>
class ABE : public AB<Key> {
 public:
   ABE();
   ABE(int);
   ABE(int, std::string);
   ~ABE();
   void Print() const;
   void DeleteNode(NodoB<Key>* node);
   bool Buscar(const Key&);
   bool Insertar(const Key&);
   void Inorden() const;
   std::ostream& operator<<(std::ostream&) ;
   const int TamRama(NodoB<Key>*);
   void InordenRama(NodoB<Key>* nodo) const;
   bool InsertaEquilRama(const Key& dato, NodoB<Key>* nodo);

 private:
   NodoB<Key>* raiz_;
};

template <class Key>
class ABB : public AB<Key>{
 public:
   ABB();
   ABB(int);
   ABB(int, std::string);
   ~ABB();
   void Print() const;
   void DeleteNode(NodoB<Key>* node);
   bool Buscar(const Key&);
   NodoB<Key>* BuscarRama(NodoB<Key>* nodo, const Key& clave_dada, int&);
   bool Insertar(const Key&);
   bool InsertarRama(NodoB<Key>*&, const Key&);
   void Inorden() const;
   std::ostream& operator<<(std::ostream&) ;
   void InordenRama(NodoB<Key>* ) const;
   const int TamRama(NodoB<Key>*);

 private:
   NodoB<Key>* raiz_;
};

template <class Key>
void ABE<Key>::Print() const {
  //operator<<(std::cout);
}

template <class Key>
void ABB<Key>::Print() const {
  //operator<<(std::cout);
}



template <class Key>
void ABE<Key>::DeleteNode(NodoB<Key>* node) {
  if (node != nullptr) {
    DeleteNode(node->GetIzquierda());
    DeleteNode(node->GetDerecha());
    delete node;
  }
}

template <class Key>
ABE<Key>::~ABE() {
  DeleteNode(raiz_);
}

template <class Key>
const int ABE<Key>::TamRama(NodoB<Key>* nodo) {
  if ( nodo == NULL ) {
    return 0;
  }
  return (1 + TamRama(nodo->GetIzquierda()) + TamRama(nodo->GetDerecha()) );
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
    Insertar(dato);
  }
}

template <class Key>
ABE<Key>::ABE(int num, std::string file) {
  raiz_ = nullptr;
  std::ifstream f(file);
  if (f.is_open()) {
    int dato;
    while (f >> dato) {
      Key llave(dato);
      Insertar(dato);
    }
    f.close();
  }
}

template <class Key>
bool ABE<Key>::Buscar(const Key& dato) {
  return raiz_->Buscar(dato);
}

template <class Key>
void ABE<Key>::Inorden() const {
  InordenRama(raiz_);
}

template <class Key>
void ABE<Key>::InordenRama(NodoB<Key>* nodo) const {
  if (nodo != nullptr) {
    InordenRama(nodo->GetIzquierda());
    std::cout << nodo->GetDato() << " " << std::endl;
    InordenRama(nodo->GetDerecha());
  }
}

template <class Key>
bool ABE<Key>::Insertar(const Key& dato) {
  if (raiz_ == NULL) { 
    raiz_ = new NodoB(dato);
    return true;
  } else if (Buscar(dato)) {
    return false;
  } else {
    return InsertaEquilRama(dato, raiz_); 
  }
}

template <class Key>
bool ABE<Key>::InsertaEquilRama(const Key& dato, NodoB<Key>* nodo) {
  if (TamRama(nodo->GetIzquierda()) <= TamRama(nodo->GetDerecha())) {
    if (nodo->GetIzquierda() != NULL) {
      InsertaEquilRama(dato, nodo->GetIzquierda());
    } else { 
      nodo->GetIzquierda() = new NodoB<Key>(dato);
      return true;
    }
  }
  else {
    if (nodo->GetDerecha() != NULL) {
      InsertaEquilRama(dato, nodo->GetDerecha());
    } else {
      nodo->GetDerecha() = new NodoB<Key>(dato);
      return true;
    }
  }
  return false;
}

template <class Key>
std::ostream& ABB<Key>::operator<<(std::ostream& out) {
  if (raiz_ == nullptr) {
    return out;
  }
  std::queue<NodoB<Key> *> nodes;
  nodes.push(raiz_);
  int level = 1;
  while (!nodes.empty()) {
    int nodeCount = nodes.size();
    out << "nivel " << level << " ";
    while (nodeCount > 0) {
      NodoB<Key> *current = nodes.front();
      nodes.pop();
      if (current == nullptr) {
        out << "[.] ";
      } else {
        out << "[" << current->GetDato() << "] ";
        nodes.push(current->GetIzquierda());
        nodes.push(current->GetDerecha());
      }
      nodeCount--;
    }
    out << std::endl;
    level++;
  }
  return out;
}

//ABB

template <class Key>
const int ABB<Key>::TamRama(NodoB<Key>* nodo) {
  if ( nodo == NULL ) {
    return 0;
  }
  return (1 + TamRama(nodo->GetIzquierda()) + TamRama(nodo->GetDerecha()) );
}

template <class Key>
void ABB<Key>::DeleteNode(NodoB<Key>* node) {
  if (node != nullptr) {
    DeleteNode(node->GetIzquierda());
    DeleteNode(node->GetDerecha());
    delete node;
  }
}

template <class Key>
ABB<Key>::~ABB() {
  DeleteNode(raiz_);
}


template <class Key>
bool ABB<Key>::Buscar(const Key& clave_dada) {
  int comparaciones = 0;
  bool resultado = BuscarRama(raiz_, clave_dada, comparaciones) != nullptr;
  std::cout << "Comparaciones = " <<comparaciones << std::endl;
  return resultado;
}

template <class Key>
NodoB<Key>* ABB<Key>::BuscarRama(NodoB<Key>* nodo, const Key& clave_dada, int& comparaciones) {
  comparaciones++;
  if (nodo == nullptr) {
    return nullptr;
  }
  comparaciones++;
  if (clave_dada == nodo->GetDato()) {
    return nodo;
  }
  comparaciones++;
  if (clave_dada < nodo->GetDato()) {
    return BuscarRama(nodo->GetIzquierda(), clave_dada, comparaciones);
  }
  return BuscarRama(nodo->GetDerecha(), clave_dada, comparaciones);
}


template <class Key>
ABB<Key>::ABB() {
  raiz_ = nullptr;
}

template <class Key>
ABB<Key>::ABB(int num) {
  raiz_ = nullptr;
  for (int i = 0; i < num; i++) {
    Key dato;
    //std::cout << "Insertando " << dato << std::endl;
    Insertar(dato);
  }
}

template <class Key>
ABB<Key>::ABB(int num, std::string file) {
  raiz_ = nullptr;
  std::ifstream f(file);
  if (f.is_open()) {
      int dato;
    while (f >> dato) {
      Key llave(dato);
      Insertar(llave);
    }
    f.close();
  }
}

template <class Key>
bool ABB<Key>::Insertar(const Key& clave) {
  if ( Buscar(clave) ) {
    return false;
  }
  bool opcion = InsertarRama(raiz_, clave); 
  return opcion;
}

template<class Key>
bool ABB<Key>::InsertarRama(NodoB<Key>*& nodo, const Key& clave) {
  if (nodo == nullptr) { 
    nodo = new NodoB<Key>(clave);
    return true;
  }
  else if (clave < nodo->GetDato()) { 
    return InsertarRama(nodo->GetIzquierda(), clave);
  }
  else {
    return InsertarRama(nodo->GetDerecha(), clave); 
  }
} 

template <class Key>
void ABB<Key>::Inorden() const {
  InordenRama(raiz_);
}

template <class Key>
void ABB<Key>::InordenRama(NodoB<Key>* nodo) const {
  if (nodo != nullptr) {
    InordenRama(nodo->GetIzquierda());
    std::cout << nodo->GetDato() << " " << std::endl;
    InordenRama(nodo->GetDerecha());
  }
}

template <class Key>
std::ostream& ABE<Key>::operator<<(std::ostream& out) {
  if (raiz_ == nullptr) {
    return out;
  }
  std::queue<NodoB<Key> *> nodes;
  nodes.push(raiz_);
  int level = 1;
  while (!nodes.empty()) {
    int nodeCount = nodes.size();
    out << "nivel " << level << " ";
    while (nodeCount > 0) {
      NodoB<Key> *current = nodes.front();
      nodes.pop();
      if (current == nullptr) {
        out << "[.] ";
      } else {
        out << "[" << current->GetDato() << "] ";
        nodes.push(current->GetIzquierda());
        nodes.push(current->GetDerecha());
      }
      nodeCount--;
    }
    out << std::endl;
    level++;
  }
  return out;
}