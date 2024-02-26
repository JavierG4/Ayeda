#ifndef latice_h
#define latice_h

#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <utility>
#include <set>
#include <vector>
#include "myvector.h"
#include "celula.h"
#include "matriz.h"

class Celula;

/**
 * @brief Clase que representa una red de células.
 */
class Latice {
 public:
   /**
    * @brief Constructor de la clase Latice.
    * @param filas El número de filas de la red.
    * @param columnas El número de columnas de la red.
    * @param frontera El tipo de frontera de la red (0 = abierta fría, 1 = abierta caliente, 2 = periódica).
    */
   Latice(int filas, int columnas, int frontera);

   /**
    * @brief Constructor de la clase Latice.
    * @param archivo El nombre del archivo que contiene la configuración inicial de la red.
    * @param frontera El tipo de frontera de la red (0 = abierta fría, 1 = abierta caliente, 2 = periódica).
    */
   Latice(std::string archivo, int frontera);

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
    * @brief Sobrecarga del operador [] para acceder a una célula en una posición dada.
    * @param pos La posición de la célula.
    * @return La célula en la posición dada.
    */
   Celula& operator[](Posicion pos);

   /**
    * @brief Obtiene el tamaño de la población actual en la red.
    * @return El tamaño de la población actual en la red.
    */
   std::size_t Population();

   /**
    * @brief Pregunta el estado de una célula en una posición dada.
    * @param fila La fila de la célula.
    * @param columna La columna de la célula.
    * @return El estado de la célula en la posición dada.
    */
   int PreguntarEstado(int fila, int columna);

   /**
    * @brief Comprueba si una célula está viva o muerta.
    */
   void Comprobar();

   /**
    * @brief Obtiene una referencia a una célula en una posición dada.
    * @param fila La fila de la célula.
    * @param columna La columna de la célula.
    * @return Una referencia a la célula en la posición dada.
    */
   Celula& GetCell(int fila, int columna);

   /**
    * @brief Sobrecarga del operador de inserción para imprimir la red en un flujo de salida.
    * @param os El flujo de salida.
    * @param latice La red a imprimir.
    * @return El flujo de salida.
    */
   friend std::ostream& operator<<(std::ostream& os, Latice& latice);

   /**
    * @brief Obtiene la matriz que representa la red.
    * @return La matriz que representa la red.
    */
   Matriz GetMatriz();

   /**
    * @brief Imprime las instrucciones del juego de la vida.
    */
   void PrintInstrucciones();

   /**
    * @brief Imprime la configuración actual de la red.
    */
   void PrintLatice();

   /**
    * @brief Comprueba si una célula tiene al menos un vecino vivo.
    * @param estado El estado de la célula.
    * @return true si la célula tiene al menos un vecino vivo, false en caso contrario.
    */
   bool Alrededor(int estado);

 private:
   Matriz latice_; // La matriz que representa la red
   int numero_celulas_; // El número de células en la red
   int frontera_; // El tipo de frontera de la red (0 = abierta fría, 1 = abierta caliente, 2 = periódica)
};

#endif 