#ifndef latice_h
#define latice_h

#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <utility>
#include <set>
#include <vector>
#include "celula.h"
#include <ostream>

class Celula;

/**
 * @class Latice
 * @brief Clase que representa una red de células.
 */
class Latice {
 public:
   /**
    * @brief Constructor de la clase Latice.
    * @param num_celulas El número de células en la red.
    * @param frontera El tipo de frontera de la red (0 = abierta fría, 1 = abierta caliente, 2 = periódica).
    * @param nombre_archivo El nombre del archivo de configuración de la red.
    */
   Latice(int num_celulas, int frontera, std::string nombre_archivo);

   /**
    * @brief Destructor de la clase Latice.
    */
   ~Latice();

   /**
    * @brief Obtiene el número de células en la red.
    * @return El número de células en la red.
    */
   int GetNumCelula();

   /**
    * @brief Obtiene el tipo de frontera de la red.
    * @return El tipo de frontera de la red (0 = abierta fría, 1 = abierta caliente, 2 = periódica).
    */
   int GetFrontera();

   /**
    * @brief Calcula la siguiente generación de la red.
    */
   void NextGeneration();

   /**
    * @brief Sobrecarga del operador [] para acceder a una célula específica en la red.
    * @param index El índice de la célula a acceder.
    * @return Una referencia a la célula en el índice especificado.
    */
   Celula& operator[](int index);

   /**
    * @brief Imprime la red en la consola.
    * @param generacion La generación actual de la red.
    */
   void PrintLatice(int generacion);

 private:
   std::vector<Celula*> latice_; ///< Vector que almacena las células de la red.
   int numero_celulas_; ///< Número de células en la red.
   int frontera_; ///< Tipo de frontera de la red (0 = abierta fría, 1 = abierta caliente, 2 = periódica).
};

#endif 