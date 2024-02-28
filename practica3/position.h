#ifndef position_h
#define position_h

#include <vector>
#include <stdexcept>
#include <cstdarg>

typedef int Coor_t;

class Position {
 public:
  Position () = default;
// Operador de acceso a la i-ésima coordenada
  virtual Coor_t operator[](unsigned int) const = 0;
};

template <int Dim=2, class Coordinate_t=int>
class PositionDim: public Position {
 private:
   Coor_t Coordinates[Dim];
 public:
// Constructor con lista variable de parámetros
  PositionDim(int sz, ...) {
    va_list vl;
    va_start(vl, sz);
    for(int d=0; d<Dim; d++) {
      Coordinates[d] = va_arg(vl, Coor_t);
    }
    va_end(vl);
  }

   Coor_t operator[](unsigned int index) const {
    if (index >= Dim) {
      throw std::out_of_range("Index out of range");
    }
    return Coordinates[index];
   }
};
/*
template <class Coordinate_t>
class PositionDim<1, Coordinate_t>: public Position {
 private:
   Coor_t Coordinates[1];
 public:
  PositionDim(int sz, ...) {
    va_list vl;
    va_start(vl, sz);
    Coordinates[0] = va_arg(vl, Coor_t);
    va_end(vl);
  }

  Coor_t operator[](unsigned int) const {
    if (0 >= 1) {
      throw std::out_of_range("Index out of range");
    }
    return Coordinates[0];
  }
};
*/
#endif