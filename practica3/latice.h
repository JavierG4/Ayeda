#ifndef latice_h
#define latice_h

#include <iostream>
/*
#include <stdlib.h>
#include <fstream>
#include <utility>
#include <set>
#include <vector>
#include "myvector.h"
#include "celula.h"
#include "matriz.h"
#include "factorycell.h"
#include "position.h"
#include "estado.h"



class Celula;
/*
/**
 * @brief Clase que representa una red de células.
 */
class Latice {
 public:
  //Latice(std::string, const FactoryCelula&);
  virtual void Latice::nextGeneration() = 0;
  virtual std::size_t Latice::Population() const = 0;
  virtual ostream& Latice::display(ostream&) = 0;
  friend std::ostream& operator<<(std::ostream&, const Latice&);
};

#endif 