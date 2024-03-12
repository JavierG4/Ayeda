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
class Sum : public DispersionFunction<Key> {
 public:
   Sum(unsigned n) : n_(n) {}
   unsigned operator()(const Key& k) const {
     unsigned sum = 0;
     for (unsigned i = 0; i < sizeof(k); i++) {
       sum += k % 10;
       k /= 10;
     }
     return sum % n_;
   }
 private:
   unsigned n_;
};

template<class Key>
class ExplorationFunction {
 public: 
   ExplorationFunction(unsigned n) : modulo_(n) {}
   virtual unsigned operator()(const Key&, unsigned) const=0; 
 protected:
  unsigned modulo_;
};

template<class Key>
class LinearExploration : public ExplorationFunction<Key> {
 public:
   using ExplorationFunction<Key>::modulo_;
   LinearExploration(unsigned n) : ExplorationFunction<Key>(n) {}
   unsigned operator()(const Key&, unsigned i) const {
     return i;
   }
};

template<class Key>
class QuadraticExploration : public ExplorationFunction<Key> {
 public:
   using ExplorationFunction<Key>::modulo_;
   QuadraticExploration(unsigned n) : ExplorationFunction<Key>(n) {}
   unsigned operator()(const Key&, unsigned i) const {
     return i * i;
   }
};

template<class Key>
class DoubleDispersion : public ExplorationFunction<Key> {
 public:
   DoubleDispersion(unsigned n, DispersionFunction<Key>& dispersion) : ExplorationFunction<Key>(n), dispersion_(dispersion) {}
   unsigned operator()(const Key& k, unsigned i) const {
     return dispersion_(k) * i;
   }
 private:
   DispersionFunction<Key>& dispersion_;
};

template<class Key>
class Redispersion : public ExplorationFunction<Key> {
 public:
   Redispersion(unsigned n, DispersionFunction<Key>& dispersion) : ExplorationFunction<Key>(n), dispersion_(dispersion) {}
   unsigned operator()(const Key& k, unsigned i) const {
     return dispersion_(i);
   }
 private:
   DispersionFunction<Key>& dispersion_;
};


#endif
