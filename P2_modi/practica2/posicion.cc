#include "posicion.h"

Posicion::Posicion(int posicionx, int posiciony) {
  posicion_x_ = posicionx;
  posicion_y_ = posiciony;
}

Posicion::Posicion() {
  posicion_x_ = 0;
  posicion_y_ = 0;
}

int Posicion::GetPosicionX() {
  return posicion_x_;
}

int Posicion::GetPosicionY() {
  return posicion_y_;
}