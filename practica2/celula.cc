
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
  int posx = GetPosicion().GetPosicionX();
  int posy = GetPosicion().GetPosicionY();
  if (reticula.GetFrontera() == 0 ||reticula.GetFrontera() == 1) {
    int arriba = reticula.GetMatriz()[posx - 1][posy]->GetEstado().GetEstado();
    int abajo = reticula.GetMatriz()[posx + 1][posy]->GetEstado().GetEstado();
    int derecha = reticula.GetMatriz()[posx ][posy + 1]->GetEstado().GetEstado();
    int izquierda = reticula.GetMatriz()[posx][posy - 1]->GetEstado().GetEstado();
    int arriba_derecha = reticula.GetMatriz()[posx - 1][posy + 1]->GetEstado().GetEstado();
    int arriba_izquierda = reticula.GetMatriz()[posx - 1][posy - 1]->GetEstado().GetEstado();
    int abajo_derecha = reticula.GetMatriz()[posx + 1][posy + 1]->GetEstado().GetEstado();
    int abajo_izquierda = reticula.GetMatriz()[posx + 1][posy - 1]->GetEstado().GetEstado();
    int total = arriba + abajo + derecha + izquierda;
    //total += arriba_derecha + arriba_izquierda + abajo_derecha + abajo_izquierda;
    //std::cout << total << " " << posx << posy << std::endl;
    if ( total == 2 || total == 3) {
      return 1;
    } else {
      return 0;
    }
  } else if (reticula.GetFrontera() == 2) {
    if ( posx == 0 ) { // posicion (0,0) que iria a la (n,m)
    }
  } else if ( reticula.GetFrontera() == 3 ) {
    if (posx == 0 && posy == 0) { // (0,0)
      int arriba = GetEstado().GetEstado();
      int abajo = reticula.GetMatriz()[posx + 1][posy]->GetEstado().GetEstado();
      int derecha = reticula.GetMatriz()[posx ][posy + 1]->GetEstado().GetEstado();
      int izquierda = GetEstado().GetEstado();
      int arriba_derecha = reticula.GetMatriz()[posx ][posy + 1]->GetEstado().GetEstado();
      int arriba_izquierda = GetEstado().GetEstado();
      int abajo_derecha = reticula.GetMatriz()[posx + 1][posy + 1]->GetEstado().GetEstado();
      int abajo_izquierda = reticula.GetMatriz()[posx + 1][posy]->GetEstado().GetEstado();
      int total = arriba + abajo + derecha + izquierda;
      total += arriba_derecha + arriba_izquierda + abajo_derecha + abajo_izquierda;
      //std::cout << total << " " << posx << posy << std::endl;
      if ( total == 2 || total == 3) {
        return 1;
      } else {
        return 0;
      }
    } else if (posx == 0 && posy == reticula.GetMatriz().GetColumnas() - 1) {
      int arriba = GetEstado().GetEstado();
      int abajo = reticula.GetMatriz()[posx + 1][posy]->GetEstado().GetEstado();
      int derecha = GetEstado().GetEstado();
      int izquierda = reticula.GetMatriz()[posx][posy - 1]->GetEstado().GetEstado();
      int arriba_derecha = GetEstado().GetEstado();
      int arriba_izquierda = reticula.GetMatriz()[posx][posy - 1]->GetEstado().GetEstado();
      int abajo_derecha = reticula.GetMatriz()[posx + 1][posy]->GetEstado().GetEstado();
      int abajo_izquierda = reticula.GetMatriz()[posx + 1][posy - 1]->GetEstado().GetEstado();
      int total = arriba + abajo + derecha + izquierda;
      total += arriba_derecha + arriba_izquierda + abajo_derecha + abajo_izquierda;
      //std::cout << total << " " << posx << posy << std::endl;
      if ( total == 2 || total == 3) {
        return 1;
      } else {
        return 0;
      }
    } else if (posx == reticula.GetMatriz().GetFilas() - 1 && posy == 0) {
      int arriba = reticula.GetMatriz()[posx - 1][posy]->GetEstado().GetEstado();
      int abajo = GetEstado().GetEstado();
      int derecha = reticula.GetMatriz()[posx ][posy + 1]->GetEstado().GetEstado();
      int izquierda = GetEstado().GetEstado();
      int arriba_derecha = reticula.GetMatriz()[posx -1][posy + 1]->GetEstado().GetEstado();
      int arriba_izquierda = reticula.GetMatriz()[posx - 1][posy]->GetEstado().GetEstado();
      int abajo_derecha =  reticula.GetMatriz()[posx ][posy + 1]->GetEstado().GetEstado();
      int abajo_izquierda = GetEstado().GetEstado();
      int total = arriba + abajo + derecha + izquierda;
      total += arriba_derecha + arriba_izquierda + abajo_derecha + abajo_izquierda;
      //std::cout << total << " " << posx << posy << std::endl;
      if ( total == 2 || total == 3) {
        return 1;
      } else {
        return 0;
      }
    } else if (posx == reticula.GetMatriz().GetFilas() - 1 && posy == reticula.GetMatriz().GetColumnas() - 1) {
      int arriba = reticula.GetMatriz()[posx - 1][posy]->GetEstado().GetEstado();
      int abajo = GetEstado().GetEstado();
      int derecha = GetEstado().GetEstado();
      int izquierda = reticula.GetMatriz()[posx][posy - 1]->GetEstado().GetEstado();
      int arriba_derecha = reticula.GetMatriz()[posx - 1][posy]->GetEstado().GetEstado();
      int arriba_izquierda = reticula.GetMatriz()[posx - 1][posy - 1]->GetEstado().GetEstado();
      int abajo_derecha = GetEstado().GetEstado();
      int abajo_izquierda = reticula.GetMatriz()[posx][posy - 1]->GetEstado().GetEstado();
      int total = arriba + abajo + derecha + izquierda;
      total += arriba_derecha + arriba_izquierda + abajo_derecha + abajo_izquierda;
      //std::cout << total << " " << posx << posy << std::endl;
      if ( total == 2 || total == 3) {
        return 1;
      } else {
        return 0;
      }
    } else if (posx == 0) {
      int arriba = GetEstado().GetEstado();
      int abajo = reticula.GetMatriz()[posx + 1][posy]->GetEstado().GetEstado();
      int derecha = reticula.GetMatriz()[posx ][posy + 1]->GetEstado().GetEstado();
      int izquierda = reticula.GetMatriz()[posx][posy - 1]->GetEstado().GetEstado();
      int arriba_derecha = reticula.GetMatriz()[posx ][posy + 1]->GetEstado().GetEstado();
      int arriba_izquierda = reticula.GetMatriz()[posx][posy - 1]->GetEstado().GetEstado();
      int abajo_derecha = reticula.GetMatriz()[posx + 1][posy + 1]->GetEstado().GetEstado();
      int abajo_izquierda = reticula.GetMatriz()[posx + 1][posy - 1]->GetEstado().GetEstado();
      int total = arriba + abajo + derecha + izquierda;
      total += arriba_derecha + arriba_izquierda + abajo_derecha + abajo_izquierda;
      //std::cout << total << " " << posx << posy << std::endl;
      if ( total == 2 || total == 3) {
        return 1;
      } else {
        return 0;
      }
    } else if (posx == reticula.GetMatriz().GetFilas() - 1) {
      int arriba = reticula.GetMatriz()[posx - 1][posy]->GetEstado().GetEstado();
      int abajo = GetEstado().GetEstado();
      int derecha = reticula.GetMatriz()[posx ][posy + 1]->GetEstado().GetEstado();
      int izquierda = reticula.GetMatriz()[posx][posy - 1]->GetEstado().GetEstado();
      int arriba_derecha = reticula.GetMatriz()[posx - 1][posy + 1]->GetEstado().GetEstado();
      int arriba_izquierda = reticula.GetMatriz()[posx - 1][posy - 1]->GetEstado().GetEstado();
      int abajo_derecha = reticula.GetMatriz()[posx ][posy + 1]->GetEstado().GetEstado();
      int abajo_izquierda = reticula.GetMatriz()[posx][posy - 1]->GetEstado().GetEstado();
      int total = arriba + abajo + derecha + izquierda;
      total += arriba_derecha + arriba_izquierda + abajo_derecha + abajo_izquierda;
      //std::cout << total << " " << posx << posy << std::endl;
      if ( total == 2 || total == 3) {
        return 1;
      } else {
        return 0;
      }
    } else if (posy == 0) {
      int arriba = reticula.GetMatriz()[posx - 1][posy]->GetEstado().GetEstado();
      int abajo = reticula.GetMatriz()[posx + 1][posy]->GetEstado().GetEstado();
      int derecha = reticula.GetMatriz()[posx ][posy + 1]->GetEstado().GetEstado();
      int izquierda = GetEstado().GetEstado();
      int arriba_derecha = reticula.GetMatriz()[posx - 1][posy + 1]->GetEstado().GetEstado();
      int arriba_izquierda = reticula.GetMatriz()[posx - 1][posy]->GetEstado().GetEstado();
      int abajo_derecha = reticula.GetMatriz()[posx + 1][posy + 1]->GetEstado().GetEstado();
      int abajo_izquierda = reticula.GetMatriz()[posx + 1][posy]->GetEstado().GetEstado();
      int total = arriba + abajo + derecha + izquierda;
      total += arriba_derecha + arriba_izquierda + abajo_derecha + abajo_izquierda;
      //std::cout << total << " " << posx << posy << std::endl;
      if ( total == 2 || total == 3) {
        return 1;
      } else {
        return 0;
      }
    } else if (posy == reticula.GetMatriz().GetColumnas() - 1) {
      int arriba = reticula.GetMatriz()[posx - 1][posy]->GetEstado().GetEstado();
      int abajo = reticula.GetMatriz()[posx + 1][posy]->GetEstado().GetEstado();
      int derecha = GetEstado().GetEstado();
      int izquierda = reticula.GetMatriz()[posx][posy - 1]->GetEstado().GetEstado();
      int arriba_derecha = reticula.GetMatriz()[posx - 1][posy]->GetEstado().GetEstado();
      int arriba_izquierda = reticula.GetMatriz()[posx - 1][posy - 1]->GetEstado().GetEstado();
      int abajo_derecha = reticula.GetMatriz()[posx + 1][posy]->GetEstado().GetEstado();
      int abajo_izquierda = reticula.GetMatriz()[posx + 1][posy - 1]->GetEstado().GetEstado();
      int total = arriba + abajo + derecha + izquierda;
      total += arriba_derecha + arriba_izquierda + abajo_derecha + abajo_izquierda;
      //std::cout << total << " " << posx << posy << std::endl;
      if ( total == 2 || total == 3) {
        return 1;
      } else {
        return 0;
      }
    } else {
      int arriba = reticula.GetMatriz()[posx - 1][posy]->GetEstado().GetEstado();
      int abajo = reticula.GetMatriz()[posx + 1][posy]->GetEstado().GetEstado();
      int derecha = reticula.GetMatriz()[posx ][posy + 1]->GetEstado().GetEstado();
      int izquierda = reticula.GetMatriz()[posx][posy - 1]->GetEstado().GetEstado();
      int arriba_derecha = reticula.GetMatriz()[posx - 1][posy + 1]->GetEstado().GetEstado();
      int arriba_izquierda = reticula.GetMatriz()[posx - 1][posy - 1]->GetEstado().GetEstado();
      int abajo_derecha = reticula.GetMatriz()[posx + 1][posy + 1]->GetEstado().GetEstado();
      int abajo_izquierda = reticula.GetMatriz()[posx + 1][posy - 1]->GetEstado().GetEstado();
      int total = arriba + abajo + derecha + izquierda;
      total += arriba_derecha + arriba_izquierda + abajo_derecha + abajo_izquierda;
      //std::cout << total << " " << posx << posy << std::endl;
      if ( total == 2 || total == 3) {
        return 1;
      } else {
        return 0;
      }
    }
  }
}
/* 
x x(0,1) x (0 ,2)
x x(1,1) x (1,2)
x x(2,1) x(2,2)
*/