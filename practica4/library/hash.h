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
  if (search(k) == true) {
    return false;
  }
  unsigned index = dispersion_(k);
  container_[index] = k;
  return true;
}

template<class Key>
void HashTable<Key, dynamicSequence<Key>>::menu() {
  unsigned x = 0;
  bool flag;
  std::cout << "Quieres pasar los Nif via terminal o txt/ 0 = terminar / 1 = txt" << std::endl;
  std::cin >> flag;
  std::vector<Nif> lista_Nif;
  if (flag == 1) {
    std::ifstream file("nif.txt");
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
  while (true) {
    int opcion;
    std::cout << "Quieres añadir o buscar un Nif / 0 = terminar / 1 = añadir / 2 = buscar / 3 = mostrar tabla" << std::endl;
    std::cin >> opcion;
    if (opcion == 0) {
      break;
    } else if (opcion == 1) {
      int nif1;
      std::cout << "Introduce el nif" << std::endl;
      std::cin >> nif1;
      unsigned index = dispersion_(Nif(nif1));
      container_[index].insert(Nif(nif1));
    } else if (opcion == 2) {
      std::cout << "Que nif quieres buscar" << std::endl;
      int nif1 = 0;
      std::cin >> nif1;
      unsigned index = dispersion_(Nif(nif1));
      bool x = container_[index].search(Nif(nif1));
      if (x) {
        std::cout << "Se ha encontrado el nif " << nif1 << std::endl;
      } else {
        std::cout << "No se ha encontrado el nif " << nif1 << std::endl;
      }
    } else if (opcion == 3) { 
      display(std::cout);
    }
  }
}

template<class Key, class Container>
HashTable<Key, Container>::HashTable(unsigned table_size, DispersionFunction<Key>& dispersion, ExplorationFunction<Key>& exploration, unsigned blocksize)
: tablesize_(table_size), dispersion_(dispersion), exploration_(exploration), blockSize_(blocksize) {
  container_ = new Container(table_size);
  staticSequence<Nif> Sequence(blockSize_);
  for (int i = 0; i < table_size; i++) {
    container_[i] = Sequence;
  }
}

template<class Key, class Container>
bool HashTable<Key,Container>::search(const Key& k) const {
  unsigned index = dispersion_(k);
  bool full = false;
  bool encontrado = false;
  if (container_[index].isFull()) {
    full = true;
    for (int i = 0; i < container_[index].getSize(); i++) {
      if (container_[index].getData()[i] == k) {
        return true;
      }
    }
    int i = 0;
    while (encontrado == false && full == true) {
      unsigned index = exploration_(k,i);
      if (container_[index].isFull() == false) {
        full = false;
      }
      for ( int j = 0; j < blockSize_; j++) {
        if (container_[index].getData()[j] == k) {
          return true;
        }
      }
      i++;
    }
  } else {
    for (int i = 0; i < container_[index].getSize(); i++) {
      if (container_[index].getData()[i] == k) {
        return true;
      }
    }
    encontrado = false;
  }
  return encontrado;
}

template<class Key, class Container>
std::ostream& HashTable<Key,Container>::display(std::ostream& os) const {
  for (int i = 0; i < tablesize_; i++) {
    os << "Poscion " << i << ": " << std::endl;  
    for (int j = 0; j < container_[i].getSize(); j++) {
      os << container_[i].getData()[j] << " ";
    }
    os << std::endl;
  }
  os << std::endl;
  return os;
}

template<class Key, class Container>
bool HashTable<Key,Container>::insert(const Key& k) {
  if (search(k) == true) {
    return false;
  }
  unsigned index = dispersion_(k);
  if (container_[index].isFull()) {
    int i = 0;
    bool full = true;
    while (full == true) {
      unsigned index = exploration_(k,i);
      if (container_[index].isFull() == false) {
        full = false;
      }
      i++;
    }
    container_[index].insert(k);
  } else {
    container_[index].insert(k);
  }
  return true;
}

template<class Key, class Container>
void HashTable<Key,Container>::menu() {
  unsigned x = 0;
  bool flag;
  std::cout << "Quieres pasar los Nif via terminal o txt/ 0 = terminar / 1 = txt" << std::endl;
  std::cin >> flag;
  std::vector<Nif> lista_Nif;
  if (flag == 1) {
    std::ifstream file("nif.txt");
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
    // Insert NIFs into hash table
    for (const auto& nif : lista_Nif) {
      insert(nif);
    }
  } 
  while (true) {
    int option;
    std::cout << "Choose an option: \n"
              << "0 = Exit \n"
              << "1 = Insertar nif \n"
              << "2 = Buscar nif \n"
              << "3 = Mostrar tabla \n";
    std::cin >> option;
    if (option == 0) {
      break;
    } else if (option == 1) {
      Key k;
      std::cout << "Escribe el nif a añadir: ";
      std::cin >> k;
      bool inserted = insert(k);
      if (inserted) {
        std::cout << "Key " << k << " Se añadi correctamente\n";
      } else {
        std::cout << "Key " << k << " No se puede añadir\n";
      }
    } else if (option == 2) {
      Key k;
      std::cout << "Escribe el nif a buscar: ";
      std::cin >> k;
      bool found = search(k);
      if (found) {
        std::cout << "Key " << k << " found.\n";
      } else {
        std::cout << "Key " << k << " not found.\n";
      }
    } else if (option == 3) {
      display(std::cout);
    } else {
      std::cout << "Invalid option. Please try again.\n";
    }
  }
}

#endif