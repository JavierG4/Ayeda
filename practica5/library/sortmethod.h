#include "sequence.h"
#include "nif.h"
#include <vector>
#include <iostream>
#include "algoritmos.h"
#include <fstream>


template<class Key> 
class SortMethod {
 public:
   SortMethod(const staticSequence<Key>& data, int size, int flag, std::string file);
   virtual void Sort(bool) = 0;

 protected:
   staticSequence<Key> data_;
   int size_;
};

template <class Key>
class QuickSort : public SortMethod<Key> {
 public:
   QuickSort(const staticSequence<Key>& data, int size, int flag, std::string file) : SortMethod<Key>(data, size, flag, file) {}
   void Sort(bool trace) {
     quickSort(this->data_, this->size_, trace);
   }
};

template <class Key>
class HeapSort : public SortMethod<Key> {
 public:
   HeapSort(const staticSequence<Key>& data, int size, int flag, std::string file) : SortMethod<Key>(data, size, flag, file) {}
   void Sort(bool trace) {
     heapSort(this->data_, this->size_, trace);
   }
};

template <class Key>
class Seleccion : public SortMethod<Key> {
 public:
   Seleccion(const staticSequence<Key>& data, int size, int flag, std::string file) : SortMethod<Key>(data, size, flag, file) {}
   void Sort(bool trace) {
     seleccionSort(this->data_, this->size_, trace);
   }
};

template <class Key>
class RadixSort : public SortMethod<Key> {
 public:
   RadixSort(const staticSequence<Key>& data, int size, int flag, std::string file) : SortMethod<Key>(data, size, flag, file) {}
   void Sort(bool trace) {
     radixSort(this->data_, this->size_, trace);
   }
};

template <class Key>
class ShellSort : public SortMethod<Key> {
 public:
    ShellSort(const staticSequence<Key>& data, int size, int flag, std::string file) : SortMethod<Key>(data, size, flag, file) {}
   void Sort(bool trace) {
     shellSort(this->data_, this->size_, trace);
   }
};

template <class Key>
SortMethod<Key>::SortMethod(const staticSequence<Key>& data, int size, int flag, std::string file) : data_(data), size_(size){
  if ( flag == 0 ) { // Ramdom
    for ( int i = 0; i < size_; i++ ) {
      Key llave = Key();
      //std::cout << llave << std::endl;
      data_.insert(llave);
    }
  } else if ( flag == 1 ) { //manual
    for ( int i = 0 ; i < size_; i++ ) {
      int numero;
      std::cin >> numero;
      Key llave(numero);
      data_.insert(llave);
    }
  } else if ( flag == 2 ) { // file
    std::ifstream file1(file);
    for ( int i = 0; i < size_; i++) {
      int numero;
      file1 >> numero;
      Key llave(numero);
      data_.insert(llave);
    }
  } else {
    std::cout << "Error: Invalid flag" << std::endl;
  }
}