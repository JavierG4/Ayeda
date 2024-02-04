// Universidad de La Laguna
// Escuela Superior de Ingenier´ıa y Tecnolog´ıa
// Grado en Ingenier´ıa Inform´atica
// Asignatura: Computabilidad y Algoritmia
// Curso: 2º
// Pr´actica 5:mplementación de un simulador de autómatas finitos 
// Autor: Javier González Brito
// Correo: alu0101548197@ull.edu.es
// Fecha: 17/09/2023
// Archivo alfabeto.h
// Contiene la implementacion de la clase alfabeto
// Enlaces de inter´es
// Historial de revisiones
// 14/09/2023 - Creaci´on (primera versi´on) del c´odigo
#ifndef ALFABETO_H
#define ALAFABETO_H

#include<iostream>
#include<stdlib.h>
#include<fstream>
#include <string.h>
#include <utility>
#include <set>
#include <vector>

class Alfabeto{
 public:
   void remove_set();                          // Brief@ funcion que se encarga de vaciar el set
                                               // parametros ninguno
   //void print_set();    // Brief@ funcion que se encarga de imprimir el set
                                               // param1 Archivo de entrada, param2 archivo de salida
   std::set<char> get_set();                   // Brief@ funcion que se encarga de devolver el valor del set privado
                                               // parametros ninguno
   void set_set(std::set<char>);
   void set_valor(char);
 private:
   std::set<char> alfabeto_;                   //set, atributo privado
};
std::ostream& operator<<(std::ostream&,Alfabeto&);  // Sobrecarga de operador de salida, para imprimir los datos del set

#endif  // ALFABETO_H