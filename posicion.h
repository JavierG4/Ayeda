#pragma once

#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string.h>
#include <utility>
#include <set>
#include <vector>

class Posicion {
 public:
   Posicion(int,int,int);
   Posicion();
   std::vector<int> GetVecindad() const;
 private:
   std::vector<int> vecindad;
}