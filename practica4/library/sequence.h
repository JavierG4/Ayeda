#ifndef SEQUENCE_H
#define SEQUENCE_H

#include <iostream>
#include <vector>

template<class Key>
class Sequence {
  public: 
    virtual bool search(const Key& k) const = 0;
    virtual bool insert(const Key& k) = 0;
};

template<class Key> 
class dynamicSequence: public Sequence<Key> {
 public:
  dynamicSequence() : data_(std::vector<Key*>()) {} // Inicializa data_ como un vector vacío
  bool search(const Key& k) const;
  bool insert(const Key& k);
  std::vector<Key*> getData() const {return data_;}
 private:
   std::vector<Key*> data_;
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
    data_ = new Key*[size];
    for (int i = 0; i < size; i++) {
      data_[i] = nullptr;
    }
  }
  bool isFull() const;
  bool search(const Key& k) const;
  bool insert(const Key& k);
  unsigned getSize() {return size_;}
  Key** getData() {return data_;}
  int getInicio() {return inicio;}
 private:
  int inicio;
  unsigned size_;
  Key** data_;
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
  if(isFull()) {
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