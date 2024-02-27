#include "celula.h"
#include "position.h"
#include "Estado.h"
#include <iostream>
#include "celulace.h"
#include "celulalife.h"

class FactoryCelula {
 public:
  // Método creador de células
  virtual Celula* createCelula(const Position&, const Estado&) const = 0;
};

// Replicar para cada tipo de célula
class FactoryCelulaAce110: public FactoryCelula {
 public:
  Celula* createCelula(const Position& p, const Estado& s) const {
    return new CelulaAce110(p, s);
  }
};

class FactoryCelulaAce30: public FactoryCelula {
 public:
  Celula* createCelula(const Position& p, const Estado& s) const {
    return new CelulaAce110(p, s);
  }
};

class FactoryCelulaAce23_3: public FactoryCelula {
 public:
  Celula* createCelula(const Position& p, const Estado& s) const {
    return new CelulaLife23_3(p, s);
  }
};

class FactoryCelulaAce51_346: public FactoryCelula {
 public:
  Celula* createCelula(const Position& p, const Estado& s) const {
    return new CelulaLife51_346(p, s);
  }
};
