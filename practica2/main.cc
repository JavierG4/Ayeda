#include <iostream>
#include "latice.h"
#include "celula.h"
//#include "matriz.h"
//#include "myvector.h"

void Help() {
  std::cout << "-size <M> <N>, M es el número de filas y N es el número de columnas del tablero." << std::endl;
  std::cout << "-border <b [v]>, b=open, v=[0|1]. Frontera abierta, fría o caliente. b=periodic" << std::endl;
  std::cout << "-border <b>, b=reflective b=noborder " << std::endl;
  std::cout << "[-init <file>], (opcional) file es un nombre del fichero que contiene un array de estados con la configuración inicial del autómata celular." << std::endl;
}

int main(int argc, char* argv[]) {
  //Help();
  int flag = 0;
  int filas = std::stoi(argv[2]);
  int columnas = std::stoi(argv[3]);
  if ( argv[4] == "-border" ) {
    if ( argv[5] == "open" ) {
      if ( argv[6] == "0" ) {
        flag = 0;
      } else if ( argv[6] == "1" ) {
        flag = 1;
      }
    } else if ( argv[5] == "periodic" ) {
      flag = 2;
    } else if (argv[5] == "reflective") {
      flag = 3;
    } else if (argv[5] == "noborder") {
      flag = 4;
    }
  }
  std::cout << "flag: " << flag << std::endl;
  std::cout << "filas: " << filas << std::endl;
  std::cout << "columnas: " << columnas << std::endl;
  //std::cout << "fichero: " << fichero << std::endl;
  Latice latice(filas, columnas, flag);
  latice.PrintLatice();
  return 0;
}