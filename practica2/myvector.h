#ifndef myvector_h
#define myvector_h

#include <iostream>
#include "celula.h"
#include <vector>

class Myvector {
 public:
   Myvector(Celula*, int, int);
   Myvector(int);
   Myvector();
   void push_back(Celula*);
   void push_front(Celula*);
   void SetCelula(int, Celula*);
   Celula* GetCelula(int);
   int GetIndiceInicial();
   void SetIndiceInicial(int);
   Celula*& operator[](int);
   int size();

 private:
   std::vector<Celula*> myvector_;
   int indice_inicial_;
   int size_;
};

#endif