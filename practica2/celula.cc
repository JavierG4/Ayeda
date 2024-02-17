
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

void Celula::SetEstadoSiguiente(Estado estado) {
  estado_siguiente_ = estado;
}



int Celula::NextState(Latice& reticula) {
  if (reticula.GetFrontera() == 0 ||reticula.GetFrontera() == 1) {
    int arriba = reticula.GetMatriz()[GetPosicion().GetPosicionX() - 1][GetPosicion().GetPosicionY()]->GetEstado().GetEstado();
    int abajo = reticula.GetMatriz()[GetPosicion().GetPosicionX() + 1][GetPosicion().GetPosicionY()]->GetEstado().GetEstado();
    int derecha = reticula.GetMatriz()[GetPosicion().GetPosicionX() ][GetPosicion().GetPosicionY() + 1]->GetEstado().GetEstado();
    int izquierda = reticula.GetMatriz()[GetPosicion().GetPosicionX()][GetPosicion().GetPosicionY() - 1]->GetEstado().GetEstado();
    int arriba_derecha = reticula.GetMatriz()[GetPosicion().GetPosicionX() - 1][GetPosicion().GetPosicionY()]->GetEstado().GetEstado();
    int arriba_izquierda = reticula.GetMatriz()[GetPosicion().GetPosicionX() - 1][GetPosicion().GetPosicionY() + 1]->GetEstado().GetEstado();
    int abajo_derecha = reticula.GetMatriz()[GetPosicion().GetPosicionX() + 1][GetPosicion().GetPosicionY() + 1]->GetEstado().GetEstado();
    int abajo_izquierda = reticula.GetMatriz()[GetPosicion().GetPosicionX() + 1][GetPosicion().GetPosicionY() - 1]->GetEstado().GetEstado();
    int total = arriba + abajo + derecha + izquierda;
    total += arriba_derecha + arriba_izquierda + abajo_derecha + abajo_izquierda;
    if ( total == 2 || total == 3) {
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