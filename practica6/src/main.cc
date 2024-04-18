#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>
#include <fstream>
#include <utility>
#include "nodob.h"
#include "ab.h"
#include "nif.h"

/*
a. -ab <abe|abb>, para indicar el tipo de árbol con el que se va a trabajar.
b. -init <i> [s][f], indica la forma de introducir los datos de la secuencia
i=manual
i=random [s], s es el número de elementos a generar
i=file [s][f], s es el número de elementos a generar
f es nombre del fichero de entrada


Formas de ejecutralo
./Arbol -ab abe -init ramdom 5

*/

int main(int argc, char* argv[]) {
  std::string opcion = argv[2];
  std::string init = argv[4];
  AB<Nif>* arbol;
  if (opcion == "abe" ) {
    if (init == "manual" ) {
      arbol = new ABE<Nif>();
    } else if (init == "ramdom" ) {
      int num = std::stoi(argv[5]);
      arbol = new ABE<Nif>(num);
    } else {
      int num = std::stoi(argv[5]);
      std::string file = argv[6];
      arbol = new ABE<Nif>(num,file);
    }
  } else {
    if (init == "manual" ) {
      arbol = new ABB<Nif>();
    } else if (init == "ramdom" ) {
      int num = std::stoi(argv[5]);
      arbol = new ABB<Nif>(num);
    } else {
      int num = std::stoi(argv[5]);
      std::string file = argv[6];
      arbol = new ABB<Nif>(num,file);
    }
  }
  //Menú
  bool salir = false;
  while ( salir == false ) {
    int opcion_menu;
    std::cout << "[0] Salir \n";
    std::cout << "[1] Insertar \n";
    std::cout << "[2] Buscar \n";
    std::cout << "[3] Mostrar árbol inorden\n";
    std::cin >> opcion_menu;
    if (opcion_menu == 0) {
      salir = true;
    } else if ( opcion_menu == 1) {
      int numero;
      std::cout << "Valor a insertar" << std::endl;
      std::cin >> numero;
      Nif llave(numero);
      arbol->Insertar(llave);
      arbol->Inorden();
    } else if ( opcion_menu == 2) {
      int numero;
      std::cout << "Valor a Buscar" << std::endl;
      std::cin >> numero;
      Nif llave(numero);
      bool respuesta = arbol->Buscar(llave);
      if (respuesta) {
        std::cout << "Se encontro al número" << numero << std::endl;
      }
    } else if (opcion_menu == 3) {
      arbol->Inorden();
    } else {
      std::cout << "Opción no válida\n";
    }
  }
}