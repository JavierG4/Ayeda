#ifndef celulace_h
#define celulace_h

#include <celula.h>
#include <position.h>
#include <Estado.h>
#include <iostream>
#include "latice.h"

class Latice;


class CelulaAce : public Celula {
 public:
  CelulaCe(const Position& pos, const Estado& estado) : Celula(pos, estado) {}
};


class CelulaAce110 : public CelulaAce {
 public:
  CelulaAce110(const Position& pos, const Estado& estado) : CelulAce(pos, estado) {}
  int NextState(Latice& latice);
  void UpdateState();
};

class CelulaAce30 : public CelulaAce {
 public:
  CelulaAce30(const Position& pos, const Estado& estado) : CelulAce(pos, estado) {}
  int NextState(Latice& latice);
  void UpdateState();
};






#endif
