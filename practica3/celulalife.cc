#include "celulalife.h"

int CelulaLife23_3::NextState(Latice& reticula) {
  int posx = (*GetPosition())[0];
  int posy = (*GetPosition())[1];
  int contador = 0;
  contador += reticula[PositionDim<2>(2,posx - 1, posy - 1)].GetEstado().GetEstado(); //Arriba izquierda
  contador += reticula[PositionDim<2>(2,posx - 1, posy)].GetEstado().GetEstado(); //Arriba
  contador += reticula[PositionDim<2>(2,posx - 1, posy + 1)].GetEstado().GetEstado(); //Arriba derecha
  contador += reticula[PositionDim<2>(2,posx, posy - 1)].GetEstado().GetEstado(); //Izquierda
  contador += reticula[PositionDim<2>(2,posx, posy + 1)].GetEstado().GetEstado(); //Derecha
  contador += reticula[PositionDim<2>(2,posx + 1, posy - 1)].GetEstado().GetEstado(); // Abajo izquierda
  contador += reticula[PositionDim<2>(2,posx + 1, posy)].GetEstado().GetEstado(); // Abajo
  contador += reticula[PositionDim<2>(2,posx + 1, posy + 1)].GetEstado().GetEstado(); // Abajo derecha
  //std::cout << posx << " " << posy << " " << contador << std::endl;
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

void CelulaLife23_3::UpdateState() {
  estado_ = estado_siguiente_;
}

int CelulaLife51_346::NextState(Latice& reticula) {
  int posx = (*GetPosition())[0];
  int posy = (*GetPosition())[1];
  int contador = 0;
  contador += reticula[PositionDim<2>(2,posx - 1, posy - 1)].GetEstado().GetEstado(); //Arriba izquierda
  contador += reticula[PositionDim<2>(2,posx - 1, posy)].GetEstado().GetEstado(); //Arriba
  contador += reticula[PositionDim<2>(2,posx - 1, posy + 1)].GetEstado().GetEstado(); //Arriba derecha
  contador += reticula[PositionDim<2>(2,posx, posy - 1)].GetEstado().GetEstado(); //Izquierda
  contador += reticula[PositionDim<2>(2,posx, posy + 1)].GetEstado().GetEstado(); //Derecha
  contador += reticula[PositionDim<2>(2,posx + 1, posy - 1)].GetEstado().GetEstado(); // Abajo izquierda
  contador += reticula[PositionDim<2>(2,posx + 1, posy)].GetEstado().GetEstado(); // Abajo
  contador += reticula[PositionDim<2>(2,posx + 1, posy + 1)].GetEstado().GetEstado(); // Abajo derecha
  //std::cout << posx << " " << posy << " " << contador << std::endl;
  if (GetEstado().GetEstado() == 0) {
    if (contador == 3 || contador == 4 || contador == 6) {
      return 1;
    } else {
      return 0;
    }
  } else {
    if (contador == 5 || contador == 1) {
      return 1;
    } else {
      return 0;
    }
  }
}

void CelulaLife51_346::UpdateState() {
  estado_ = estado_siguiente_;
}