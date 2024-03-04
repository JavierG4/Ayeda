#ifndef celulace_h
#define celulace_h

#include "celula.h"
#include "position.h"
#include "estado.h"
#include <iostream>
#include "latice.h"

class Latice;
class Celula;

class CelulaAce : public Celula {
 public:
  //CelulaAce(const Position& pos, const Estado& estado) : Celula(pos, estado) {}
  using Celula::Celula;
};


class CelulaAce110 : public CelulaAce {
 public:
  //CelulaAce110(const Position& pos, const Estado& estado) : CelulaAce(pos, estado) {}
  using CelulaAce::CelulaAce;
  int NextState(Latice& latice);
  void UpdateState();
};

class CelulaAce30 : public CelulaAce {
 public:
  //CelulaAce30(const Position& pos, const Estado& estado) : CelulaAce(pos, estado) {}
  using CelulaAce::CelulaAce;
  int NextState(Latice& latice);
  void UpdateState();
};






#endif
