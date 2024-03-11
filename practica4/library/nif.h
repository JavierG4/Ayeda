
#ifndef NIF_H
#define NIF_H

#include <iostream>
#include <random>
#include <cstdlib>
#include <ctime>

class nif {
private:
  int value;

public:
  nif();
  nif(long num);
  bool operator==(const nif& other) const;
  bool operator!=(const nif& other) const;
  bool operator<(const nif& other) const;
  bool operator>(const nif& other) const;
  bool operator<=(const nif& other) const;
  bool operator>=(const nif& other) const;
  operator long() const;
};


#endif // NIF_H