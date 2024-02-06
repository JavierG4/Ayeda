#include "celula.h"

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

}

int Celula::NextState(const Latice& reticula) {
  return 0;
}

//ostream& operator<<(ostream& os, const Celula& cell) {
  //os << cell.getEstado();
  //return os;
//}

Posicion Celula::GetPosicion() const {
  return pos_;
}

Celula::Celula() {
  pos_ = Posicion();
  estado_ = Estado();
  estado_siguiente_ = Estado();
}

