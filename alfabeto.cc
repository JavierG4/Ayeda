#include "alfabeto.h"

void Alfabeto::remove_set() {
  std::set<char> set = alfabeto_;
  for (auto& carcater : set) {
    alfabeto_.erase(carcater);
  }
}


std::ostream& operator<<(std::ostream& out, Alfabeto& a) {
	out << "{";
  auto iterador = a.get_set().rbegin(); 
	for (auto i : a.get_set()) { 
		if (*iterador == i) {
			out << i;
			continue;
		}
		out << i << ", ";
	}
	out << "}" << std::endl;
  return out;
}

std::set<char> Alfabeto::get_set() {
  return alfabeto_;
}

void Alfabeto::set_set(std::set<char> set){
	alfabeto_ = set;
}

void Alfabeto::set_valor(char symbol){
	alfabeto_.insert(symbol);
}