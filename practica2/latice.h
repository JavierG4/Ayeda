#ifndef latice_h
#define latice_h

#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <utility>
#include <set>
#include <vector>
#include "myvector.h"
#include "celula.h"
#include "matriz.h"

class Celula;

class Latice {
 public:
   Latice(int,int,int);
   Latice(std::string,int);
   ~Latice();
   int GetNumCelula();
   int GetFrontera();
   void NextGeneration();
   //Celula& operator[](int);
   std::size_t Population();
   int PreguntarEstado(int,int);
   void Comprobar();
   /* En el primer recorrido cada célula accede a su vecindad y aplica la función
   de transición para calcular su estado siguiente.
   En el segundo recorrido cada célula actualiza su estado.*/
   //friend ostream& operator<<(ostream&, const Lattice&);
   Matriz GetMatriz();
   void PrintInstrucciones();
   void PrintLatice();
   bool Alrededor(int);
 private:
   Matriz latice_;
   int numero_celulas_;
   int frontera_; // 0 = abierta fria, 1 = abierta caliente, 2 = periódica
};

#endif 