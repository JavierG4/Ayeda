#ifndef SEQUENCE_H
#define SEQUENCE_H

#include <iostream>
#include <vector>

/**
 * @class Sequence
 * @brief Clase base abstracta para las secuencias.
 * @tparam Key Tipo de la clave que se manejará en la secuencia.
 */
template<class Key>
class Sequence {
  public: 
    /**
     * @brief Busca una clave en la secuencia.
     * @param k Clave a buscar.
     * @return Verdadero si la clave se encuentra en la secuencia, falso en caso contrario.
     */
    virtual bool search(const Key& k) const = 0;

    /**
     * @brief Inserta una clave en la secuencia.
     * @param k Clave a insertar.
     * @return Verdadero si la inserción fue exitosa, falso en caso contrario.
     */
    virtual bool insert(const Key& k) = 0;
};

/**
 * @class dynamicSequence
 * @brief Clase que implementa una secuencia dinámica.
 * @tparam Key Tipo de la clave que se manejará en la secuencia.
 */
template<class Key> 
class dynamicSequence: public Sequence<Key> {
 public:
  /**
   * @brief Constructor que inicializa la secuencia como vacía.
   */
  dynamicSequence() : data_(std::vector<Key*>()) {} // Inicializa data_ como un vector vacío

  /**
   * @brief Busca una clave en la secuencia.
   * @param k Clave a buscar.
   * @return Verdadero si la clave se encuentra en la secuencia, falso en caso contrario.
   */
  bool search(const Key& k) const;

  /**
   * @brief Inserta una clave en la secuencia.
   * @param k Clave a insertar.
   * @return Verdadero si la inserción fue exitosa, falso en caso contrario.
   */
  bool insert(const Key& k);

  /**
   * @brief Obtiene los datos de la secuencia.
   * @return Vector con los datos de la secuencia.
   */
  std::vector<Key*> getData() const {return data_;}

 private:
   std::vector<Key*> data_; ///< Vector que almacena los datos de la secuencia.
};

template<class Key>
bool dynamicSequence<Key>::insert(const Key& k) {
  if (search(k)) {
    return false;
  }
  Key* newKey = new Key(k); // Crea un nuevo Key en el heap
  data_.push_back(newKey); // Añade el puntero al vector
  return true;
}
template<class Key>
bool dynamicSequence<Key>::search(const Key& k) const {
  for (int i = 0; i < data_.size(); i++) {
    if (*data_[i] == k) {
      return true;
    }
  }
  return false;
}


/**
 * @class staticSequence
 * @brief Clase que implementa una secuencia estática.
 * @tparam Key Tipo de la clave que se manejará en la secuencia.
 */
template<class Key> 
class staticSequence: public Sequence<Key> {
 public:
  /**
   * @brief Constructor que inicializa la secuencia con un tamaño determinado.
   * @param size Tamaño de la secuencia.
   */
  staticSequence(unsigned size) {
    inicio = 0;
    size_ = size;
    data_ = new Key*[size];
    for (int i = 0; i < size; i++) {
      data_[i] = nullptr;
    }
  }

  /**
   * @brief Destructor que libera la memoria ocupada por la secuencia.
   */
  ~staticSequence() {
    for (int i = 0; i < size_; i++) {
      delete data_[i];
    }
    delete[] data_;
  }

  /**
   * @brief Verifica si la secuencia está llena.
   * @return Verdadero si la secuencia está llena, falso en caso contrario.
   */
  bool isFull() const;

  /**
   * @brief Busca una clave en la secuencia.
   * @param k Clave a buscar.
   * @return Verdadero si la clave se encuentra en la secuencia, falso en caso contrario.
   */
  bool search(const Key& k) const;

  /**
   * @brief Inserta una clave en la secuencia.
   * @param k Clave a insertar.
   * @return Verdadero si la inserción fue exitosa, falso en caso contrario.
   */
  bool insert(const Key& k);

  /**
   * @brief Obtiene el tamaño de la secuencia.
   * @return Tamaño de la secuencia.
   */
  unsigned getSize() {return size_;}

  /**
   * @brief Obtiene los datos de la secuencia.
   * @return Puntero a los datos de la secuencia.
   */
  Key** getData() {return data_;}

  /**
   * @brief Obtiene el inicio de la secuencia.
   * @return Inicio de la secuencia.
   */
  int getInicio() {return inicio;}

 private:
  int inicio; ///< Inicio de la secuencia.
  unsigned size_; ///< Tamaño de la secuencia.
  Key** data_; ///< Puntero a los datos de la secuencia.
};

template<class Key>
bool staticSequence<Key>::isFull() const {
  for (int i = 0; i < size_ ; i++) {
    if (data_[i] == nullptr) {
      return false;
    }
  }
  return true;
}

template<class Key>
bool staticSequence<Key>::search(const Key& k) const {
  for ( int i = 0; i < inicio; i++ ) {
    if (data_[i] != nullptr && *data_[i] == k) {
      return true;
    }
  }
  return false;
}

template<class Key>
bool staticSequence<Key>::insert(const Key& k) {
  if (search(k)) {
    return true;
  }
  if (isFull()) {
    return false;
  }
  for (int i = 0; i < size_; i++) {
    if (data_[i] == nullptr)  {
      data_[i] = new Key(k);
      inicio++;
      return true;
    }
  }
  return false;
}
#endif