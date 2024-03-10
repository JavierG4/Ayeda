#ifndef HASH_H
#define HASH_H


#include <iostream>
#include "sequence.h"
#include "function.h"

class HashTable<class Key, class Container=staticSequence<Key>> {
 public:
   HashTable(unsigned, DispersionFunction<Key>&, ExplorationFunction<Key>&,unsigned);
 
 private:
  unsigned tablesize_;
  DispersionFunction<Key>& dispersion_;
  ExplorationFunction<Key>& exploration_;
}

#endif