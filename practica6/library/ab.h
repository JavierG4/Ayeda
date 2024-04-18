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
   std::ofstream& operator<<(std::ofstream&);

};

template <class Key>
class ABE : public AB<Key> {
 public:
   ABE();
   ABE(int);
   ABE(int, std::string);
   ~ABE();
   void DeleteNode(NodoB<Key>* node);
   bool Buscar(const Key&);
   bool Insertar(const Key&);
   void Inorden() const;
   std::ofstream& operator<<(std::ofstream&);
   const int TamRama(NodoB<Key>*);
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
   void DeleteNode(NodoB<Key>* node);
   bool Buscar(const Key&);
   bool Insertar(const Key&);
   bool InsertarRama(NodoB<Key>*&, const Key&);
   void Inorden() const;
   std::ofstream& operator<<(std::ofstream&);
   const int TamRama(NodoB<Key>*);

 private:
   NodoB<Key>* raiz_;
};

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
bool ABE<Key>::InsertaEquilRama(const Key& dato, NodoB<Key>* nodo) {
  if (TamRama(nodo->GetIzquierda()) <= TamRama(nodo->GetDerecha())) {
    if (nodo->GetIzquierda() != NULL) {
      InsertaEquilRama(dato, nodo->GetIzquierda());
    } else { 
      nodo->GetIzquierda() = new NodoB<Key>(dato);
    }
  }
  else {
    if (nodo->GetDerecha() != NULL) {
      InsertaEquilRama(dato, nodo->GetDerecha());
    } else {
      nodo->GetDerecha() = new NodoB<Key>(dato);
    }
  }
}

template <class Key>
void ABE<Key>::Inorden() const {
  if (raiz_ == nullptr) {
    return;
  }
  std::queue<NodoB<Key> *> nodes;
  nodes.push(raiz_);
  int level = 1;
  while (!nodes.empty()) {
    int nodeCount = nodes.size();
    std::cout << "nivel " << level << " ";
    while (nodeCount > 0) {
      NodoB<Key> *current = nodes.front();
      nodes.pop();

      if (current == nullptr) {
        std::cout << "[.] ";
      }
      else {
        std::cout << "[" << current->GetDato() << "] ";
        nodes.push(current->GetIzquierda());
        nodes.push(current->GetDerecha());
      }
      nodeCount--;
    }
    std::cout << std::endl;
    level++;
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
bool ABB<Key>::Buscar(const Key& dato) {
  return raiz_->Buscar(dato);
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
  return InsertarRama(raiz_, clave); 
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
  if (raiz_ == nullptr) {
    return;
  }
  std::queue<NodoB<Key> *> nodes;
  nodes.push(raiz_);
  int level = 1;
  while (!nodes.empty()) {
    int nodeCount = nodes.size();
    std::cout << "nivel " << level << " ";
    while (nodeCount > 0) {
      NodoB<Key> *current = nodes.front();
      nodes.pop();
      if (current == nullptr) {
        std::cout << "[.] ";
      } else {
        std::cout << "[" << current->GetDato() << "] ";
        nodes.push(current->GetIzquierda());
        nodes.push(current->GetDerecha());
      }
      nodeCount--;
    }
    std::cout << std::endl;
    level++;
  }
}