#pragma once

#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string.h>
#include <utility>
#include <set>
#include <vector>

/**
 * @class Estado
 * @brief Clase que representa un estado.
 *
 * Esta clase representa un estado y proporciona métodos para obtener y establecer el estado.
 */
class Estado {
 public:
   /**
    * @brief Constructor de la clase Estado.
    * @param estado El estado a asignar.
    */
   Estado(int estado);

   /**
    * @brief Constructor por defecto de la clase Estado.
    */
   Estado();

   /**
    * @brief Obtiene el estado actual.
    * @return El estado actual.
    */
   int GetEstado() const;

   /**
    * @brief Establece el estado.
    * @param estado El estado a establecer.
    */
   void SetEstado(int estado);

 private:
  int estado_; /**< El estado actual. */
};