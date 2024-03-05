#include "celulace.h"

int CelulaAce110::NextState(Latice& latice) {
  int vecinos = 0;
  int posx = (*GetPosition())[0];
  int central = GetEstado().GetEstado();
  int izquierda = latice[PositionDim<1>(1,posx - 2)].GetEstado().GetEstado();
  int derecha = latice[PositionDim<1>(1,posx - 1)].GetEstado().GetEstado();
  vecinos = (central + derecha + central * derecha + izquierda * central * derecha) % 2;
  return vecinos;
}

void CelulaAce110::UpdateState() {
  estado_ = estado_siguiente_;
}

int CelulaAce30::NextState(Latice& latice) {
  int vecinos = 0;
  int posx = (*GetPosition())[0];
  int central = GetEstado().GetEstado();
  int izquierda = latice[PositionDim<1>(1,posx - 1)].GetEstado().GetEstado();
  int derecha = latice[PositionDim<1>(1,posx + 1)].GetEstado().GetEstado();
  vecinos = (izquierda + central + derecha + central * derecha) % 2;
  return vecinos;
}

void CelulaAce30::UpdateState() {
  estado_ = estado_siguiente_;
}