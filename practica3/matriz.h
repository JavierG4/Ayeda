#ifndef matriz_h
#define matriz_h
#include <iostream>
#include "myvector.h"

class Myvector;

/**
 * @class Matriz
 * @brief Clase que representa una matriz.
 *
 * La clase Matriz permite almacenar y manipular una matriz de Myvector.
 * Proporciona métodos para acceder a los elementos de la matriz, agregar
 * vectores al final o al principio, obtener el número de filas y columnas,
 * redimensionar la matriz, obtener el índice inicial y el tamaño total.
 */
class Matriz {
 public:
    /**
     * @brief Constructor de la clase Matriz.
     * @param filas El número de filas de la matriz.
     * @param columnas El número de columnas de la matriz.
     * @param indice_inicial El índice inicial de la matriz.
     */
    Matriz(int filas, int columnas, int indice_inicial);

    /**
     * @brief Constructor por defecto de la clase Matriz.
     */
    Matriz();

    /**
     * @brief Operador de acceso a los elementos de la matriz.
     * @param index El índice de la fila a acceder.
     * @return Una referencia al vector de la fila especificada.
     */
    const Myvector& operator[](int index) const;

    /**
     * @brief Agrega un vector al final de la matriz.
     * @param vector El vector a agregar.
     */
    void Push_back(Myvector vector);

    /**
     * @brief Agrega un vector al principio de la matriz.
     * @param vector El vector a agregar.
     */
    void Push_front(Myvector vector);

    /**
     * @brief Obtiene el número de filas de la matriz.
     * @return El número de filas.
     */
    int GetFilas() const;

    /**
     * @brief Obtiene el número de columnas de la matriz.
     * @return El número de columnas.
     */
    int GetColumnas() const;

    /**
     * @brief Redimensiona la matriz.
     * @param size El nuevo tamaño de la matriz.
     */
    void resize(int size);

    /**
     * @brief Obtiene el índice inicial de la matriz.
     * @return El índice inicial.
     */
    int GetIndiceInicial();

    /**
     * @brief Obtiene el tamaño total de la matriz.
     * @return El tamaño total.
     */
    int GetSize();

 private:
   std::vector<Myvector> matriz_; ///< Vector que almacena los vectores de la matriz.
   int size_; ///< Tamaño total de la matriz.
   int indice_inicial_; ///< Índice inicial de la matriz.
   int numero_celulas_; ///< Número total de celdas en la matriz.
   int filas_; ///< Número de filas de la matriz.
   int columnas_; ///< Número de columnas de la matriz.
};


#endif