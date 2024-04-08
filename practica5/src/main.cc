#include <iostream>
#include "sequence.h"
#include "nif.h"
#include <string>
#include "sortmethod.h"


/*
a. -size <s>, s es el tamaño de la secuencia.
b. -ord <m>, m es el código que identifica un método de ordenación.
c. -init <i> [f], indica la forma de introducir los datos de la secuencia
    i=manual 1
    i=random 0
    i=file f=nombre del fichero de entrada 2
d. -trace <y|n>, indica si se muestra o no la traza durante la ejecución.

Codigos
0 Selección
1 QuickSort
2 HeapSort
3 Por Incrementos Decrecientes (ShellSort): debe permitir seleccionar la constante
de reducción alfa, siendo 0 < alfa < 1
4 RadixSort



Ejemplos de uso:

./Sort -size 5 -ord 2 -init 0 -trace 0
./Sort -size 5 -ord 1 -init 0 -trace 1

*/
int main(int argc, char* argv[]) {
  int size = std::stoi(argv[2]);
  int ord = std::stoi(argv[4]);
  int init = std::stoi(argv[6]);
  std::cout << "Size: " << size << std::endl;
  std::cout << "Ord: " << ord << std::endl;
  std::cout << "Init: " << init << std::endl;
  int i = 0;
  std::string file;
  if (init == 2 ) {
    i++;
    file = std::stoi(argv[7]);
  }
  bool trace = std::stoi(argv[i + 8]); // 0 = no, 1 = yes
  SortMethod<Nif>* algoritmo;
  staticSequence<Nif> data(size);
  switch (ord) {
    case 0:
      algoritmo = new Seleccion<Nif>(data, size, init, file);
      break;
    case 1:
      algoritmo = new QuickSort<Nif>(data, size, init, file);
      break;
    case 2:
      algoritmo = new HeapSort<Nif>(data, size, init, file);
      break;
    case 3:
      algoritmo = new ShellSort<Nif>(data, size, init, file);
      break;
    case 4:
      algoritmo = new RadixSort<Nif>(data, size, init, file);
      break;
  }
  algoritmo->Sort(trace); // Hay que indicar la traza tambien
  delete algoritmo;
  return 0;
}