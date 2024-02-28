#include "celulace.h"

CelulaAce110::NextState(Latice& latice) {
  int vecinos = 0;
  int posx = (*GetPosition())[0];
  int central = GetEstado().GetEstado();
  int izquierda = latice[posx - 1].GetEstado().GetEstado();
  int derecha = latice[posx + 1].GetEstado().GetEstado();
  vecinos = (central + derecha + central * derecha + izquierda * central * derecha) % 2;
  return vecinos;
}

CelulaAce110::UpdateState() {
  estado_ = estado_siguiente_;
}

CelulaAce30::NextState(Latice& latice) {
  int vecinos = 0;
  int posx = (*GetPosition())[0];
  int central = GetEstado().GetEstado();
  int izquierda = latice[posx - 1].GetEstado().GetEstado();
  int derecha = latice[posx + 1].GetEstado().GetEstado();
  vecinos = (izquierda + central + derecha + central * derecha) % 2;
  return vecinos;
}

CelulaAce30::UpdateState() {
  estado_ = estado_siguiente_;
}