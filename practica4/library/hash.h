#ifndef HASH_H
#define HASH_H


#include <iostream>
#include "sequence.h"
#include "function.h"
#include <nif.h>


template<class Key, class Container=staticSequence<Key>> class HashTable{
 public:
  HashTable(unsigned table_size, DispersionFunction<Key>& dispersion, ExplorationFunction<Key>& exploration,unsigned blocksize) {
    tablesize_ = table_size;
    dispersion_ = dispersion;
    exploration_ = exploration;
    blockSize_ = blocksize;  
}
   ~HashTable() {
     delete container_;
  }
 private:
  unsigned tablesize_;
  DispersionFunction<Key>& dispersion_;
  ExplorationFunction<Key>& exploration_;
  unsigned blockSize_;
  Container* container_;
};

template<class Key> class HashTable<Key, dynamicSequence<Key> > {
 public:
   HashTable(unsigned table_size, DispersionFunction<Key>& dispersion, ExplorationFunction<Key>& exploration) {
     tablesize_ = table_size;
     dispersion_ = dispersion;
     exploration_ = exploration;}
  
 private:
   unsigned tablesize_;
   DispersionFunction<Key>& dispersion_;
   ExplorationFunction<Key>& exploration_;
};





#endif