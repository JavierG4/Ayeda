#pragma once

#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string.h>
#include <utility>
#include <set>
#include <vector>

/**
 * @brief Clase que representa una posición.
 * Esta clase representa una posición en un sistema de coordenadas.
 * Permite obtener y modificar la posición.
 */
class Posicion {
 public:
   /**
    * @brief Constructor de la clase Posicion.
    * @param posicion La posición inicial.
    */
   Posicion(int, int);
   /**
    * @brief Constructor por defecto de la clase Posicion.
    * Crea una posición con valor 0.
    */
   Posicion(); 
   
   /**
    * @brief Obtiene la posición actual.
    * @return La posición actual.
    */
   int GetPosicionX();
   /**
    * @brief Obtiene la posición actual.
    * @return La posición actual.
    */
   int GetPosicionY();
   
 private:
   int posicion_x_; /**< La posición actual. */
   int posicion_y_; /**< La posición actual. */
};
