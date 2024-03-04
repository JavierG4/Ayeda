#include "celula.h"
#include "latice.h"

Celula::Celula(Position& pos, const Estado& estado = Estado()) {
  pos_ = pos.clone();
  estado_ = estado;
  estado_siguiente_ = estado;
}

Celula::~Celula() {
  delete pos_;
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

Position* Celula::GetPosition() const {
  return pos_;
}


void Celula::SetEstadoSiguiente(Estado estado) {
  estado_siguiente_ = estado;
}
