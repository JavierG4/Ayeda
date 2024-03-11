#ifndef HASH_H
#define HASH_H


#include <iostream>
#include "sequence.h"
#include "function.h"

template<class Key, class Container=staticSequence<Key>> class HashTable{
 public:
   HashTable(unsigned, DispersionFunction<Key>&, ExplorationFunction<Key>&,unsigned);
 
 private:
  unsigned tablesize_;
  DispersionFunction<Key>& dispersion_;
  ExplorationFunction<Key>& exploration_;
  unsigned blockSize_;
};

template<class Key> class HashTable<Key, dynamicSequence<Key> > {
 public:
   HashTable(unsigned, DispersionFunction<Key>&, ExplorationFunction<Key>&);
  
 private:
   unsigned tablesize_;
   DispersionFunction<Key>& dispersion_;
   ExplorationFunction<Key>& exploration_;
};

#endif