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
    void Push_back(Myvector);
    void Push_front(Myvector);
    int GetFilas();
    int GetColumnas();
    void resize(int);
    int GetIndiceInicial();
    int GetSize();
    friend std::ostream& operator<<(std::ostream&, Matriz&);
 private:
   std::vector<Myvector> matriz_;
   int size_;
   int indice_inicial_;
   int numero_celulas_;
   int filas_;
   int columnas_;
};


#endif