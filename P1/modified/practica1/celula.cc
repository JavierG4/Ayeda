
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
  int izquierda, derecha, central, izquierdax2, derechax2;
  int contador0 = 0;
  int contador1 = 0;
  int siguiente = 0;
  int flag = 0;
  //std::cout << "Si " << std::endl;
  //std::cout << "posicion: " << GetPosicion().GetPosicion() << std::endl;
  if (reticula.GetFrontera() == 1 || reticula.GetFrontera() == 0) {
    izquierda = reticula[GetPosicion().GetPosicion() - 1].GetEstado().GetEstado();
    derecha = reticula[GetPosicion().GetPosicion() + 1].GetEstado().GetEstado();
    central = GetEstado().GetEstado();
    izquierdax2 = reticula[reticula.GetNumCelula() - 2].GetEstado().GetEstado();
    derechax2 = reticula[GetPosicion().GetPosicion() + 2].GetEstado().GetEstado();
    siguiente = derecha + derechax2 + central + izquierda + izquierdax2;
    if ( siguiente <= 2 ) {
      flag = 0;
    } else {
      flag = 1;
    }
    return flag;
  } else {
    if (GetPosicion().GetPosicion() == 0) {
      derecha = reticula[GetPosicion().GetPosicion() + 1].GetEstado().GetEstado();
      derechax2 = reticula[GetPosicion().GetPosicion() + 2].GetEstado().GetEstado();
      central = GetEstado().GetEstado();
      izquierda = reticula[reticula.GetNumCelula() - 1].GetEstado().GetEstado();
      izquierdax2 = reticula[reticula.GetNumCelula() - 2].GetEstado().GetEstado();
      siguiente = derecha + derechax2 + central + izquierda + izquierdax2;
    if ( siguiente <= 2 ) {
      flag = 0;
    } else {
      flag = 1;
    }
    return flag;
    } else if (GetPosicion().GetPosicion() == reticula.GetNumCelula() - 1) {
      izquierda = reticula[GetPosicion().GetPosicion() - 1].GetEstado().GetEstado();
      izquierdax2 = reticula[GetPosicion().GetPosicion() - 2].GetEstado().GetEstado();
      derecha = reticula[0].GetEstado().GetEstado();
      derechax2 = reticula[1].GetEstado().GetEstado();
      central = GetEstado().GetEstado();
      siguiente = derecha + derechax2 + central + izquierda + izquierdax2;
      if ( siguiente <= 2 ) {
        flag = 0;
      } else {
        flag = 1;
      }
      return flag;
    } else {
      izquierda = reticula[GetPosicion().GetPosicion() - 1].GetEstado().GetEstado();
      derechax2 = reticula[GetPosicion().GetPosicion() + 1].GetEstado().GetEstado();
      izquierdax2 = reticula[GetPosicion().GetPosicion() - 2].GetEstado().GetEstado();
      derecha = reticula[GetPosicion().GetPosicion() + 2].GetEstado().GetEstado();
      central = GetEstado().GetEstado();
      siguiente = derecha + derechax2 + central + izquierda + izquierdax2;
      if ( siguiente <= 2 ) {
        flag = 0;
      } else {
        flag = 1;
      }
      return flag;
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

