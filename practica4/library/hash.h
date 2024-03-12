#ifndef HASH_H
#define HASH_H


#include <iostream>
#include "sequence.h"
#include "function.h"
#include <nif.h>
#include <termios.h>
#include <unistd.h>
#include <limits>
#include <fstream>



template<class Key, class Container=staticSequence<Key>> class HashTable{
 public:
  HashTable(unsigned table_size, DispersionFunction<Key>& dispersion, ExplorationFunction<Key>& exploration,unsigned blocksize);
   ~HashTable() {
     delete container_;
  }
  std::ostream& display(std::ostream& os) const;
  void menu();
  bool search(const Key& K) const;
  bool insert(const Key& k);
 private:
  unsigned tablesize_;
  DispersionFunction<Key>& dispersion_;
  ExplorationFunction<Key>& exploration_;
  unsigned blockSize_;
  Container* container_;
};

template<class Key> class HashTable<Key, dynamicSequence<Key> > {
 public:
   HashTable(unsigned table_size, DispersionFunction<Key>& dispersion, ExplorationFunction<Key>& exploration);
   std::ostream& display(std::ostream& os) const;
   bool search(const Key& K) const;
   bool insert(const Key& k);
   void menu();
 private:
   unsigned tablesize_;
   DispersionFunction<Key>& dispersion_;
   ExplorationFunction<Key>& exploration_;
   std::vector<dynamicSequence<Key>> container_;
};

template<class Key, class Container>
HashTable<Key, Container>::HashTable(unsigned table_size, DispersionFunction<Key>& dispersion, ExplorationFunction<Key>& exploration, unsigned blocksize)
: tablesize_(table_size), dispersion_(dispersion), exploration_(exploration), blockSize_(blocksize) {
  container_ = new Container(table_size);
  staticSequence<Nif> Sequence(blockSize_);
  for (int i = 0; i < table_size; i++) {
    container_[i] = Sequence;
  }
}

template<class Key>
HashTable<Key, dynamicSequence<Key>>::HashTable(unsigned table_size, DispersionFunction<Key>& dispersion, ExplorationFunction<Key>& exploration) : tablesize_(table_size), dispersion_(dispersion), exploration_(exploration) {
  container_.resize(table_size);
  for (int i = 0; i < table_size; i++) {
    dynamicSequence<Key> Sequence;
    container_[i] = Sequence;
  }
}

template<class Key>
bool HashTable<Key, dynamicSequence<Key>>::search(const Key& k) const {
  unsigned index = dispersion_(k);
  for (int i = 0; i < container_[index].size(); i++) {
    if (container_[index].getData()[i] == k) {
      return true;
    }
  }
}

template<class Key>
std::ostream& HashTable<Key, dynamicSequence<Key>>::display(std::ostream& os) const {
  for (int i = 0; i < tablesize_; i++) {
    os << "Poscion " << i << ": " << std::endl;  
    for (int j = 0; j < container_[i].getData().size(); j++) {
      os << container_[i].getData()[j] << " ";
    }
    os << std::endl;
  }
  os << std::endl;
  return os;
}

template<class Key>
bool HashTable<Key, dynamicSequence<Key>>::insert(const Key& k) {
  unsigned index = dispersion_(k);
  container_[index] = k;
  return true;
}

template<class Key>
void HashTable<Key, dynamicSequence<Key>>::menu() {
  unsigned x = 0;
  bool flag;
  std::cout << " Quieres pasar los Nif via terminal o txt/ 0 = terminar / 1 = txt" << std::endl;
  std::cin >> flag;
  std::vector<Nif> lista_Nif;
  if (flag == 1) {
    std::cout << " Escribe el nombre del archivo txt" << std::endl;
    std::string cadena;
    std::cin >> cadena;
    std::ifstream file(cadena);
    if (!file) {
      std::cerr << "No se pudo abrir el archivo " << std::endl;
      return;
    }
    int size = 0;
    file >> size;
    for ( int i = 0; i < size; i++) {
      int numero = 0;
      file >> numero;
      lista_Nif.push_back(Nif(numero));
    }
  } else {      
    int size;
    std::cout << "Cuantos Nifs vas a introducir " << std::endl;
    std::cin >> size;
    int Nif1;
    for (int i = 0 ; i < size; i++) {
      std::cin >> Nif1;
      lista_Nif.push_back(Nif(Nif1));
    }
  }
  for (int i = 0; i < lista_Nif.size(); i++) {
    unsigned index = dispersion_(lista_Nif[i]);
    //std::cout << index << std::endl;
    bool x = container_[index].insert(lista_Nif[i]); 
    //std::cout << "el nif " << lista_Nif[i] << " se inserto " << x << std::endl;
  }
  display(std::cout);
}



#endif