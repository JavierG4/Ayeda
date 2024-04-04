#ifndef SEQUENCE_H
#define SEQUENCE_H

#include <iostream>
#include <vector>
#include <fstream>

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
    virtual const Key& operator[](const int& p) const = 0;
    virtual Key& operator[](const int& p) = 0;
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

template<class Key> 
class staticSequence: public Sequence<Key> {
 public:
  staticSequence(unsigned size) {
    inicio = 0;
    size_ = size;
    data_.resize(size, nullptr);
  }

  ~staticSequence() {
    for (auto& ptr : data_) {
      delete ptr;
    }
  }

  bool isFull() const {
    return inicio == size_;
  }

  bool search(const Key& k) const {
    for (auto ptr : data_) {
      if (ptr != nullptr && *ptr == k) {
        return true;
      }
    }
    return false;
  }

  bool insert(const Key& k) {
    if (search(k)) {
      return true;
    }
    if (isFull()) {
      return false;
    }
    for (auto& ptr : data_) {
      if (ptr == nullptr)  {
        ptr = new Key(k);
        inicio++;
        return true;
      }
    }
    return false;
  }

  unsigned getSize() {return size_;}

  std::vector<Key*> getData() {return data_;}

  int getInicio() {return inicio;}

  const Key& operator[](const int& p) const {
    return *data_[p];
  }

  Key& operator[](const int& p) {
    return *data_[p];
  }

  friend std::ostream& operator<<(std::ostream& os, staticSequence<Key>& seq) {
    std::vector<Key*> data = seq.getData();
    for (int i = 0; i < seq.getSize(); i++) {
        os << *data[i] << " ";
    }
    return os;
  }

  void swap(int i, int f) {
    Key* temp = data_[i];
    data_[i] = data_[f];
    data_[f] = temp;
  }

 private:
  int inicio;
  unsigned size_;
  std::vector<Key*> data_;
};

#endif