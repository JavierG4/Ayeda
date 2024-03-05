//#include "position.h"
#include <iostream>
#include <vector>
#include <cstdarg>
#include "celula.h"
#include "position.h"
#include "estado.h"
#include "celulace.h"
#include "celulalife.h"
#include "factorycell.h"
#include "latice.h"
#include "latice1d.h"
#include "latice2d.h"

/*
Formas de ejecutar

./Celula -dim 1 -size 20 -cell Ace110 -border open 0
./Celula -dim 2 -size 5 5 -init matrizmodi.txt -cell Life23_3 -border noborder


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
    } else if ( std::string(argv[9 + flag_fichero + tam_dim]) == "1" ) {
      flag = 1;
    }
  } else if ( std::string(argv[8 + flag_fichero + tam_dim]) == "periodic" ) {
    flag = 2;
  } else if (std::string(argv[8 + flag_fichero + tam_dim]) == "reflective") {
    flag = 3;
  } else if (std::string(argv[8 + flag_fichero + tam_dim]) == "noborder") {
    flag = 4;
  }
  FactoryCelula* factorys;
  if (celula == "Ace110") {
    factorys = new FactoryCelulaAce110();
  } else if (celula == "Life23_3") {
    factorys = new FactoryCelulaLife23_3();
  } else if (celula == "Life51_346") {
    factorys = new FactoryCelulaLife51_346();
  } else if (celula == "Ace30") {
    factorys = new FactoryCelulaAce30();
  }
  //Celula* cell = factorys->createCelula(PositionDim<1>(1,1), Estado(1));
  Latice* latice = nullptr;
  if ( dim == 1 && flag_fichero == 2) {
    if (flag == 0) {
      latice = new latice1d_open0(file, *factorys);
    } else if (flag == 1) {
      latice = new latice1d_open1(file, *factorys);
    } else if (flag == 2) {
      latice = new latice1d_periodic(file, *factorys);
    } 
  } else if (dim == 2 && flag_fichero == 2) {
    if (flag == 0) {
      latice = new latice2d_open0(file, *factorys);
    } else if (flag == 1) {
      latice = new latice2d_open1(file, *factorys);
    } else if (flag == 2) {
      latice = new latice2d_periodic(file, *factorys);
    } else if (flag == 3) {
      latice = new latice2d_reflective(file, *factorys);
    } else if (flag == 4) {
      latice = new latice2d_noborder(file, *factorys);
    }
  } else if (dim == 1 && flag_fichero == 0) {
    if (flag == 0) {
      latice = new latice1d_open0(size, *factorys);
    } else if (flag == 1) {
      latice = new latice1d_open1(size, *factorys);
    } else if (flag == 2) {
      latice = new latice1d_periodic(size, *factorys);
    } 
  } else if (dim == 2 && flag_fichero == 0) {
    if (flag == 0) {
      latice = new latice2d_open0(filas, columnas, *factorys);
    } else if (flag == 1) {
      latice = new latice2d_open1(filas, columnas, *factorys);
    } else if (flag == 2) {
      latice = new latice2d_periodic(filas, columnas, *factorys);
    } else if (flag == 3) {
      latice = new latice2d_reflective(filas, columnas, *factorys);
    } else if (flag == 4) {
      latice = new latice2d_noborder(filas, columnas, *factorys);
    }
  }
  //std::cout << (*cell->GetPosition())[0] << std::endl;
  //std::cout << (*cell->GetPosition())[1] << std::endl;
  latice->display(std::cout) << std::endl;
  latice->PrintInstrucciones();
  latice ->nextGeneration();
  std::cout << "Flag: " << flag << std::endl;
  std::cout << "Dim: " << dim << std::endl;
  std::cout << "Size: " << size << std::endl;
  std::cout << "Filas: " << filas << std::endl;
  std::cout << "Columnas: " << columnas << std::endl;
  std::cout << "Flag_fichero: " << flag_fichero << std::endl;
  std::cout << "Celula: " << celula << std::endl;
  std::cout << "File: " << file << std::endl;
  delete factorys;
  if (latice != nullptr) {
    delete latice;
  }
  return 0;
}



