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
  int flag = 0;
  int n = std::stoi(argv[2]);
  if (std::string(argv[4]) == "open") {
    if (std::string(argv[5]) == "0") {
      //std::cout << "entra0" << std::endl;
      flag = 0;
    } else if (std::string(argv[5]) == "1") {
      //std::cout << "entra1" << std::endl;
      flag = 1;
    }
  } else if (std::string(argv[4]) == "periodic") {
    //std::cout << "entra2" << std::endl;
    flag = 2;
  }
  std::string fichero = " ";
  //std::cout << argc << std::endl;
  if (argc == 8 ) {
    fichero = argv[7];
  } else if (argc == 7 && std::string(argv[4]) == "periodic") {
    fichero = argv[6];
  }

  std::cout << "flag: " << flag << std::endl;
  std::cout << "n: " << n << std::endl;
  std::cout << "fichero: " << fichero << std::endl;
  Latice latice(n,flag,fichero);
  latice.PrintLatice(0);
  latice.NextGeneration();
  return 0;
}