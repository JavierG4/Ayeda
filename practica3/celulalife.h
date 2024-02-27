#ifndef celulaLife_h
#define celulaLife_h


#include "celula.h"
#include "position.h"
#include "estado.h"
#include <iostream>
#include "latice.h"


class Latice;
class Celula;

class CelulaLife : public Celula {
 public:
  //CelulaLife(const Position& pos, const Estado& estado) : Celula(pos, estado) {}
  using Celula::Celula;
};

class CelulaLife23_3 : public CelulaLife {
 public:
  //CelulaLife23_3(const Position& pos, const Estado& estado) : CelulaLife(pos, estado) {}
  using CelulaLife::CelulaLife;
  int NextState(Latice& latice);
  void UpdateState();
};

class CelulaLife51_346 : public CelulaLife {
 public:
  //CelulaLife51_346(const Position& pos, const Estado& estado) : CelulaLife(pos, estado) {}
  using CelulaLife::CelulaLife;
  int NextState(Latice& latice);
  void UpdateState();
};










#endif