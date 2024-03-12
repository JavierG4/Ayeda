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
  dynamicSequence() {}
  bool search(const Key& k) const;
  bool insert(const Key& k);
  std::vector<Key> getData() const {return data_;}
 private:
   std::vector<Key> data_;
};

template<class Key> 
class staticSequence: public Sequence<Key> {
 public:
  staticSequence(unsigned size) {
    size_ = size;
    data_ = new Key[size];
  }
  ~staticSequence() {
    delete[] data_;
  }
  bool isFull() const;
  bool search(const Key& k) const;
  bool insert(const Key& k);
 private:
  unsigned size_;
  Key* data_;
};

template<class Key>
bool dynamicSequence<Key>::search(const Key& k) const {
  for (int i = 0; i < data_.size(); i++) {
    if (data_[i] == k) {
      return true;
    }
  }
  return false;
}

template<class Key>
bool dynamicSequence<Key>::insert(const Key& k) {
  data_.push_back(k);
  return true;
}

template<class Key>
bool staticSequence<Key>::isFull() const {
  for (int i = 0; i < size_; i++) {
    if (data_[i] == 0) {
      return false;
    }
  }
  return true;
}

template<class Key>
bool staticSequence<Key>::search(const Key& k) const {
  for ( int i = 0; i < size_; i++ ) {
    if (data_[i] == k) {
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
    if (data_[i] == 0) {
      data_[i] = k;
      return true;
    }
  }
  return false;
}

#endif