#include "posicion.h"

Posicion::Posicion(int posicion){
  posicion_ = posicion;
}

Posicion::Posicion() {
  posicion_ = 0;
}

int Posicion::GetPosicion() {
  return posicion_;
}