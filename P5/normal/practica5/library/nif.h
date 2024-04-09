
#ifndef Nif_H
#define Nif_H

#include <iostream>
#include <random>
#include <cstdlib>
#include <ctime>

/**
 * @class Nif
 * @brief Clase que representa un Número de Identificación Fiscal (NIF).
 */
class Nif {
 public:
  /**
   * @brief Constructor por defecto que inicializa el NIF.
   */
  Nif();

  /**
   * @brief Constructor que inicializa el NIF con un valor numérico.
   * @param num Valor numérico del NIF.
   */
  Nif(long num);

  /**
   * @brief Compara este NIF con otro.
   * @param other Otro NIF con el que comparar.
   * @return Verdadero si los NIF son iguales, falso en caso contrario.
   */
  bool operator==(const Nif& other) const;

  bool operator<(const Nif& other) const;
  bool operator>(const Nif& other) const;
  bool operator!=(const Nif& other) const;

  /**
   * @brief Compara este NIF con un valor numérico.
   * @param num Valor numérico con el que comparar.
   * @return Verdadero si el NIF es igual al valor numérico, falso en caso contrario.
   */
  bool operator==(unsigned) const;

  /**
   * @brief Obtiene el valor del NIF.
   * @return Valor del NIF.
   */
  int get() const {return value;}

  /**
   * @brief Convierte el NIF a un valor numérico.
   * @return Valor numérico del NIF.
   */
  operator long() const;

 private:
  unsigned value; ///< Valor del NIF.
  static bool init() {
    srand(time(0));
    return true;
  }
};


#endif // Nif_H