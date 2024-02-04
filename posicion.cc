#include "posicion.h"

Posicion::Posicion(int x, int y, int z) {
  vecindad.push_back(x);
  vecindad.push_back(y);
  vecindad.push_back(z);
}

Posicion::Posicion() {
  vecindad.push_back(0);
  vecindad.push_back(0);
  vecindad.push_back(0);
}

std::vector<int> Posicion::GetVecindad() const {
  return vecindad;
}