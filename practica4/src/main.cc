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

*/
int main(int argc, char* argv[]) {
  int table_size = std::stoi(argv[2]);
  int fd_dispersion = std::stoi(argv[4]);
  std::string hash = argv[6];
  int blocksize = std::stoi(argv[8]);
  int fd_exploration = std::stoi(argv[10]);
  DispersionFunction<nif>* dispersion;
  ExplorationFunction<nif>* exploration;
  if (fd_dispersion == 1) {
    //dispersion = new Modulo<int>(table_size);
  } else {
    //dispersion = new PseudoRandom<int>(table_size);
  }
  if (fd_exploration == 1) {
    //exploration = new Linear<int>(table_size);
  } else {
    //exploration = new Quadratic<int>(table_size);
  }
  if (hash == "open") {
    if (fd_dispersion == 1) {
      HashTable<nif, staticSequence<nif>> hash_table(table_size, dispersion, exploration, blocksize);
    } else {
      HashTable<nif, dynamicSequence<nif>> hash_table(table_size, dispersion, exploration, blocksize);
    }
  } else {
    if (fd_dispersion == 1) {
      HashTable<nif, staticSequence<nif>> hash_table(table_size, dispersion, exploration, blocksize);
    } else {
      HashTable<nif, dynamicSequence<nif>> hash_table(table_size, dispersion, exploration, blocksize);
    }
  }
}