#include "nif.h"


nif::nif() {
  // Generate a random 8-digit value
  srand(time(0));
  value = rand() % 100000000;
}

nif::nif(long num) : value(num) {}

bool nif::operator==(const nif& other) const {
  return value == other.value;
}

bool nif::operator!=(const nif& other) const {
  return value != other.value;
}

bool nif::operator<(const nif& other) const {
  return value < other.value;
}

bool nif::operator>(const nif& other) const {
  return value > other.value;
}

bool nif::operator<=(const nif& other) const {
  return value <= other.value;
}

bool nif::operator>=(const nif& other) const {
  return value >= other.value;
}

nif::operator long() const {
  return value;
}
