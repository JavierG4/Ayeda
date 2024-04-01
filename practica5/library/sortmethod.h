#include "sequence.h"
#include "nif.h"


template<class Key> 
class SortMethod {
 public:
   SortMethod(const staticSequence<Key>& data, int size) : data_(data), size_(size) {}
   virtual void Sort() const = 0;

 private:
   staticSequence<Key> data_;
   int size_;

};

template <class Key>
class QuickSort : protected SortMethod {
  
}