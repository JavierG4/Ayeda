#include "posicion.h"

  Posicion::Posicion(const std::vector<int>& posiciones) {
    if (posiciones.size() != N) {
      throw std::invalid_argument("Número incorrecto de posiciones");
    }
    posiciones_ = posiciones;
  }

  int Position::GetPosicion(size_t dimension) {
    if (dimension >= N) {
      throw std::out_of_range("Dimensión fuera de rango");
     }
     return posiciones_[dimension];
  }