#ifndef latice2d_h
#define latice2d_h

#include "latice.h"

class latice2d : public Latice {
 public:
  latice2d(int x, int y) : Latice(x, y) {}
  void SetCelula(int x, int y, Celula* celula);
  Celula* GetCelula(int x, int y);
  void UpdateState();
  void Print();
};



#endif