#include "sequence.h"
#include "nif.h"
#include <vector>
#include <iostream>
#include "algoritmos.h"
#include <fstream>


template<class Key> 
class SortMethod {
 public:
   SortMethod(const staticSequence<Key>& data, int size, int flag);
   virtual void Sort() = 0;

 protected:
   staticSequence<Key> data_;
   int size_;
};

template <class Key>
class QuickSort : public SortMethod<Key> {
 public:
   QuickSort(const staticSequence<Key>& data, int size, int flag) : SortMethod<Key>(data, size, flag) {}
   void Sort() {
     quickSort(this->data_, this->size_);
   }
};

template <class Key>
class HeapSort : public SortMethod<Key> {
 public:
   HeapSort(const staticSequence<Key>& data, int size, int flag) : SortMethod<Key>(data, size, flag) {}
   void Sort() {
     heapSort(this->data_, this->size_);
   }
};

template <class Key>
class Seleccion : public SortMethod<Key> {
 public:
   Seleccion(const staticSequence<Key>& data, int size, int flag) : SortMethod<Key>(data, size, flag) {}
   void Sort() {
     seleccionSort(this->data_, this->size_);
   }
};

template <class Key>
class RadixSort : public SortMethod<Key> {
 public:
    RadixSort(const staticSequence<Key>& data, int size, int flag) : SortMethod<Key>(data, size, flag) {}
   void Sort() {
     radixSort(this->data_, this->size_);
   }
};

template <class Key>
class ShellSort : public SortMethod<Key> {
 public:
    ShellSort(const staticSequence<Key>& data, int size, int flag) : SortMethod<Key>(data, size, flag) {}
   void Sort() {
     shellSort(this->data_, this->size_);
   }
};

template <class Key>
SortMethod<Key>::SortMethod(const staticSequence<Key>& data, int size, int flag) : data_(data), size_(size){
  if ( flag == 0 ) { // Ramdom
    for ( int i = 0; i < size_; i++ ) {
      Key llave = Key();
      std::cout << llave << std::endl;
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
    std::ifstream file("algoritmos.txt");
    for ( int i = 0; i < size_; i++) {
      int numero;
      file >> numero;
      Key llave(numero);
      data_.insert(llave);
    }
  } else {
    std::cout << "Error: Invalid flag" << std::endl;
  }
}