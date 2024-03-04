#include "estado.h"

Estado::Estado(int estado) {
  estado_ = estado;
}

Estado::Estado() {
  estado_ = 0;
}

int Estado::GetEstado() const {
  return estado_;
}

void Estado::SetEstado(int estado) {
  estado_ = estado;
}