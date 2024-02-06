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
   Posicion(int);
   int GetPosicion();
 private:
   int posicion_;
};