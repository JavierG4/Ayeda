#ifndef FUNCTION_H
#define FUNCTION_H

#include <iostream>

template<class Key>
class DispersionFunction {
 public:
   virtual unsigned operator()(const Key&) const = 0;
};

template<class Key>
class Modulo : public DispersionFunction<Key> {
 public:
   Modulo(unsigned n) : n_(n) {}
   unsigned operator()(const Key& k) const {
     return k % n_;
   }
 private:
   unsigned n_;
};

template<class Key>
class PseudoRandom : public DispersionFunction<Key> {
 public:
   PseudoRandom(unsigned n) : n_(n) {}
   unsigned operator()(const Key& k) const {
     std::srand(k);
     return std::rand() % n_;
   }
 private:
   unsigned n_;
};

template<class Key>
class ExplorationFunction {
 public:
   virtual unsigned operator()(const Key&, unsigned) const=0;
};

#endif
