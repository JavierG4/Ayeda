#ifndef celula_h
#define celula_h

#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string.h>
#include <utility>
#include <set>
#include <vector>
#include "estado.h"
#include "position.h"
#include "latice.h"
//#include "myvector.h"

class Latice;

/**
 * @file celula.h
 * @brief Definición de la clase Celula.
 */

/**
 * @class Celula
 * @brief Clase que representa una célula en un sistema de simulación.
 */
class Celula {
 public:
  /**
   * @brief Constructor de la clase Celula.
   * @param pos La posición de la célula en el sistema.
   * @param estado El estado inicial de la célula.
   */
  Celula(Position& pos, const Estado& estado);

  ~Celula();

  /**
   * @brief Obtiene el estado actual de la célula.
   * @return El estado actual de la célula.
   */
  Estado GetEstado() const;

  /**
   * @brief Establece el estado actual de la célula.
   * @param estado El nuevo estado de la célula.
   */
  void SetEstado(Estado estado);

  /**
   * @brief Establece el estado siguiente de la célula.
   * @param estado El estado siguiente de la célula.
   */
  void SetEstadoSiguiente(Estado estado);

  /**
   * @brief Calcula el siguiente estado de la célula.
   * @param latice El sistema de células en el que se encuentra la célula.
   * @return El siguiente estado de la célula.
   */
  virtual int NextState(Latice& latice) = 0;

  /**
   * @brief Actualiza el estado actual de la célula al estado siguiente.
   */
  virtual void UpdateState() = 0;

  /**
   * @brief Obtiene la posición de la célula en el sistema.
   * @return La posición de la célula.
   */
  Position* GetPosition() const;

  /**
   * @brief Obtiene el estado siguiente de la célula.
   * @return El estado siguiente de la célula.
   */
  Estado GetEstadoSiguinte() const;

 protected:
   Estado estado_; /**< El estado actual de la célula. */
   Position* pos_; /**< La posición de la célula en el sistema. */
   Estado estado_siguiente_; /**< El estado siguiente de la célula. */
};



#endif 