#ifndef latice1d_h
#define latice1d_h
#include "latice.h"
#include "celula.h"
#include <vector>
#include "factorycell.h"

class Latice;
class Celula;

class Latice1d : public Latice {
 public:
  Latice1d(std::string, const FactoryCelula&);
  //Celula& operator[](int );

 protected:
  std::vector<Celula*> latice_; ///< Vector que almacena las células de la red.
};

class latice1d_open0 : public Latice1d {
 public:
  using Latice1d::Latice1d;
  void nextGeneration();
  std::size_t Population() const;
  Celula& operator[](int );
};

class latice1d_open1 : public Latice1d {
 public:
  using Latice1d::Latice1d;
  void nextGeneration();
  std::size_t Population() const;
  Celula& operator[](int );
};

class latice1d_periodic : public Latice1d {
 public:
  using Latice1d::Latice1d;
  void nextGeneration();
  std::size_t Population() const;
  Celula& operator[](int );
};






#endif