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
  estado_ = estado_siguiente_;
}

int Celula::NextState(const Latice& reticula) {
  if ( GetPosicion().GetPosicion() == 0 ) { 
    int izquierda = 0;
    int derecha = reticula[GetPosicion().GetPosicion() + 1].GetEstado().GetEstado();;
    int central = GetEstado().GetEstado();
    if ( reticula.GetFrontera() == 0 ){ // Abierta fria
      izquierda = 0;
    } 
    else if (reticula.GetFrontera() == 1) { // Abierta caliente
      izquierda = 1;
    } 
    else { // periodica
      izquierda = reticula[reticula.GetNumCelulas() - 1].GetEstado().GetEstado();
    }
    int siguiente = (central + derecha + central * derecha + izquierda * central * derecha) % 2;
    return siguiente;   
  } 
  else if ( GetPosicion().GetPosicion() == reticula.GetNumCelulas() - 1) {
    int izquierda = reticula[GetPosicion().GetPosicion() - 1].GetEstado().GetEstado();
    int derecha = 0;
    int central = GetEstado().GetEstado();
    if ( reticula.GetFrontera() == 0 ){
      derecha = 0;
    } 
    else if (reticula.GetFrontera() == 1) {
      derecha = 1;
    } 
    else {
      derecha = reticula[0].GetEstado().GetEstado();
    }
    int siguiente = (central + derecha + central * derecha + izquierda * central * derecha) % 2;
    return siguiente;
  } 
  else {
    int izquierda = reticula[GetPosicion().GetPosicion() - 1].GetEstado().GetEstado();
    int derecha = reticula[GetPosicion().GetPosicion() + 1].GetEstado().GetEstado();
    int central = GetEstado().GetEstado();
    // 
    int siguiente = (central + derecha + central * derecha + izquierda * central * derecha) % 2;
    return siguiente;
  }
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
