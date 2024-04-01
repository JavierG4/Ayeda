#include <iostream>
#include "sequence.h"
#include "nif.h"
#include <string>
#include "sortmethod.h"


/*
a. -size <s>, s es el tamaño de la secuencia.
b. -ord <m>, m es el código que identifica un método de ordenación.
c. -init <i> [f], indica la forma de introducir los datos de la secuencia
    i=manual
    i=random
    i=file f=nombre del fichero de entrada
d. -trace <y|n>, indica si se muestra o no la traza durante la ejecución.

Codigos
0 Selección
1 QuickSort
2 HeapSort
3 Por Incrementos Decrecientes (ShellSort): debe permitir seleccionar la constante
de reducción alfa, siendo 0 < alfa < 1
4 RadixSort



Ejemplos de uso:

./Hash -ts 5 -fd 1 -hash open -bs 5 -fe 1
./Hash -ts 1024 -fd 0 -hash close -bs 10 -fe 0

*/
int main(int argc, char* argv[]) {
  int size = std::stoi(argv[2]);
  int ord = std::stoi(argv[4]);
  std::string init = argv[6];
  int trace = std::stoi(argv[8]); // 0 = no, 1 = yes


}