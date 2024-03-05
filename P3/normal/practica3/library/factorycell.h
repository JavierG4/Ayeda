#ifndef factorycell_h
#define factorycell_h

#include "celula.h"
#include "position.h"
#include "estado.h"
#include <iostream>
#include "celulace.h"
#include "celulalife.h"

class FactoryCelula {
 public:
  // Método creador de células
  virtual Celula* createCelula( Position&, const Estado&)  = 0;
};

// Replicar para cada tipo de célula
class FactoryCelulaAce110: public FactoryCelula {
 public:
  Celula* createCelula( Position& p, const Estado& s)  {
    return new CelulaAce110(p, s);
  }
};

class FactoryCelulaAce30: public FactoryCelula {
 public:
  Celula* createCelula( Position& p, const Estado& s)  {
    return new CelulaAce30(p, s);
  }
};

class FactoryCelulaLife23_3: public FactoryCelula {
 public:
  Celula* createCelula( Position& p, const Estado& s)  {
    return new CelulaLife23_3(p, s);
  }
};

class FactoryCelulaLife51_346: public FactoryCelula {
 public:
  Celula* createCelula(Position& p, const Estado& s)  {
    return new CelulaLife51_346(p, s);
  }
};


#endif