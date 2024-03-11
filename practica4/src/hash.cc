#include "hash.h"

HashTable<Key,Container>::HashTable(unsigned table_size, DispersionFunction<Key>& dispersion, ExplorationFunction<Key>& exploration,unsigned blocksize) {
  tablesize_ = table_size;
  dispersion_ = dispersion;
  exploration_ = exploration;
  blockSize_ = blocksize;  
}

HashTable<Key, dynamicSequence<Key> >::HashTable(unsigned table_size, DispersionFunction<Key>& dispersion, ExplorationFunction<Key>& exploration) {
  tablesize_ = table_size;
  dispersion_ = dispersion;
  exploration_ = exploration;
}
