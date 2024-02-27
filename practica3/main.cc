//#include "position.h"
#include <iostream>
#include <vector>
#include <cstdarg>
#include "celula.h"
#include "position.h"
#include "Estado.h"
#include "celulace.h"
#include "celulalife.h"

/*
Formas de ejecutar

./a.out -dim 1 -size 10 -init Ace110 -border reflective



*/


int main(int argc, char* argv[]){
  int flag = 0;
  int dim = std::stoi(argv[2]);
  int size = 0;
  int filas = 0;
  int columnas = 0;
  int tam_dim = 0;
  if (dim == 1) {
    size = std::stoi(argv[4]);
    tam_dim = 0;
  } else if (dim == 2) {
    filas = std::stoi(argv[4]);
    columnas = std::stoi(argv[5]);
    tam_dim = 1;
  }
  int flag_fichero = 0;
  std::string file;
  if ( std::string(argv[5]) == "-init" ) {
    flag_fichero = 2;
    file = std::string(argv[6]);
  } else if ( std::string(argv[6]) == "-init" ) {
    flag_fichero = 2;
    file = std::string(argv[7]);
  }
  std::string celula;
  if (std::string(argv[6 + flag_fichero + tam_dim]) == "Ace110") {
    celula = "Ace110";
  } else if (std::string(argv[6 + flag_fichero + tam_dim]) == "Life23_3") {
    celula = "Life23_3";
  } else if (std::string(argv[6 + flag_fichero + tam_dim]) == "Life51_346") {
    celula = "Life51_346";
  } else if (std::string(argv[6 + flag_fichero + tam_dim]) == "Ace30") {
    celula = "Ace30";
  }
  if ( std::string(argv[8 + flag_fichero + tam_dim]) == "open" ) {
    if ( std::string(argv[9 + flag_fichero + tam_dim]) == "0" ) {
      flag = 0;
    } else if ( std::string(argv[8 + flag_fichero + tam_dim]) == "1" ) {
      flag = 1;
    }
  } else if ( std::string(argv[8 + flag_fichero + tam_dim]) == "periodic" ) {
    flag = 2;
  } else if (std::string(argv[8 + flag_fichero + tam_dim]) == "reflective") {
    flag = 3;
  } else if (std::string(argv[8 + flag_fichero + tam_dim]) == "noborder") {
    flag = 4;
  }
  if (celula == "Ace110") {
    FactoryCelulaAce110 factory;
  } else if (celula == "Life23_3") {
    FactoryCelulaLife23_3 factory;
  } else if (celula == "Life51_346") {
    FactoryCelulaLife51_346 factory;
  } else if (celula == "Ace30") {
    FactoryCelulaAce30 factory;
  }

  return 0;
}



/*
 std::cout << "Flag: " << flag << std::endl;
  std::cout << "Dim: " << dim << std::endl;
  std::cout << "Size: " << size << std::endl;
  std::cout << "Filas: " << filas << std::endl;
  std::cout << "Columnas: " << columnas << std::endl;
  std::cout << "Flag_fichero: " << flag_fichero << std::endl;
  std::cout << "Celula: " << celula << std::endl;
  std::cout << "File: " << file << std::endl;
*/