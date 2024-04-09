#include <iostream>
#include "sequence.h"
#include "nif.h"
#include <string>
#include "sortmethod.h"

int main(int argc, char* argv[]) {
  int size = std::stoi(argv[2]);
  int ord = std::stoi(argv[4]);
  int init = std::stoi(argv[6]);
  std::cout << "Size: " << size << std::endl;
  std::cout << "Ord: " << ord << std::endl;
  std::cout << "Init: " << init << std::endl;
  int i = 0;
  std::string file;
  if (init == 2 ) {
    i++;
    file = std::stoi(argv[7]);
  }
  int trace = std::stoi(argv[i + 8]); // 0 = no, 1 = yes
  SortMethod<Nif>* algoritmo;
  SortMethod<Nif>* algoritmo1;
  SortMethod<Nif>* algoritmo2;
  SortMethod<Nif>* algoritmo3;
  SortMethod<Nif>* algoritmo4;
  staticSequence<Nif> data(size);
  std::vector<SortMethod<Nif>*> algoritmos;
  algoritmo = new Seleccion<Nif>(data, size, init);
  algoritmo1 = new QuickSort<Nif>(data, size, init);
  algoritmo2 = new HeapSort<Nif>(data, size, init);
  algoritmo3 = new ShellSort<Nif>(data, size, init);
  algoritmo4 = new RadixSort<Nif>(data, size, init);
  algoritmos.push_back(algoritmo);
  algoritmos.push_back(algoritmo1);
  algoritmos.push_back(algoritmo2);
  algoritmos.push_back(algoritmo3);
  algoritmos.push_back(algoritmo4);

  for (int i = 0; i < algoritmos.size(); i++) {
    algoritmos[i]->Sort();
  }

  delete algoritmo;
  delete algoritmo1;
  delete algoritmo2;
  delete algoritmo3;
  delete algoritmo4;

  return 0;
}