#include <iostream>

class DispersionFunction<Key> {
 public:
   virtual unsigned operator()(const Key&) const = 0;
};


class ExplorationFunction<Key> {
 public:
   virtual unsigned operator()(const Key&, unsigned) const=0;
};