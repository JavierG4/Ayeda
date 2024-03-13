
#ifndef Nif_H
#define Nif_H

#include <iostream>
#include <random>
#include <cstdlib>
#include <ctime>

class Nif {
 public:
  Nif();
  Nif(long num);
  bool operator==(const Nif& other) const;
  bool operator==(unsigned) const;
  bool operator!=(const Nif& other) const;
  bool operator<(const Nif& other) const;
  bool operator>(const Nif& other) const;
  bool operator<=(const Nif& other) const;
  bool operator>=(const Nif& other) const;
  int get() const {return value;}
  operator long() const;
 private:
  unsigned value;
};


#endif // Nif_H