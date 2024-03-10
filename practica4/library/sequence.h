#include <iostream>

class Sequence<Key> {
  public: 
    virtual bool search(const Key& k) const = 0;
    virtual bool insert(const Key& k) = 0;
}

template<class Key> class dynamicSequence: public Sequence<Key> {
 public:
   virtual bool isFull() const = 0;
}

template<class Key> class staticSequence: public Sequence<Key> {
 public:


}