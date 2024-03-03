#ifndef latice1d_h
#define latice1d_h
#include "latice.h"
#include "celula.h"
#include <vector>
#include "factorycell.h"
#include <termios.h>
#include <unistd.h>
#include <limits>

class Latice;
class Celula;

class Latice1d : public Latice {
 public:
  Latice1d(std::string, FactoryCelula&);
  Latice1d(int, FactoryCelula&);
  //Celula& operator[](int );
  void PrintInstrucciones();

 protected:
  std::vector<Celula*> latice_; ///< Vector que almacena las células de la red.
};

class latice1d_open0 : public Latice1d {
 public:
  using Latice1d::Latice1d;
  void nextGeneration();
  std::size_t Population();
  Celula& operator[](const Position&);
  std::ostream& display(std::ostream& os);

};

class latice1d_open1 : public Latice1d {
 public:
  using Latice1d::Latice1d;
  void nextGeneration();
  std::size_t Population();
  Celula& operator[](const Position& );
  std::ostream& display(std::ostream& os);
};

class latice1d_periodic : public Latice1d {
 public:
  using Latice1d::Latice1d;
  void nextGeneration();
  std::size_t Population();
  Celula& operator[](const Position& );
  std::ostream& display(std::ostream& os);
};






#endif