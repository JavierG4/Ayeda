#include "posicion.h"
#include <iostream>
#include <vector>

int main(){
  std::vector<int> posiciones = {1, 2, 3};
  Posicion<3> p(posiciones);
  std::cout << p.GetPosicion(0) << std::endl;
  std::cout << p.GetPosicion(1) << std::endl;
  std::cout << p.GetPosicion(2) << std::endl;
  Posicion<3> p3d({1, 2, 3});
  return 0;
}