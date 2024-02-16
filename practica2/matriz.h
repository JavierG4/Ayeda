#ifndef matriz_h
#define matriz_h
#include <iostream>
#include "myvector.h"


class Myvector;

class Matriz {
 public:
    Matriz(int,int,int);
    Matriz();
    Myvector& operator[](int);
    int GetFilas();
    int GetColumnas();
    void resize(int);
 private:
   std::vector<Myvector> matriz_;
   int size_;
   int indice_inicial_;
   int numero_celulas_;
   int filas_;
   int columnas_;
};


#endif