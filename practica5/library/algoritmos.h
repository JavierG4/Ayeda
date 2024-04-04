#include "sequence.h"
#include "nif.h"
#include <vector>
#include <algorithm>

template <class Key>
void quickSort(staticSequence<Key>& data, int size) {
  Qsort(data, 0, data.getSize() - 1);
}

template <class Key>
void Qsort(staticSequence<Key>& data, int inicio, int fin) {
  int i = inicio;
  bool trace = true;
  //std::cout << inicio << std::endl;
  int f = fin;
  //std::cout << "e" << std::endl;
  int medio = (i+f)/2;
  //std::cout << medio << std::endl;
  Key p = data[medio];
  //std::cout << "t" << std::endl;
  while (i <= f) {
    while (data[i] < p) {
      i++;
    }
    while (data[f] > p) {
      f--;
    }
    if (i <= f) {
      data.swap(i, f);
      i++;
      f--;
      std::cout << "Se hace swap de " << data[i] << " y " << data[f] << std::endl;
      std::cout << data << std::endl;
    }
  }
  if (inicio < f) {
    //std::cout << data << std::endl;
    Qsort(data, inicio, f);
  }
  if (i < fin) {
    //std::cout << data << std::endl;
    Qsort(data, i, fin);
  }
}

template <class Key>
void heapSort(staticSequence<Key>& data, int n) {
  for (int i = n/2 - 1; i >= 0; i--) { 
    baja(i, data, n);
    std::cout << data << std::endl;
  }
  for (int i = n - 1; i > 0; i--) {
    data.swap(0,i);
    baja(0,data,i);
    std::cout << data << std::endl;
  }
}

template <class Key>
void baja(int i,staticSequence<Key>& data, int n) {
  int h1, h2, h;
  while (2*i + 1 < n) {
    h1 = 2*i + 1; 
    h2 = h1 + 1;
    if (h1 >= n) {
      break;
    }
    if (h2 >= n || data[h1] > data[h2]) {
      h = h1; 
    } else {
      h = h2;
    }
    if (data[h] <= data[i]) {
      break; 
    } else {
      data.swap(i, h);
      i = h;
    }
  }
}

template <class Key>
void seleccionSort(staticSequence<Key>& sec, int n) {
  bool trace = true;
  for (int i = 0; i < n-1; i++) {
    int min = i;
    for (int j = i+1; j < n; j++) {
      if (sec[j] < sec[min]) {
        min = j;
      }
    }
    Key x = sec[min];
    sec[min] = sec[i];
    sec[i] = x;
    if ( trace ) {
      std::cout << "Iteración " << i << ": ";
      std::cout << sec << std::endl;
    }
  }
}

template <class Key>
void radixSort(staticSequence<Key>& data, int size) {
  // Encuentra el número máximo para conocer el número de dígitos
  Key maxVal = data[0];
  for (int i = 1; i < size; i++) {
    if (data[i] > maxVal) {
      maxVal = data[i];
    }
  }

  // Realiza una iteración para cada dígito. En lugar de usar el número de dígitos de maxVal,
  // se usa log(maxVal) para obtener el número de dígitos
  for (int exp = 1; maxVal/exp > 0; exp *= 10) {
    std::vector<Key> output(size); // Vector de salida
    int i, count[10] = {0};

    // Almacena el recuento de ocurrencias en count[]
    for (i = 0; i < size; i++) { 
      count[ (data[i]/exp)%10 ]++;
    }
    // Cambia count[i] para que count[i] ahora contenga la posición actual de este dígito en output[]
    for (i = 1; i < 10; i++) { 
      count[i] += count[i - 1];
    }
    // Construye el vector de salida
    for (i = size - 1; i >= 0; i--) {
      output[count[ (data[i]/exp)%10 ] - 1] = data[i];
      count[ (data[i]/exp)%10 ]--;
    }

    // Copia el vector de salida a data[], para que data[] contenga los números ordenados
    for (i = 0; i < size; i++) { 
      data[i] = output[i];
    }
    std::cout << data << std::endl;
  }
}

template <class Key>
void shellSort(staticSequence<Key>& data, int n) {
  int delta = n ;
  while (delta > 1) {
    delta = delta / 2;
    deltasort(delta,data, n);
  }
} 

template <class Key>
void deltasort(int delta, staticSequence<Key>& sec, int n) {
  for (int i = delta; i < n; i++) {
    Key x = sec[i];
    int j = i;
    while (j >= delta && x < sec[j - delta]) {
      sec[j] = sec[j - delta];
      j = j - delta;
    }
    sec[j] = x;
    std::cout << sec << std::endl;
  }
}