#ifndef latice2d_h
#define latice2d_h

#include "latice.h"
#include "factorycell.h"
#include <iostream>
#include <string>
#include <vector>
#include "celula.h"
#include "myvector.h"
#include "matriz.h"

class Latice;
class Celula;

class Latice2d : public Latice {
 public:
  Latice2d(std::string, const FactoryCelula&);

 protected:
  Matriz latice_;
};

class latice2d_reflective : public Latice2d {
 public:
  using Latice2d::Latice2d;
  void nextGeneration();
  std::size_t Population();
  Celula& operator[](const Position&);
  std::ostream& display(std::ostream& os) override {
    // Implement the function here.
    // This is just a placeholder implementation.
    os << "latice1d_open0";
    return os;
  }
};

class latice2d_periodic : public Latice2d {
 public:
  using Latice2d::Latice2d;
  void nextGeneration();
  std::size_t Population();
  Celula& operator[](const Position&);
};

class latice2d_open0 : public Latice2d {
 public:
  using Latice2d::Latice2d;
  void nextGeneration();
  std::size_t Population();
  Celula& operator[](const Position&);
};

class latice2d_open1 : public Latice2d {
 public:
  using Latice2d::Latice2d;
  void nextGeneration();
  std::size_t Population();
  Celula& operator[](const Position&);
};
/*
class latice2d_noborder : public Latice2d {
 public:
  using Latice2d::Latice2d;
  void nextGeneration();
  std::size_t Population();
  Celula& operator[](const Position&);
};

*/

#endif