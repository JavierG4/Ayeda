#include <iostream>
#include "hash.h"
#include "function.h"
#include "sequence.h"
#include "nif.h"
#include <string>


/*
a. -ts <s>, s es el tamaño de la tabla.
b. -fd <f>, f es el código que identifica a una función de dispersión.
c. -hash <open|close>, indica la técnica de dispersión a utilizar. Implica el tipo de
secuencia utilizada para el parámetro Container.
d. -bs <s>, s es el tamaño del bloque. Sólo para dispersión cerrada.
e. -fe <f>, f es el código que identifica a una función de exploración. Sólo para
dispersión cerrada.

Ejemplos de uso:


./Hash -ts 5 -fd 1 -hash open -bs 5 -fe 1

*/
int main(int argc, char* argv[]) {
  unsigned table_size = std::stoi(argv[2]);
  int fd_dispersion = std::stoi(argv[4]);
  std::string hash = argv[6];
  unsigned blocksize = std::stoi(argv[8]);
  int fd_exploration = std::stoi(argv[10]);
  DispersionFunction<Nif>* dispersion;
  ExplorationFunction<Nif>* exploration;
  if (fd_dispersion == 1) {
    dispersion = new Modulo<Nif>(table_size);
  } else {
    dispersion = new PseudoRandom<Nif>(table_size);
  }
  if (fd_exploration == 1) {
    exploration = new LinearExploration<Nif>(table_size);
  } else {
    exploration = new QuadraticExploration<Nif>(table_size);
  }
  if (hash == "open") {
    HashTable<Nif, dynamicSequence<Nif>> hash_table(table_size, *dispersion, *exploration);
    hash_table.menu();
  } else {
    HashTable<Nif, staticSequence<Nif>> hash_table(table_size, *dispersion, *exploration, blocksize);
    //hash_table.menu();
  }
}