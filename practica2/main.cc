#include <iostream>
#include "latice.h"
#include "celula.h"
//#include "matriz.h"
//#include "myvector.h"

/*
Formas de ejecutar el programa:
./Celula -size 3 3 -border open 0
./Celula -size 5 5 -border open 1
./Celula -size 5 5 -border periodic
./Celula -size 5 5 -border reflective
./Celula -size 5 5 -border noborder
./Celula -size 5 5 -border open 0 -init matriz.txt
./Celula -size 5 5 -border open 1 -init matriz.txt
./Celula -size 5 5 -border periodic -init matriz.txt
./Celula -size 5 5 -border reflective -init matriz.txt
./Celula -size 5 5 -border noborder -init matriz.txt
*/

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
  if ( std::string(argv[5]) == "open" ) {
    if ( std::string(argv[6]) == "0" ) {
      flag = 0;
    } else if ( std::string(argv[6]) == "1" ) {
      flag = 1;
    }
  } else if ( std::string(argv[5]) == "periodic" ) {
    flag = 2;
  } else if (std::string(argv[5]) == "reflective") {
    flag = 3;
  } else if (std::string(argv[5]) == "noborder") {
    flag = 4;
  }
  if(argc == 8 ) {
    std::string file = argv[7];
    Latice latice(file, flag);
    latice.PrintInstrucciones();
    std::cout << "G ( " << 0 << " )" << std::endl;
    latice.PrintLatice();
    latice.NextGeneration();
  } else if ( argc == 9 ) {
    std::string file = argv[8];
    Latice latice(file, flag);
    latice.PrintInstrucciones();
    std::cout << "G ( " << 0 << " )" << std::endl;
    latice.PrintLatice();
    latice.NextGeneration();
  } else {
    Latice latice(filas, columnas, flag);
    latice.PrintInstrucciones();
    std::cout << "G ( " << 0 << " )" << std::endl;
    latice.PrintLatice();
    latice.NextGeneration();
  }

  return 0;
}
