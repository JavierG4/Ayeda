#include "nif.h"


Nif::Nif() {
  // Generate a random 8-digit value
  srand(time(0));
  value = rand() % 100000000;
}

Nif::Nif(long num) : value(num) {}

bool Nif::operator==(const Nif& other) const {
  std::cout << value << " == " << other.value << std::endl;
  return value == other.value;
}

bool Nif::operator!=(const Nif& other) const {
  return value != other.value;
}

bool Nif::operator<(const Nif& other) const {
  return value < other.value;
}

bool Nif::operator>(const Nif& other) const {
  return value > other.value;
}

bool Nif::operator<=(const Nif& other) const {
  return value <= other.value;
}

bool Nif::operator>=(const Nif& other) const {
  return value >= other.value;
}

Nif::operator long() const {
  return value;
}

bool Nif::operator==(unsigned num) const {
  return value == num;
}