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
  int size1 = 500;
  int size2 = 3000;
  int ord = 0;
  int init = 0;
  std::string file;
  SortMethod<int>* algoritmo;
  SortMethod<int>* algoritmo1;
  staticSequence<int> data1(size1);
  staticSequence<int> data2(size1);
  bool trace = false;
  algoritmo = new QuickSort<int>(data1, size1, init, file);
  algoritmo1 = new ShellSort<int>(data2, size1, init, file);
  algoritmo->Sort(trace); // Hay que indicar la traza tambien
  std::cout << "Quicksort de 500 "<< algoritmo->getComparaciones() << std::endl;
  algoritmo1->Sort(trace);
  std::cout << "Shellsort de 500 " << algoritmo1->getComparaciones() << std::endl;
  delete algoritmo;
  delete algoritmo1;

  SortMethod<int>* algoritmo2;
  SortMethod<int>* algoritmo3;
  staticSequence<int> data3(size2);
  staticSequence<int> data4(size2);
  algoritmo2 = new QuickSort<int>(data3, size2, init, file);
  algoritmo3 = new ShellSort<int>(data4, size2, init, file);
  algoritmo2->Sort(trace); // Hay que indicar la traza tambien
  std::cout << "Quicksort de 3000 " << algoritmo2->getComparaciones() << std::endl;
  algoritmo3->Sort(trace);
  std::cout << "Shellsort de 3000 " << algoritmo3->getComparaciones() << std::endl;
  
  delete algoritmo2;
  delete algoritmo3;
  return 0;
}