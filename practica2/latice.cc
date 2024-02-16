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
  //std::cout << "j2" ;
  latice_ = Matriz(filas, columnas, numero_celulas_);
  //std::cout << "i" ;
  for (int i = 0; i < filas; i++) {
    for (int j = 0; j < columnas; j++) {
      //std::cout << "j" ;
      latice_[i][j] = new Celula(Posicion(i,j),Estado(PreguntarEstado(i, j)));
    }
  }
}

Latice::~Latice() {
  for (int i = 0; i < latice_.GetFilas(); i++) {
    for (int j = 0; i < latice_[i].size(); j++) {
      delete latice_[i][j];
    }
  }
}

int Latice::PreguntarEstado(int x, int y) {
  int estado;
  std::cout << "Introduzca el estado de la célula: (" << x << ", " << y << ") ";
  std::cin >> estado;
  return estado;
}

void Latice::NextGeneration() {
  
}

void Latice::PrintLatice() {
  for (int i = 0; i < latice_.GetFilas(); i++) {
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
  for ( int i = 0; i < latice_.GetFilas(); i++ ) { // Accedo a cada fila , es decir cada Myvector<celula*>
    for ( int j = 0; j < latice_[i].size(); j++ ) { // Accedo a cada columna, es decir cada celula* y accedo a lo que apunta y le hago un get
      if ( latice_[i][j] -> GetEstado().GetEstado() == 1 ) {
        population++;
      }
    }
  }
  return population;
}