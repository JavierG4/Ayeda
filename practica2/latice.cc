#include "latice.h"
#include <iostream> // Add this line
#include <termios.h>
#include <unistd.h>

int getch() {
  struct termios oldattr, newattr;
  int ch;
  tcgetattr(STDIN_FILENO, &oldattr);
  newattr = oldattr;
  newattr.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newattr);
  ch = getchar();
  tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);
  return ch;
}

Latice::Latice(int filas, int columnas, int frontera) {
  numero_celulas_ = columnas * filas;
  frontera_ = frontera;
  latice_ = Myvector<Myvector<Celula*>>(filas);
  for (int i = 0; i < filas; i++) {
    Myvector<Celula*> fila(columnas);
    for (int j = 0; j < columnas; j++) {
      int estado = PreguntarEstado(i, j);
      Celula* celula = new Celula(Posicion(i, j), Estado(estado));
      fila.push_back(celula);
    }
    latice_[i] = fila;
  }
}

Latice::~Latice() {
  for (int i = 0; i < latice_.size(); i++) {
    for (int j = 0; i < latice_[i].size(); j++) {
      delete latice_[i][j];
    }
  }
}

int PreguntarEstado(int x, int y) {
  int estado;
  std::cout << "Introduzca el estado de la célula: (" << x << ", " << y << ")";
  std::cin >> estado;
  return estado;
}

void Latice::NextGeneration() {
  
}

void Latice::PrintLatice() {
  for (int i = 0; i < latice_.size(); i++) {
    for (int j = 0; j < latice_[i].size(); j++) {
      std::cout << latice_[i][j] -> GetEstado().GetEstado() << " ";
    }
    std::cout << std::endl;
  }
}

int Latice::GetNumCelula() {
  return numero_celulas_;
}

int Latice::GetFrontera() {
  return frontera_;
} 

/*Celula& Latice::operator[](int i) {
  return *latice_[i];
}
*/

std::size_t Latice::Population()  {
  int population = 0;
  for ( int i = 0; i < latice_.size(); i++ ) { // Accedo a cada fila , es decir cada Myvector<celula*>
    for ( int j = 0; j < latice_[i].size(); j++ ) { // Accedo a cada columna, es decir cada celula* y accedo a lo que apunta y le hago un get
      if ( latice_[i][j] -> GetEstado().GetEstado() == 1 ) {
        population++;
      }
    }
  }
  return population;
}