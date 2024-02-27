#ifndef myvector_h
#define myvector_h

#include <iostream>
#include <vector>

class Celula;

/**
 * @class Myvector
 * @brief Clase que representa un vector de objetos de tipo Celula.
 * 
 * Esta clase proporciona métodos para manipular un vector de objetos de tipo Celula.
 * Permite agregar elementos al final o al principio del vector, obtener y establecer
 * elementos en posiciones específicas, obtener el tamaño del vector, entre otras operaciones.
 */
class Myvector {
 public:
   /**
    * @brief Constructor de Myvector que recibe un puntero a una Celula, un índice inicial y un tamaño.
    * @param celula Puntero a una Celula.
    * @param indice_inicial Índice inicial del vector.
    * @param size Tamaño del vector.
    */
   Myvector(Celula*, int, int);

   /**
    * @brief Constructor de Myvector que recibe un tamaño.
    * @param size Tamaño del vector.
    */
   Myvector(int);

   /**
    * @brief Constructor de Myvector sin parámetros.
    */
   Myvector();

   /**
    * @brief Agrega una Celula al final del vector.
    * @param celula Puntero a una Celula.
    */
   void push_back(Celula*);

   /**
    * @brief Agrega una Celula al principio del vector.
    * @param celula Puntero a una Celula.
    */
   void push_front(Celula*);

   /**
    * @brief Establece una Celula en una posición específica del vector.
    * @param index Índice de la posición en la que se establecerá la Celula.
    * @param celula Puntero a una Celula.
    */
   void SetCelula(int, Celula*);

   /**
    * @brief Obtiene la Celula en una posición específica del vector.
    * @param index Índice de la posición de la Celula a obtener.
    * @return Puntero a la Celula en la posición especificada.
    */
   Celula* GetCelula(int);

   /**
    * @brief Obtiene el índice inicial del vector.
    * @return Índice inicial del vector.
    */
   int GetIndiceInicial();

   /**
    * @brief Establece el índice inicial del vector.
    * @param indice_inicial Índice inicial del vector.
    */
   void SetIndiceInicial(int);

   /**
    * @brief Sobrecarga del operador [] para acceder a una Celula en una posición específica del vector.
    * @param index Índice de la posición de la Celula a acceder.
    * @return Referencia a la Celula en la posición especificada.
    */
   Celula*& operator[](int);

   /**
    * @brief Obtiene el tamaño del vector.
    * @return Tamaño del vector.
    */
   int size();

 private:
   std::vector<Celula*> myvector_; ///< Vector de punteros a Celula.
   int indice_inicial_; ///< Índice inicial del vector.
   int size_; ///< Tamaño del vector.
};

#endif