#include "celula.h"

Celula::Celula(const Posicion& pos, const Estado& estado) {
  pos_ = pos;
  estado_ = estado;
}

Estado Celula::getEstado() const {
  return estado_;
}

void Celula::SetEstado(Estado estado) {
  estado_ = estado;
}

void Celula::updateState() {

}

ostream& operator<<(ostream& os, const Celula& cell) {
  //os << cell.getEstado();
  //return os;
}

Posicion Celula::getPosicion() const {
  return pos_;
}

