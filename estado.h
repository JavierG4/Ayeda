#pragma once

#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string.h>
#include <utility>
#include <set>
#include <vector>

class Estado {
 public:
   Estado(int estado);
   Estado();
   int GetEstado() const;
   void SetEstado(int estado);
 private:
  int estado_;
};