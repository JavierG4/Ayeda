
#ifndef Nif_H
#define Nif_H

#include <iostream>
#include <random>
#include <cstdlib>
#include <ctime>

class Nif {
private:
  int value;

public:
  Nif();
  Nif(long num);
  bool operator==(const Nif& other) const;
  bool operator==(int) const;
  bool operator!=(const Nif& other) const;
  bool operator<(const Nif& other) const;
  bool operator>(const Nif& other) const;
  bool operator<=(const Nif& other) const;
  bool operator>=(const Nif& other) const;
  operator long() const;
};


#endif // Nif_H