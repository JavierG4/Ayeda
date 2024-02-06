#include <iostream>
#include "latice.h"
#include "celula.h"

void Help() {
  std::cout << "-size <n>, n es el tamaño del retículo. Número de células." << std::endl;
  std::cout << "-border <b [v]>, b=open, v=[0|1]. Frontera abierta, fría o caliente. b=periodic" << std::endl;
  std::cout << "[-init <file>], (opcional) file es un nombre del fichero que contiene un array de estados con la configuración inicial del autómata celular." << std::endl;
  std::cout << "Si no se especifica se utilizará la configuración inicial por defecto, esto es, un «1» en la célula central del retículo" << std::endl;
}

int main(int argc, char* argv[]) {
  //Help();
  int n = 8;
  Latice latice(n);
  latice.PrintLatice();
  return 0;
}