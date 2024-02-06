#ifndef celula_h
#define celula_h

#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string.h>
#include <utility>
#include <set>
#include <vector>
#include "estado.h"
#include "posicion.h"

class Latice;

class Celula {
 public:
  Celula(const Posicion&, const Estado&);
  Celula();
  Estado GetEstado() const;
  void SetEstado(Estado);
  void SetEstadoSiguiente(Estado);
  int NextState(const Latice&);
  void UpdateState(); // Preguntar si es necesario y como usarla
  Posicion GetPosicion() const;
  Estado GetEstadoSiguinte() const;

  //ostream& operator<<(ostream&, const Cell&);

 private:
   //Latice latice_;
   Estado estado_;
   Posicion pos_;
   Estado estado_siguiente_;
   //Una función de transición local
};


#endif 