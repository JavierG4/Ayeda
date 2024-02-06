#include "celula.h"

Celula::Celula(const Posicion& pos, const Estado& estado = Estado()) {
  pos_ = pos;
  estado_ = estado;
}

Estado Celula::GetEstado() const {
  return estado_;
}

Estado Celula::GetEstadoSiguinte() const {

}

void Celula::SetEstado(Estado estado) {
  estado_ = estado;
}

void Celula::UpdateState() {

}

void Celula::NextState(const Latice& reticuki)

ostream& operator<<(ostream& os, const Celula& cell) {
  //os << cell.getEstado();
  //return os;
}

Posicion Celula::getPosicion() const {
  return pos_;
}

