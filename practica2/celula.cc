
#include "celula.h"
#include "latice.h"

Celula::Celula(const Posicion& pos, const Estado& estado = Estado()) {
  pos_ = pos;
  estado_ = estado;
  estado_siguiente_ = estado;
}

Estado Celula::GetEstado() const {
  return estado_;
}

Estado Celula::GetEstadoSiguinte() const {
  return estado_siguiente_;
}

void Celula::SetEstado(Estado estado) {
  estado_ = estado;
}

void Celula::UpdateState() {
  estado_ = estado_siguiente_;
}

Posicion Celula::GetPosicion() const {
  return pos_;
}

Celula::Celula() {
  pos_ = Posicion();
  estado_ = Estado();
  estado_siguiente_ = Estado();
}

void Celula::SetEstadoSiguiente(Estado estado) {
  estado_siguiente_ = estado;
}



int Celula::NextState(Latice& reticula) {
  int posx = GetPosicion().GetPosicionX();
  int posy = GetPosicion().GetPosicionY();
  int contador = 0;
  contador += reticula[Posicion(posx - 1, posy - 1)].GetEstado().GetEstado();
  contador += reticula[Posicion(posx - 1, posy)].GetEstado().GetEstado();
  contador += reticula[Posicion(posx - 1, posy + 1)].GetEstado().GetEstado();
  contador += reticula[Posicion(posx, posy - 1)].GetEstado().GetEstado();
  contador += reticula[Posicion(posx, posy + 1)].GetEstado().GetEstado();
  contador += reticula[Posicion(posx + 1, posy - 1)].GetEstado().GetEstado();
  contador += reticula[Posicion(posx + 1, posy)].GetEstado().GetEstado();
  contador += reticula[Posicion(posx + 1, posy + 1)].GetEstado().GetEstado();
  if (GetEstado().GetEstado() == 0) {
    if (contador == 3) {
      return 1;
    } else {
      return 0;
    }
  } else {
    if (contador == 2 || contador == 3) {
      return 1;
    } else {
      return 0;
    }
  }
}
/* 
x x(0,1) x (0 ,2)
x x(1,1) x (1,2)
x x(2,1) x(2,2)
*/