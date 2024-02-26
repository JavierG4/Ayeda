
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

int Celula::NextState(Latice& reticula) {
  int izquierda, derecha, central;
  int siguiente;
  if (reticula.GetFrontera() == 1 || reticula.GetFrontera() == 0) {
    izquierda = reticula[GetPosicion().GetPosicion() - 1].GetEstado().GetEstado();
    derecha = reticula[GetPosicion().GetPosicion() + 1].GetEstado().GetEstado();
    central = GetEstado().GetEstado();
    siguiente = (central + derecha + central * derecha + izquierda * central * derecha) % 2;
    return siguiente;
  } else {
    if (GetPosicion().GetPosicion() == 0) {
      derecha = reticula[GetPosicion().GetPosicion() + 1].GetEstado().GetEstado();
      central = GetEstado().GetEstado();
      izquierda = reticula[reticula.GetNumCelula() - 1].GetEstado().GetEstado();
      siguiente = (central + derecha + central * derecha + izquierda * central * derecha) % 2;
      return siguiente;
    } else if (GetPosicion().GetPosicion() == reticula.GetNumCelula() - 1) {
      izquierda = reticula[GetPosicion().GetPosicion() - 1].GetEstado().GetEstado();
      derecha = reticula[0].GetEstado().GetEstado();
      central = GetEstado().GetEstado();
      siguiente = (central + derecha + central * derecha + izquierda * central * derecha) % 2;
      return siguiente;
    } else {
      izquierda = reticula[GetPosicion().GetPosicion() - 1].GetEstado().GetEstado();
      derecha = reticula[GetPosicion().GetPosicion() + 1].GetEstado().GetEstado();
      central = GetEstado().GetEstado();
      siguiente = (central + derecha + central * derecha + izquierda * central * derecha) % 2;
      return siguiente;
    }
  }
}

std::ostream& operator<<(std::ostream& os, const Celula& cell) {
  if (cell.GetEstado().GetEstado() == 0) {
    os << " ";
  } else {
    os << "X";
  }
  return os;
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

