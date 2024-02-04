#pragma once
#include "latice.h"

Latice::Latice(int n) {
  numero_celulas_ = n;
  latice_ = new Celula[n];
}

Latice::~Latice() {
  delete[] latice_;
}



