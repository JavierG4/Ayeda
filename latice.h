#ifndef latice_h
#define latice_h

#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <utility>
#include <set>
#include <vector>
#include "celula.h"

class Celula;

class Latice {
 public:
   Latice(int n);
   ~Latice();
   int GetNumCelula(int i);
   int GetFrontera();
   void NextGeneration();
   /* En el primer recorrido cada célula accede a su vecindad y aplica la función
   de transición para calcular su estado siguiente.
   En el segundo recorrido cada célula actualiza su estado.*/
   //friend ostream& operator<<(ostream&, const Lattice&);
   void PrintLatice();
 private:
   Celula *latice_;
   int numero_celulas_;
   int frontera_; // 0 = abierta fria, 1 = abierta caliente, 2 = periódica
};

#endif 