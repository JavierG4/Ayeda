#ifndef FUNCTION_H
#define FUNCTION_H

#include <iostream>
#include <cmath>

/**
 * @class DispersionFunction
 * @brief Clase base abstracta para las funciones de dispersión.
 * @tparam Key Tipo de la clave que se dispersará.
 */
template<class Key>
class DispersionFunction {
 public:
   /**
    * @brief Operador que realiza la dispersión de la clave.
    * @param k Clave a dispersar.
    * @return Valor de dispersión de la clave.
    */
   virtual unsigned operator()(const Key& k) const = 0;
};

/**
 * @class Modulo
 * @brief Clase que implementa una función de dispersión mediante el operador módulo.
 * @tparam Key Tipo de la clave que se dispersará.
 */
template<class Key>
class Modulo : public DispersionFunction<Key> {
 public:
   /**
    * @brief Constructor que establece el divisor para el operador módulo.
    * @param n Divisor para el operador módulo.
    */
   Modulo(unsigned n) : n_(n) {}

   /**
    * @brief Realiza la dispersión de la clave mediante el operador módulo.
    * @param k Clave a dispersar.
    * @return Valor de dispersión de la clave.
    */
   unsigned operator()(const Key& k) const {
     return k % n_;
   }

 private:
   unsigned n_; ///< Divisor para el operador módulo.
};

/**
 * @class PseudoRandom
 * @brief Clase que implementa una función de dispersión pseudoaleatoria.
 * @tparam Key Tipo de la clave que se dispersará.
 */
template<class Key>
class PseudoRandom : public DispersionFunction<Key> {
 public:
   /**
    * @brief Constructor que establece el divisor para el número pseudoaleatorio.
    * @param n Divisor para el número pseudoaleatorio.
    */
   PseudoRandom(unsigned n) : n_(n) {}

   /**
    * @brief Realiza la dispersión de la clave generando un número pseudoaleatorio.
    * @param k Clave a dispersar.
    * @return Valor de dispersión de la clave.
    */
   unsigned operator()(const Key& k) const {
     std::srand(k);
     return std::rand() % n_;
   }

 private:
   unsigned n_; ///< Divisor para el número pseudoaleatorio.
};


/**
 * @class Sum
 * @brief A class that represents a sum-based dispersion function.
 * @tparam Key The type of the key used for dispersion.
 */
template<class Key>
class Sum : public DispersionFunction<Key> {
 public:
   /**
    * @brief Constructor for the Sum class.
    * @param n The size of the hash table.
    */
   Sum(unsigned n) : n_(n) {}

   /**
    * @brief Calculates the dispersion value for a given key.
    * @param k The key for which to calculate the dispersion value.
    * @return The calculated dispersion value.
    */
   unsigned operator()(const Key& k) const {
     unsigned sum = 0;
     unsigned key = k.get();
     while (key > 0) {
       sum += key % 10;
       key /= 10;
     }
     return sum % n_;
   }

 private:
   unsigned n_; /**< The size of the hash table. */
};

/**
 * @class ExplorationFunction
 * @brief Clase base abstracta para las funciones de exploración.
 * @tparam Key Tipo de la clave que se explorará.
 */
template<class Key>
class ExplorationFunction {
 public: 
   /**
    * @brief Constructor que establece el módulo para la exploración.
    * @param n Módulo para la exploración.
    */
   ExplorationFunction(unsigned n) : modulo_(n) {}

   /**
    * @brief Operador que realiza la exploración de la clave.
    * @param k Clave a explorar.
    * @param i Índice de exploración.
    * @return Valor de exploración de la clave.
    */
   virtual unsigned operator()(const Key&, unsigned) const=0; 

 protected:
  unsigned modulo_; ///< Módulo para la exploración.
};

/**
 * @class LinearExploration
 * @brief Clase que implementa una función de exploración lineal.
 * @tparam Key Tipo de la clave que se explorará.
 */
template<class Key>
class LinearExploration : public ExplorationFunction<Key> {
 public:
   using ExplorationFunction<Key>::modulo_;

   /**
    * @brief Constructor que establece el módulo para la exploración lineal.
    * @param n Módulo para la exploración lineal.
    */
   LinearExploration(unsigned n) : ExplorationFunction<Key>(n) {}

   /**
    * @brief Realiza la exploración de la clave de manera lineal.
    * @param k Clave a explorar.
    * @param i Índice de exploración.
    * @return Valor de exploración de la clave.
    */
   unsigned operator()(const Key&, unsigned i) const {
      return i;
   }
};

/**
 * @class QuadraticExploration
 * @brief Clase que implementa una función de exploración cuadrática.
 * @tparam Key Tipo de la clave que se explorará.
 */
template<class Key>
class QuadraticExploration : public ExplorationFunction<Key> {
 public:
   using ExplorationFunction<Key>::modulo_;

   /**
    * @brief Constructor que establece el módulo para la exploración cuadrática.
    * @param n Módulo para la exploración cuadrática.
    */
   QuadraticExploration(unsigned n) : ExplorationFunction<Key>(n) {}

   /**
    * @brief Realiza la exploración de la clave de manera cuadrática.
    * @param k Clave a explorar.
    * @param i Índice de exploración.
    * @return Valor de exploración de la clave.
    */
   unsigned operator()(const Key&, unsigned i) const {
    return  i * i;
   }
};


/**
 * @class DoubleDispersion
 * @brief A class that represents a double dispersion exploration function.
 * @tparam Key The type of the key.
 */
template<class Key>
class DoubleDispersion : public ExplorationFunction<Key> {
 public:
  /**
   * @brief Constructs a DoubleDispersion object.
   * @param n The size of the exploration function.
   * @param dispersion The dispersion function to be used.
   */
  DoubleDispersion(unsigned n, DispersionFunction<Key>& dispersion) 
  : ExplorationFunction<Key>(n), dispersion_(dispersion) {}

  /**
   * @brief Calculates the exploration value for a given key and index.
   * @param k The key for which the exploration value is calculated.
   * @param i The index of the exploration value.
   * @return The exploration value.
   */
   unsigned operator()(const Key& k, unsigned i) const {
     return dispersion_(k) * i;
   }

 private:
   DispersionFunction<Key>& dispersion_; /**< The dispersion function. */
};


/**
 * @brief The Redispersion class represents a redispersion function used in exploration.
 * 
 * This class calculates the displacement of a key based on a random number generator.
 * The displacement is determined by iterating over a given number of times and generating random numbers.
 */
template<class Key>
class Redispersion : public ExplorationFunction<Key> {
 public:
   /**
    * @brief Constructs a Redispersion object with a given number of iterations and a dispersion function.
    * 
    * @param n The number of iterations.
    * @param dispersion The dispersion function used to calculate the displacement.
    */
   Redispersion(unsigned n) : ExplorationFunction<Key>(n) {}

   /**
    * @brief Calculates the displacement of a key based on the given index.
    * 
    * @param k The key for which the displacement is calculated.
    * @param i The index used to determine the number of iterations.
    * @return The displacement of the key.
    */
   unsigned operator()(const Key& k, unsigned i) const {
     srand(long(k));
     unsigned displacement = 0;
     for (unsigned j = 0; j < i; j++) {
       displacement = rand();
     }
     return displacement;
   }
};

#endif
