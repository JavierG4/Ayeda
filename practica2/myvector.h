#ifndef myvector_h
#define myvector_h


#include <iostream>
#include "celula.h"
#include <vector>

template <typename T>
class Myvector {
 public:
   Myvector(T, int, int);
   Myvector();
   void push_back(T);
   void push_front(T);
   void SetCelula(int, T*);
   T* GetCelula(int);
   int GetIndiceInicial();
   void SetIndiceInicial(int);
   T& operator[](int);
   int size();

 private:
   std::vector<T> myvector_;
   int indice_inicial_;
   int size_;
};

#include "myvector.cc"

#endif