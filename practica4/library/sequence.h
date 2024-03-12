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
  dynamicSequence();
  bool search(const Key& k) const;
  bool insert(const Key& k);
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

#endif