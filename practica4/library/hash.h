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


int exploration = 0;
int full_num = 0;

/**
 * @class HashTable
 * @brief Clase que representa una tabla hash.
 * @tparam Key Tipo de la clave que se manejará en la tabla hash.
 * @tparam Container Tipo del contenedor que se usará en la tabla hash. Por defecto, se usa una secuencia estática.
 */
template<class Key, class Container=staticSequence<Key>> 
class HashTable{
 public:
  /**
   * @brief Constructor que inicializa la tabla hash.
   * @param table_size Tamaño de la tabla hash.
   * @param dispersion Función de dispersión que se usará en la tabla hash.
   * @param exploration Función de exploración que se usará en la tabla hash.
   * @param blocksize Tamaño del bloque que se usará en la tabla hash.
   */
  HashTable(unsigned table_size, DispersionFunction<Key>& dispersion, ExplorationFunction<Key>& exploration,unsigned blocksize);

  /**
   * @brief Destructor que libera la memoria ocupada por la tabla hash.
   */
  ~HashTable();

  /**
   * @brief Muestra la tabla hash en un flujo de salida.
   * @param os Flujo de salida donde se mostrará la tabla hash.
   * @return Flujo de salida modificado.
   */
  std::ostream& display(std::ostream& os) const;

  /**
   * @brief Muestra un menú de opciones para la tabla hash.
   */
  void menu();

  /**
   * @brief Busca una clave en la tabla hash.
   * @param K Clave a buscar.
   * @return Verdadero si la clave se encuentra en la tabla hash, falso en caso contrario.
   */
  bool search(const Key& K) const;

  /**
   * @brief Inserta una clave en la tabla hash.
   * @param k Clave a insertar.
   * @return Verdadero si la inserción fue exitosa, falso en caso contrario.
   */
  bool insert(const Key& k);

 private:
  unsigned tablesize_; ///< Tamaño de la tabla hash.
  DispersionFunction<Key>& dispersion_; ///< Función de dispersión que se usa en la tabla hash.
  ExplorationFunction<Key>& exploration_; ///< Función de exploración que se usa en la tabla hash.
  unsigned blockSize_; ///< Tamaño del bloque que se usa en la tabla hash.
  Container** container_; ///< Contenedor que se usa en la tabla hash.
};

/**
 * @class HashTable
 * @brief Clase que representa una tabla hash con una secuencia dinámica.
 * @tparam Key Tipo de la clave que se manejará en la tabla hash.
 */
template<class Key> 
class HashTable<Key, dynamicSequence<Key> > {
 public:
   /**
    * @brief Constructor que inicializa la tabla hash.
    * @param table_size Tamaño de la tabla hash.
    * @param dispersion Función de dispersión que se usará en la tabla hash.
    * @param exploration Función de exploración que se usará en la tabla hash.
    */
   HashTable(unsigned table_size, DispersionFunction<Key>& dispersion, ExplorationFunction<Key>& exploration);

   /**
    * @brief Muestra la tabla hash en un flujo de salida.
    * @param os Flujo de salida donde se mostrará la tabla hash.
    * @return Flujo de salida modificado.
    */
   std::ostream& display(std::ostream& os) const;

   /**
    * @brief Busca una clave en la tabla hash.
    * @param K Clave a buscar.
    * @return Verdadero si la clave se encuentra en la tabla hash, falso en caso contrario.
    */
   bool search(const Key& K) const;

   /**
    * @brief Inserta una clave en la tabla hash.
    * @param k Clave a insertar.
    * @return Verdadero si la inserción fue exitosa, falso en caso contrario.
    */
   bool insert(const Key& k);

   /**
    * @brief Muestra un menú de opciones para la tabla hash.
    */
   void menu();

 private:
   unsigned tablesize_; ///< Tamaño de la tabla hash.
   DispersionFunction<Key>& dispersion_; ///< Función de dispersión que se usa en la tabla hash.
   ExplorationFunction<Key>& exploration_; ///< Función de exploración que se usa en la tabla hash.
   std::vector<dynamicSequence<Key>> container_; ///< Contenedor que se usa en la tabla hash.
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
    if (container_[index].search(k) == true){
      return true;
    }
  }
}

template<class Key>
std::ostream& HashTable<Key, dynamicSequence<Key>>::display(std::ostream& os) const {
  for (int i = 0; i < tablesize_; i++) {
    os << "Poscion " << i << ": " << std::endl;  
    for (int j = 0; j < container_[i].getData().size(); j++) {
      os << *container_[i].getData()[j] << " ";
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
      bool x = container_[index].insert(Nif(nif1));
      if (x) {
        std::cout << "Se ha insertado el nif " << nif1 << std::endl;
      } else {
        std::cout << "No se ha insertado el nif " << nif1 << std::endl;
      }
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
  container_ = new Container*[table_size];
  for (int i = 0; i < table_size; i++) {
    container_[i] = new staticSequence<Nif>(blockSize_);
  }
}

template<class Key, class Container>
bool HashTable<Key,Container>::search(const Key& k) const {
  unsigned index = dispersion_(k);
  bool full = false;
  bool encontrado = false;
  if (container_[index]->isFull()) {
    full = true;
    if (container_[index]->search(k)) {
      return true;
    }
    int i = 1;
    while (encontrado == false && full == true) {
      unsigned aux = exploration_(k,i);
      aux = index + aux;
      aux = aux % tablesize_;
      //std::cout << "i = "<< index << " ex =" << aux <<std::endl;
      exploration++;
      if (container_[aux]->isFull() == false) {
        full_num++;
        full = false;
      }
      if (container_[aux]->search(k)) {
        return true;
      }
      i++;
      if (i == tablesize_) {
        return false;
      }
    }
  } else {
    if (container_[index]->search(k)) {
      return true;
    }
    encontrado = false;
  }
  return encontrado;
}

template<class Key, class Container>
std::ostream& HashTable<Key,Container>::display(std::ostream& os) const {
  for (int i = 0; i < tablesize_; i++) {
    os << "Posicion " << i << ": " << std::endl;  
    for (int j = 0; j < container_[i]->getInicio(); j++) {
      os << *container_[i]->getData()[j] << " ";
    }
    os << std::endl;
  }
  os << std::endl;
  return os;
}

template<class Key, class Container>
bool HashTable<Key,Container>::insert(const Key& k) {
  unsigned index = dispersion_(k);
  if (container_[index]->search(k) == true) {
    return false;
  }
  if (container_[index]->isFull()) {
    int i = 1;
    bool full = true;
    while (full == true) {
      unsigned exploration = exploration_(k,i);
      unsigned aux = index + exploration;
      aux = aux % tablesize_;
      //std::cout << "i = "<< index << " ex =" << exploration << "final = " << aux <<std::endl;
      if (container_[aux]->insert(k) == true) {
        return true;
      }
      i++;
      if (i == tablesize_) {
        return false;
      }
    }
  } else {
    if ( container_[index]->search(k) == true) {
      return false;
    } else {
      container_[index]->insert(k);
    }
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
  std::vector<Nif> lista_Nif2;
  if (flag == 1) {
    std::ifstream file("nif2.txt");
    if (!file) {
      std::cerr << "No se pudo abrir el archivo " << std::endl;
      return;
    }
    int size = 0;
    file >> size;
    for ( int i = 0; i < size ; i++) {
      int numero = 0;
      if ( size / 2 < i) {
        file >> numero;
        lista_Nif2.push_back(Nif(numero));
      } else {
        file >> numero;
        lista_Nif.push_back(Nif(numero));
      }
      file >> numero;
      lista_Nif.push_back(Nif(numero));
    }
    // Insert NIFs into hash table
    for (const auto& nif : lista_Nif) {
      //std::cout << "Inserting " << nif.get() << std::endl;
      insert(nif);
    }
  } 
  while (true) {
    int option;
    std::cout << "Choose an option: \n"
              << "0 = Exit \n"
              << "1 = Insertar nif \n"
              << "2 = Buscar nif \n"
              << "3 = Mostrar tabla \n"
              << "4 = Contar exploracion \n";
    std::cin >> option;
    if (option == 0) {
      break;
    } else if (option == 1) {
      int k;
      std::cout << "Escribe el nif a añadir: ";
      std::cin >> k;
      bool inserted = insert(Nif(k));
      if (inserted) {
        std::cout << "Key " << k << " Se añadi correctamente o ya estaba añadida\n";
      } else {
        std::cout << "Key " << k << " No se puede añadir\n";
      }
    } else if (option == 2) {
      int k;
      std::cout << "Escribe el nif a buscar: " << std::endl;;
      std::cin >> k;
      bool found = search(Nif(k));
      if (found) {
        std::cout << "Key " << k << " found.\n";
      } else {
        std::cout << "Key " << k << " not found.\n";
      }
    } else if (option == 3) {
      display(std::cout);
    } else if (option == 4) {
      int exploracion = 0;
      int size_half = tablesize_ / 2;
      exploration = 0;
      full_num = 0;
      std::cout << exploration << std::endl;
      std::cout << lista_Nif2.size() << std::endl;
      for (int i = 0 ;i < lista_Nif2.size(); i++) {
        search(lista_Nif2[i]);
      }
      std::cout << "Exploration" << exploration << std::endl;
      std::cout << "Full num" << full_num << std::endl;
    } else {
      std::cout << "Invalid option\n";
    }
  }
}

template<class Key, class Container>
HashTable<Key,Container>::~HashTable() {
  for (int i = 0; i < tablesize_; i++) {
    delete container_[i];
  }
  delete[] container_;
}
#endif